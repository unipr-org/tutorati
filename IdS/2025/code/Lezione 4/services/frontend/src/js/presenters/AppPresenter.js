(function (App) {
    class AppPresenter {
        // dependency injection: riceve model e views dal bootstrap
        constructor(model, views) {
            this.taskList = model.taskList;
            this.taskStorage = model.taskStorage;
            
            this.appView = views.appView;
            this.taskListView = views.taskListView;
            this.modalView = views.modalView;
        }

        // inizializzazione di tutti i binding tra view e presenter
        init() {
            // collegamento eventi della vista principale
            this.appView.bindOpenModal(this.handleOpenModal.bind(this));
            this.appView.bindClearAll(this.handleClearAll.bind(this));
            
            // collegamento eventi del modale
            this.modalView.bindSubmit(this.handleAddTask.bind(this));
            this.modalView.bindClose(this.handleCloseModal.bind(this));
            
            // collegamento eventi della lista (con event delegation)
            this.taskListView.bindDeleteTask(this.handleDeleteTask.bind(this));
            this.taskListView.bindToggleComplete(this.handleToggleComplete.bind(this));
            this.taskListView.bindEditTask(this.handleEditTask.bind(this));
            
            // caricamento dati all'avvio
            this.loadTasks();
        }

        // caricamento task dallo storage e rendering iniziale
        loadTasks() {
            const tasks = this.taskStorage.findAll();
            tasks.forEach(task => this.taskList.addTask(task));
            
            this.taskListView.render(this.taskList.getAllTasks());
        }
        
        // metodo privato per aggiornare la visualizzazione della lista
        _refreshListView() {
            this.taskListView.render(this.taskList.getAllTasks());
        }

        // --- gestori degli eventi utente ---

        handleOpenModal() {
            this.modalView.reset();
            this.modalView.show();
        }

        handleCloseModal() {
            this.modalView.hide();
        }

        handleAddTask(taskData) {
            // validazione input utente
            if (!taskData.title || !taskData.description || !taskData.dueDate || !taskData.priority) {
                this.appView.showAlert('Per favore compila tutti i campi obbligatori');
                return;
            }

            // creazione nuova task (business logic nel model)
            const newTask = new App.Task(
                App.Task.generateId(), 
                taskData.title, 
                taskData.description, 
                taskData.dueDate, 
                taskData.priority
            );

            // persistenza dei dati
            this.taskList.addTask(newTask);
            this.taskStorage.save(newTask);

            // aggiornamento interfaccia
            this._refreshListView();
            this.modalView.hide();
            this.appView.showAlert('Task aggiunta con successo!');
        }

        handleDeleteTask(taskId) {
            // rimozione dal model e storage
            this.taskList.removeTask(taskId);
            this.taskStorage.delete(taskId);
            
            // aggiornamento vista
            this._refreshListView();
            this.appView.showAlert('Task eliminata');
        }

        handleToggleComplete(taskId) {
            // recupero task dal model
            const task = this.taskList.getTaskById(taskId);
            if (!task) return;
            
            // modifica dello stato (business logic)
            if (task.status === 'complete') {
                task.markIncomplete();
            } else {
                task.markComplete();
            }
            
            // salvataggio modifiche
            this.taskStorage.save(task);
            
            // refresh della vista
            this._refreshListView();
        }

        handleEditTask(taskId) {
            // recupero task da modificare
            const task = this.taskList.getTaskById(taskId);
            if (!task) return;
            
            // popolamento form con dati esistenti
            this.modalView.populateForm(task.toDTO());
            this.modalView.show();
            
            // rebinding temporaneo per gestire la modifica invece della creazione
            this.modalView.bindSubmit((taskData) => {
                task.updateDetails(
                    taskData.title,
                    taskData.description,
                    taskData.dueDate,
                    taskData.priority
                );
                
                this.taskStorage.save(task);
                this._refreshListView();
                this.modalView.hide();
                this.appView.showAlert('Task modificata!');
                
                // ripristino del binding originale per nuove aggiunte
                this.modalView.bindSubmit(this.handleAddTask.bind(this));
            });
        }

        handleClearAll() {
            if (this.taskList.getTaskCount() === 0) {
                this.appView.showAlert('Non ci sono task da cancellare');
                return;
            }
            
            // cancellazione completa da model e storage
            this.taskStorage.clear();
            this.taskList.clear();
            
            // refresh vista
            this._refreshListView();
            this.appView.showAlert('Tutte le task sono state cancellate');
        }
    }
    App.AppPresenter = AppPresenter;
})(window.App = window.App || {});