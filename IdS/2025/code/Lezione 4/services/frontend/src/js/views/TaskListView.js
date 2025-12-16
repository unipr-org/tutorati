(function (App) {
    class TaskListView {
        constructor() {
            this.tbody = $('#task-table-body');
        }

        // riceve i dati pronti e li renderizza
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
                    'incomplete': 'Non completata' 
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
                        <td class="border border-black p-2">${dto.priority}</td>
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
                                    ✏️
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
        bindDeleteTask(handler) {
            this.tbody.on('click', '.task-delete-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                if (confirm('Sei sicuro di voler eliminare questa task?')) {
                    handler(taskId);
                }
            });
        }

        bindToggleComplete(handler) {
            this.tbody.on('click', '.task-toggle-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                handler(taskId);
            });
        }

        bindEditTask(handler) {
            this.tbody.on('click', '.task-edit-btn', (e) => {
                const taskId = $(e.currentTarget).data('task-id');
                handler(taskId);
            });
        }
    }
    App.TaskListView = TaskListView;
})(window.App = window.App || {});