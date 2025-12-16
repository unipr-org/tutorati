(function (App) {

    class TaskList {
        #tasks;
        constructor() {
            this.#tasks = [];
        }

        addTask(task) {
            this.#tasks.push(task);
        }

        removeTask(id) {
            this.#tasks = this.#tasks.filter(t => t.id !== id);
        }

        getAllTasks() {
            return this.#tasks;
        }

        getTaskById(id) {
            return this.#tasks.find(t => t.id === id);
        }

        getCompletedTasks() {
            return this.#tasks.filter(task => task.status === 'complete');
        }

        getIncompleteTasks() {
            return this.#tasks.filter(task => task.status === 'incomplete');
        }

        clear() {
            this.#tasks = [];
        }

        getTaskCount() {
            return this.#tasks.length;
        }

        // Ordinamento per priorità
        getTasksByPriority() {
            const priorityOrder = { 'Alta': 1, 'Media': 2, 'Bassa': 3 };
            return [...this.#tasks].sort((a, b) => 
                priorityOrder[a.priority] - priorityOrder[b.priority]
            );
        }

        // Ordinamento per scadenza
        getTasksByDueDate() {
            return [...this.#tasks].sort((a, b) => 
                new Date(a.dueDate) - new Date(b.dueDate)
            );
        }
    }
    App.TaskList = TaskList;

})(window.App = window.App || {});
