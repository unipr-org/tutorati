/**
 * Script di bootstrap dell'applicazione Task Manager.
 * Inizializza i modelli, le viste e il presenter utilizzando il pattern MVP.
 * @file script.js
 */
(function (App) {
    
    $(document).ready(function() {
        
        /**
         * Configurazione del modello dell'applicazione.
         * Utilizza localStorage per la persistenza dei dati.
         * @type {Object}
         */
        const model = {
            taskList: new App.TaskList(),
            taskStorage: new App.Task2localStorage()
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
    });

})(window.App);