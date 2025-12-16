
(function (App) {

    class TaskView {
        constructor() {
            // riferimenti dom
            this.tbody = $('#task-table-body');
            this.modal = $('#task-modal');
            this.form = $('#task-form');
            this.openModalBtn = $('#open-modal-btn');
            this.closeModalBtn = $('#close-modal-btn');
            this.clearAllBtn = $('#clear-all-btn');

        }

        // Metodo per mostrare le attività
        // riceve i dati *già pronti* dal Presenter
        renderTasks(tasks) {
            this.tbody.empty(); // Svuota la tabella

            if (tasks.length === 0) {
                this.tbody.html(`
                    <td colspan="5" class="border border-black p-2 text-center text-gray-500 italic">
                        Nessuna attività presente. Clicca sul pulsante + per aggiungerne una.
                    </td>
                `);
                return;
            }

            tasks.forEach(task => {
                const statusMap = { 'complete': 'Completata', 'incomplete': 'Non completata' };
                const formattedDate = task.dueDate ? new Date(task.dueDate).toLocaleDateString('it-IT') : '';
                
                this.tbody.append(`
                    <tr data-task-id="${task.id}">
                        <td class="border border-black p-2">${task.title}</td>
                        <td class="border border-black p-2">${task.description}</td>
                        <td class="border border-black p-2">${formattedDate}</td>
                        <td class="border border-black p-2">${task.priority}</td>
                        <td class="border border-black p-2">${statusMap[task.status] || task.status}</td>
                    </tr>
                `);
            });
        }
        

        // --- Gestori di Eventi (Binding) ---
        // La Vista "aggancia" un'azione dell'utente (es. submit)
        // a un metodo (handler) fornito dal Presenter.

        bindOpenModal(handler) {
            this.openModalBtn.on('click', () => {
                handler(); // Esegui la logica del Presenter
            });
        }
        
        bindCloseModal(handler) {
             this.closeModalBtn.on('click', () => {
                handler();
            });
             // Chiudi cliccando fuori
             this.modal.on('click', (e) => {
                 if (e.target.id === 'task-modal') {
                     handler();
                 }
             });
             // Chiudi con ESC
             $(document).on('keydown', (e) => {
                 if (e.key === 'Escape') {
                     handler();
                 }
             });
        }

        bindAddTask(handler) {
            this.form.on('submit', (e) => {
                e.preventDefault();
                const taskData = this.getTaskData();
                handler(taskData); // Passa i dati al Presenter
            });
        }

        bindClearAll(handler) {
            this.clearAllBtn.on('click', () => {
                // La vista può gestire conferme semplici
                if (confirm('Sei sicuro di voler cancellare tutte le attività?')) {
                    handler();
                }
            });
        }
        
        // metodo per mostrare errori (invece di alert)
        showAlert(message) {
            alert(message); // Semplice, ma idealmente sarebbe un elemento DOM
        }
    }

    App.TaskView = TaskView;

})(window.App = window.App || {});