(function (App) {
    /**
     * Vista principale dell'applicazione.
     * Gestisce gli elementi UI comuni come pulsanti, spinner di caricamento e notifiche.
     * @class
     */
    class AppView {
        /**
         * Crea una nuova istanza di AppView.
         * Inizializza i riferimenti agli elementi DOM e crea elementi di loading e alert se necessario.
         */
        constructor() {
            this.openModalBtn = $('#open-modal-btn');
            this.clearAllBtn = $('#clear-all-btn');
            this.loadingSpinner = $('#loading-spinner');
            this.alertContainer = $('#alert-container');

            // Crea elementi di loading e alert se non esistono
            if (this.loadingSpinner.length === 0) {
                $('body').append('<div id="loading-spinner" style="display:none; position:fixed; top:50%; left:50%; transform:translate(-50%,-50%); z-index:9999; background:rgba(0,0,0,0.7); color:white; padding:20px; border-radius:8px;">Caricamento...</div>');
                this.loadingSpinner = $('#loading-spinner');
            }

            if (this.alertContainer.length === 0) {
                $('body').append('<div id="alert-container" style="position:fixed; top:20px; right:20px; z-index:9999;"></div>');
                this.alertContainer = $('#alert-container');
            }
        }

        // --- Binding Eventi (delegati al Presenter) ---
        
        /**
         * Collega il gestore per l'apertura del modale.
         * @param {Function} handler - Funzione da eseguire al click
         */
        bindOpenModal(handler) {
            this.openModalBtn.on('click', handler);
        }

        /**
         * Collega il gestore per la cancellazione di tutte le task.
         * Include una richiesta di conferma prima di procedere.
         * @param {Function} handler - Funzione da eseguire dopo la conferma
         */
        bindClearAll(handler) {
            this.clearAllBtn.on('click', () => {
                if (confirm('Sei sicuro di voler cancellare tutte le attività?')) {
                    handler();
                }
            });
        }

        /**
         * Mostra o nasconde lo spinner di caricamento.
         * @param {boolean} show - true per mostrare, false per nascondere
         */
        showLoading(show) {
            if (show) {
                this.loadingSpinner.show();
            } else {
                this.loadingSpinner.hide();
            }
        }

        /**
         * Mostra un messaggio di alert all'utente.
         * L'alert viene automaticamente rimosso dopo 5 secondi.
         * @param {string} message - Messaggio da visualizzare
         * @param {string} [type='info'] - Tipo di alert (success, error, warning, info)
         */
        showAlert(message, type = 'info') {
            const alertClass = {
                'success': 'alert-success',
                'error': 'alert-danger',
                'warning': 'alert-warning',
                'info': 'alert-info'
            }[type] || 'alert-info';

            const alertHtml = `
                <div class="alert ${alertClass} alert-dismissible fade show" role="alert" style="min-width:250px; margin-bottom:10px;">
                    ${message}
                    <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
                </div>
            `;

            const $alert = $(alertHtml);
            this.alertContainer.append($alert);

            // Auto-rimuovi dopo 5 secondi
            setTimeout(() => {
                $alert.fadeOut(300, function() {
                    $(this).remove();
                });
            }, 5000);
        }
    }
    App.AppView = AppView;
})(window.App = window.App || {});