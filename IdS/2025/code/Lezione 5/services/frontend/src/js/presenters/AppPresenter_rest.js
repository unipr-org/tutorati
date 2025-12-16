(function (App) {
    /**
     * Presenter principale dell'applicazione con supporto REST API.
     * Gestisce la logica di business e coordina le interazioni tra Model e View.
     * Include gestione asincrona delle operazioni e feedback all'utente.
     * @class
     */
    class AppPresenter {
        /**
         * Crea una nuova istanza del Presenter utilizzando Dependency Injection.
         * @param {Object} model - Oggetto contenente i modelli dell'applicazione
         * @param {TaskList} model.taskList - Lista delle task
         * @param {Task2persistentStorage} model.taskStorage - Gestore della persistenza REST
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
         * Carica le task dal server in modo asincrono e le renderizza nella vista.
         * Mostra indicatore di caricamento e gestisce gli errori.
         * @async
         * @returns {Promise<void>}
         */
        async loadTasks() {
            try {
                this.appView.showLoading(true);
                const tasks = await this.taskStorage.findAll();
                
                // Pulisce la lista corrente
                this.taskList.clear();
                
                // Aggiunge le task dal server
                tasks.forEach(task => this.taskList.addTask(task));
                
                this.taskListView.render(this.taskList.getAllTasks());
                this.appView.showLoading(false);
            } catch (error) {
                this.appView.showLoading(false);
                this.appView.showAlert('Errore nel caricamento delle task: ' + error.message, 'error');
            }
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
         * Gestisce l'aggiunta di una nuova task in modo asincrono.
         * @async
         * @param {Object} taskData - Dati della task da aggiungere
         * @param {string} taskData.title - Titolo della task
         * @param {string} taskData.description - Descrizione della task
         * @param {string} taskData.dueDate - Data di scadenza
         * @param {string} taskData.priority - Priorità della task
         * @returns {Promise<void>}
         */
        async handleAddTask(taskData) {
            // validazione input utente
            if (!taskData.title || !taskData.description || !taskData.dueDate || !taskData.priority) {
                this.appView.showAlert('Per favore compila tutti i campi obbligatori', 'warning');
                return;
            }

            try {
                this.appView.showLoading(true);
                
                // creazione nuova task (business logic nel model)
                const newTask = new App.Task(
                    null, // ID generato dal server
                    taskData.title, 
                    taskData.description, 
                    taskData.dueDate, 
                    taskData.priority
                );

                // persistenza dei dati tramite API
                const savedTask = await this.taskStorage.save(newTask);

                // aggiunta al model locale
                this.taskList.addTask(savedTask);

                // aggiornamento interfaccia
                this._refreshListView();
                this.modalView.hide();
                this.appView.showLoading(false);
                this.appView.showAlert('Task aggiunta con successo!', 'success');
            } catch (error) {
                this.appView.showLoading(false);
                this.appView.showAlert('Errore nel salvataggio della task: ' + error.message, 'error');
            }
        }

        /**
         * Gestisce l'eliminazione di una task in modo asincrono.
         * Richiede conferma prima di procedere.
         * @async
         * @param {string|number} taskId - ID della task da eliminare
         * @returns {Promise<void>}
         */
        async handleDeleteTask(taskId) {
            if (!confirm('Sei sicuro di voler eliminare questa task?')) {
                return;
            }
            
            try {
                this.appView.showLoading(true);
                
                // rimozione dal server
                await this.taskStorage.delete(taskId);
                
                // rimozione dal model locale
                this.taskList.removeTask(taskId);
                
                // aggiornamento vista
                this._refreshListView();
                this.appView.showLoading(false);
                this.appView.showAlert('Task eliminata', 'success');
            } catch (error) {
                this.appView.showLoading(false);
                this.appView.showAlert('Errore nell\'eliminazione della task: ' + error.message, 'error');
            }
        }

        /**
         * Gestisce il cambio di stato di una task in modo asincrono.
         * @async
         * @param {string|number} taskId - ID della task da modificare
         * @returns {Promise<void>}
         */
        async handleToggleComplete(taskId) {
            try {
                this.appView.showLoading(true);
                
                // recupero task dal model
                const task = this.taskList.getTaskById(taskId);
                if (!task) return;
                
                // modifica dello stato (business logic)
                if (task.status === 'complete') {
                    task.markIncomplete();
                } else {
                    task.markComplete();
                }
                
                // salvataggio modifiche sul server
                await this.taskStorage.save(task);
                
                // refresh della vista
                this._refreshListView();
                this.appView.showLoading(false);
            } catch (error) {
                this.appView.showLoading(false);
                this.appView.showAlert('Errore nell\'aggiornamento dello stato: ' + error.message, 'error');
            }
        }

        /**
         * Gestisce la modifica di una task esistente in modo asincrono.
         * Apre il modale con i dati precompilati e gestisce il salvataggio sul server.
         * @async
         * @param {string|number} taskId - ID della task da modificare
         * @returns {Promise<void>}
         */
        async handleEditTask(taskId) {
            // recupero task da modificare
            const task = this.taskList.getTaskById(taskId);
            if (!task) return;
            
            // popolamento form con dati esistenti
            this.modalView.populateForm(task.toDTO());
            this.modalView.show();
            
            // rebinding temporaneo per gestire la modifica invece della creazione
            this.modalView.bindSubmit(async (taskData) => {
                try {
                    this.appView.showLoading(true);
                    
                    task.updateDetails(
                        taskData.title,
                        taskData.description,
                        taskData.dueDate,
                        taskData.priority,
                        taskData.status
                    );
                    
                    // salvataggio sul server
                    await this.taskStorage.save(task);
                    
                    this._refreshListView();
                    this.modalView.hide();
                    this.appView.showLoading(false);
                    this.appView.showAlert('Task modificata!', 'success');
                    
                    // ripristino del binding originale per nuove aggiunte
                    this.modalView.bindSubmit(this.handleAddTask.bind(this));
                } catch (error) {
                    this.appView.showLoading(false);
                    this.appView.showAlert('Errore nell\'aggiornamento della task: ' + error.message, 'error');
                }
            });
        }

        /**
         * Gestisce la cancellazione di tutte le task in modo asincrono.
         * Richiede conferma prima di procedere con l'eliminazione.
         * @async
         * @returns {Promise<void>}
         */
        async handleClearAll() {
            if (this.taskList.getTaskCount() === 0) {
                this.appView.showAlert('Non ci sono task da cancellare', 'info');
                return;
            }
            
            if (!confirm('Sei sicuro di voler eliminare TUTTE le task? Questa operazione non può essere annullata.')) {
                return;
            }
            
            try {
                this.appView.showLoading(true);
                
                // cancellazione completa dal server
                await this.taskStorage.clear();
                
                // cancellazione dal model locale
                this.taskList.clear();
                
                // refresh vista
                this._refreshListView();
                this.appView.showLoading(false);
                this.appView.showAlert('Tutte le task sono state cancellate', 'success');
            } catch (error) {
                this.appView.showLoading(false);
                this.appView.showAlert('Errore nella cancellazione delle task: ' + error.message, 'error');
            }
        }
    }
    App.AppPresenter = AppPresenter;
})(window.App = window.App || {});
