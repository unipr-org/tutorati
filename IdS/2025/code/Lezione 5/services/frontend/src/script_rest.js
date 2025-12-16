/**
 * Script di bootstrap dell'applicazione Task Manager con supporto REST API.
 * Inizializza i modelli, le viste e il presenter utilizzando il pattern MVP.
 * Supporta sia localStorage che persistenza tramite REST API.
 * @file script_rest.js
 */
(function (App) {
    
    $(document).ready(function() {
        
        /**
         * Flag di configurazione per la scelta della modalità di storage.
         * true = REST API, false = localStorage
         * @constant {boolean}
         */
        const USE_REST_API = true;
        
        /**
         * Configurazione del modello dell'applicazione.
         * Sceglie dinamicamente tra localStorage e REST API in base alla configurazione.
         * @type {Object}
         */
        const model = {
            taskList: new App.TaskList(),
            // scelta dinamica dello storage
            taskStorage: USE_REST_API 
                ? new App.Task2persistentStorage() 
                : new App.Task2localStorage()
        };
        
        /**
         * Configurazione delle viste dell'applicazione.
         * @type {Object}
         */
        const views = {
            appView: new App.AppView(),
            taskListView: new App.TaskListView(),
            modalView: new App.ModalView()
        };
        
        /**
         * Inizializzazione del Presenter con dependency injection.
         * @type {AppPresenter}
         */
        const presenter = new App.AppPresenter(model, views);
        
        // Avvio dell'applicazione
        presenter.init();
        
        console.log('App (Composite MVP) inizializzata correttamente');
        console.log('Storage mode:', USE_REST_API ? 'REST API' : 'localStorage');
    });

})(window.App);
