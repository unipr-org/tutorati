// script.js
(function (App) {
    
    $(document).ready(function() {
        
        // modello
        const model = {
            taskList: new App.TaskList(),
            taskStorage: new App.Task2localStorage()
        };
        
        // viste
        const views = {
            appView: new App.AppView(),
            taskListView: new App.TaskListView(),
            modalView: new App.ModalView()
        };
        
        // inizializzazione del Presenter
        const presenter = new App.AppPresenter(model, views);
        
        // avvio dell'applicazione
        presenter.init();
        
        console.log('App (Composite MVP) inizializzata correttamente');
    });

})(window.App);