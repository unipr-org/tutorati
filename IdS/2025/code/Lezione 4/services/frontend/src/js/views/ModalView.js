(function (App) {
    class ModalView {
        constructor() {
            this.modal = $('#task-modal');
            this.form = $('#task-form');
            this.closeModalBtn = $('#close-modal-btn');
            
            // Campi del form
            this.taskNameInput = $('#task-name');
            this.taskDescInput = $('#task-desc');
            this.taskDueDateInput = $('#task-due-date');
            this.taskPriorityInput = $('#task-priority');
        }

        show() {
            this.modal.removeClass('hidden');
        }

        hide() {
            this.modal.addClass('hidden');
        }

        reset() {
            this.form[0].reset();
        }

        getTaskData() {
            return {
                title: this.taskNameInput.val().trim(),
                description: this.taskDescInput.val().trim(),
                dueDate: this.taskDueDateInput.val(),
                priority: this.taskPriorityInput.val()
            };
        }

        // Popola il form con i dati di una task esistente (per la modifica)
        populateForm(taskDTO) {
            this.taskNameInput.val(taskDTO.title);
            this.taskDescInput.val(taskDTO.description);
            this.taskDueDateInput.val(taskDTO.dueDate);
            this.taskPriorityInput.val(taskDTO.priority);
        }

        // --- binding degli eventi (delegati al Presenter) ---
        bindSubmit(handler) {
            // rimozione di eventuali handler precedenti per evitare duplicati
            this.form.off('submit');
            this.form.on('submit', (e) => {
                e.preventDefault();
                handler(this.getTaskData());
            });
        }

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