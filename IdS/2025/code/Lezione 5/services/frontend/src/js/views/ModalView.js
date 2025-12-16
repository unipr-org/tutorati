(function (App) {
    /**
     * Vista del modale per aggiungere/modificare task.
     * Gestisce il form e gli eventi associati al modale.
     * @class
     */
    class ModalView {
        /**
         * Crea una nuova istanza di ModalView.
         * Inizializza i riferimenti agli elementi DOM del modale e del form.
         */
        constructor() {
            this.modal = $('#task-modal');
            this.form = $('#task-form');
            this.closeModalBtn = $('#close-modal-btn');
            
            // Campi del form
            this.taskNameInput = $('#task-name');
            this.taskDescInput = $('#task-desc');
            this.taskDueDateInput = $('#task-due-date');
            this.taskPriorityInput = $('#task-priority');
            this.taskStatusInput = $('#task-status');
        }

        /**
         * Mostra il modale.
         */
        show() {
            this.modal.removeClass('hidden');
        }

        /**
         * Nasconde il modale.
         */
        hide() {
            this.modal.addClass('hidden');
        }

        /**
         * Resetta i campi del form ai valori predefiniti.
         */
        reset() {
            this.form[0].reset();
        }

        /**
         * Raccoglie i dati inseriti nel form.
         * @returns {{title: string, description: string, dueDate: string, priority: string, status: string}} Oggetto con i dati della task
         */
        getTaskData() {
            return {
                title: this.taskNameInput.val().trim(),
                description: this.taskDescInput.val().trim(),
                dueDate: this.taskDueDateInput.val(),
                priority: this.taskPriorityInput.val(),
                status: this.taskStatusInput.val()
            };
        }

        /**
         * Popola il form con i dati di una task esistente per la modifica.
         * @param {Object} taskDTO - DTO della task contenente i dati da visualizzare
         * @param {string} taskDTO.title - Titolo della task
         * @param {string} taskDTO.description - Descrizione della task
         * @param {string} taskDTO.dueDate - Data di scadenza
         * @param {string} taskDTO.priority - Priorità della task
         * @param {string} taskDTO.status - Stato della task
         */
        populateForm(taskDTO) {
            this.taskNameInput.val(taskDTO.title);
            this.taskDescInput.val(taskDTO.description);
            this.taskDueDateInput.val(taskDTO.dueDate);
            this.taskPriorityInput.val(taskDTO.priority);
            this.taskStatusInput.val(taskDTO.status);
        }

        // --- binding degli eventi (delegati al Presenter) ---
        
        /**
         * Collega il gestore per il submit del form.
         * Rimuove eventuali handler precedenti per evitare duplicati.
         * @param {Function} handler - Funzione da eseguire, riceve i dati del form come parametro
         */
        bindSubmit(handler) {
            // rimozione di eventuali handler precedenti per evitare duplicati
            this.form.off('submit');
            this.form.on('submit', (e) => {
                e.preventDefault();
                handler(this.getTaskData());
            });
        }

        /**
         * Collega il gestore per la chiusura del modale.
         * Gestisce il click sul pulsante di chiusura, il click fuori dal modale e il tasto ESC.
         * @param {Function} handler - Funzione da eseguire alla chiusura
         */
        bindClose(handler) {
            this.closeModalBtn.on('click', handler);
            this.modal.on('click', (e) => {
                if (e.target.id === 'task-modal') handler();
            });
            $(document).on('keydown', (e) => {
                if (e.key === 'Escape' && !this.modal.hasClass('hidden')) {
                    handler();
                }
            });
        }
    }
    App.ModalView = ModalView;
})(window.App = window.App || {});