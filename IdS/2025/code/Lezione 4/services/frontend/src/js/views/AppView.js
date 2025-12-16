(function (App) {
    class AppView {
        constructor() {
            this.openModalBtn = $('#open-modal-btn');
            this.clearAllBtn = $('#clear-all-btn');
        }

        // --- Binding Eventi (delegati al Presenter) ---
        bindOpenModal(handler) {
            this.openModalBtn.on('click', handler);
        }

        bindClearAll(handler) {
            this.clearAllBtn.on('click', () => {
                if (confirm('Sei sicuro di voler cancellare tutte le attività?')) {
                    handler();
                }
            });
        }
        
        showAlert(message) {
            alert(message);
        }
    }
    App.AppView = AppView;
})(window.App = window.App || {});