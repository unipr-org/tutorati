(function (App) {
    /**
     * Vista della lista delle task.
     * Gestisce il rendering della tabella delle task e gli eventi associati.
     * @class
     */
    class TaskListView {
        /**
         * Crea una nuova istanza di TaskListView.
         * Inizializza il riferimento al corpo della tabella.
         */
        constructor() {
            this.tbody = $('#task-table-body');
        }

        /**
         * Renderizza la lista delle task nella tabella.
         * @param {Task[]} tasks - Array di task da visualizzare
         */
        render(tasks) {
            this.tbody.empty();

            if (tasks.length === 0) {
                this.tbody.html(`
                    <tr>
                        <td colspan="6" class="border border-black p-2 text-center text-gray-500 italic">
                            Nessuna attività presente.
                        </td>
                    </tr>
                `);
                return;
            }

            tasks.forEach(task => {
                const dto = task.toDTO(); // Usiamo il DTO per i dati
                const statusMap = {
                    'complete': 'Completata',
                    'pending': 'Non iniziata',
                    'in_progress': 'In corso'
                };
                const priorityMap = {
                    'high': 'Alta',
                    'medium': 'Media',
                    'low': 'Bassa'
                };
                const formattedDate = dto.dueDate ? 
                    new Date(dto.dueDate + 'T00:00:00').toLocaleDateString('it-IT') : '';
                
                const statusClass = dto.status === 'complete' ? 
                    'bg-green-100 line-through' : '';
                
                this.tbody.append(`
                    <tr data-task-id="${dto.id}" class="${statusClass}">
                        <td class="border border-black p-2">${dto.title}</td>
                        <td class="border border-black p-2">${dto.description}</td>
                        <td class="border border-black p-2">${formattedDate}</td>
                        <td class="border border-black p-2">${priorityMap[dto.priority] || dto.priority}</td>
                        <td class="border border-black p-2">${statusMap[dto.status] || dto.status}</td>
                        <td class="border border-black p-2">
                            <div class="flex gap-2 justify-center">
                                <button 
                                    class="task-toggle-btn px-2 py-1 ${dto.status === 'complete' ? 'bg-yellow-500' : 'bg-green-500'} text-white rounded hover:opacity-80"
                                    data-task-id="${dto.id}"
                                    title="${dto.status === 'complete' ? 'Segna come non completata' : 'Segna come completata'}"
                                >
                                    ${dto.status === 'complete' ? '↩️' : '✓'}
                                </button>
                                <button 
                                        class="task-edit-btn px-2 py-1 bg-blue-500 text-white rounded hover:bg-blue-600"
                                    data-task-id="${dto.id}"
                                    title="Modifica"
                                >
                                    <svg xmlns="http://www.w3.org/2000/svg" class="ionicon" viewBox="0 0 512 512"><path fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="32" d="M364.13 125.25L87 403l-23 45 44.99-23 277.76-277.13-22.62-22.62zM420.69 68.69l-22.62 22.62 22.62 22.63 22.62-22.63a16 16 0 000-22.62h0a16 16 0 00-22.62 0z"/></svg>
                                </button>
                                <button 
                                    class="task-delete-btn px-2 py-1 bg-red-500 text-white rounded hover:bg-red-600"
                                    data-task-id="${dto.id}"
                                    title="Elimina"
                                >
                                    🗑️
                                </button>
                            </div>
                        </td>
                    </tr>
                `);
            });
        }

        // --- binding degli eventi (event delegation) ---
        
        /**
         * Collega il gestore per l'eliminazione delle task.
         * Utilizza event delegation per gestire i click sui pulsanti di eliminazione.
         * @param {Function} handler - Funzione da eseguire, riceve taskId come parametro
         */
        bindDeleteTask(handler) {
            this.tbody.on('click', '.task-delete-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                if (confirm('Sei sicuro di voler eliminare questa task?')) {
                    handler(taskId);
                }
            });
        }

        /**
         * Collega il gestore per il cambio di stato delle task.
         * Utilizza event delegation per gestire i click sui pulsanti di toggle.
         * @param {Function} handler - Funzione da eseguire, riceve taskId come parametro
         */
        bindToggleComplete(handler) {
            this.tbody.on('click', '.task-toggle-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                handler(taskId);
            });
        }

        /**
         * Collega il gestore per la modifica delle task.
         * Utilizza event delegation per gestire i click sui pulsanti di modifica.
         * @param {Function} handler - Funzione da eseguire, riceve taskId come parametro
         */
        bindEditTask(handler) {
            this.tbody.on('click', '.task-edit-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                handler(taskId);
            });
        }
    }
    App.TaskListView = TaskListView;
})(window.App = window.App || {});