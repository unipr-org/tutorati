(function (App) {
    /**
     * Presenter principale dell'applicazione secondo il pattern MVP.
     * Gestisce la logica di business e coordina le interazioni tra Model e View.
     * @class
     */
    class AppPresenter {
        /**
         * Crea una nuova istanza del Presenter utilizzando Dependency Injection.
         * @param {Object} model - Oggetto contenente i modelli dell'applicazione
         * @param {TaskList} model.taskList - Lista delle task
         * @param {Task2localStorage|Task2persistentStorage} model.taskStorage - Gestore della persistenza
         * @param {Object} views - Oggetto contenente le viste dell'applicazione
         * @param {AppView} views.appView - Vista principale
         * @param {TaskListView} views.taskListView - Vista della lista task
         * @param {ModalView} views.modalView - Vista del modale
         */
        constructor(model, views) {
            this.taskList = model.taskList;
            this.taskStorage = model.taskStorage;
            
            this.appView = views.appView;
            this.taskListView = views.taskListView;
            this.modalView = views.modalView;
        }

        /**
         * Inizializza tutti i binding tra view e presenter.
         * Collega gli eventi delle viste ai relativi gestori.
         */
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

        /**
         * Carica le task dallo storage e le renderizza nella vista.
         * Chiamato all'avvio dell'applicazione.
         */
        loadTasks() {
            const tasks = this.taskStorage.findAll();
            tasks.forEach(task => this.taskList.addTask(task));
            
            this.taskListView.render(this.taskList.getAllTasks());
        }
        
        /**
         * Metodo privato per aggiornare la visualizzazione della lista.
         * @private
         */
        _refreshListView() {
            this.taskListView.render(this.taskList.getAllTasks());
        }

        // --- gestori degli eventi utente ---

        /**
         * Gestisce l'apertura del modale per aggiungere una nuova task.
         */
        handleOpenModal() {
            this.modalView.reset();
            this.modalView.show();
        }

        /**
         * Gestisce la chiusura del modale.
         */
        handleCloseModal() {
            this.modalView.hide();
        }

        /**
         * Gestisce l'aggiunta di una nuova task.
         * @param {Object} taskData - Dati della task da aggiungere
         * @param {string} taskData.title - Titolo della task
         * @param {string} taskData.description - Descrizione della task
         * @param {string} taskData.dueDate - Data di scadenza
         * @param {string} taskData.priority - Priorità della task
         */
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

        /**
         * Gestisce l'eliminazione di una task.
         * @param {string|number} taskId - ID della task da eliminare
         */
        handleDeleteTask(taskId) {
            // rimozione dal model e storage
            this.taskList.removeTask(taskId);
            this.taskStorage.delete(taskId);
            
            // aggiornamento vista
            this._refreshListView();
            this.appView.showAlert('Task eliminata');
        }

        /**
         * Gestisce il cambio di stato di una task (completata/non completata).
         * @param {string|number} taskId - ID della task da modificare
         */
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

        /**
         * Gestisce la modifica di una task esistente.
         * Apre il modale con i dati precompilati e gestisce il salvataggio.
         * @param {string|number} taskId - ID della task da modificare
         */
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

        /**
         * Gestisce la cancellazione di tutte le task.
         * Rimuove tutte le task dal model e dallo storage.
         */
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