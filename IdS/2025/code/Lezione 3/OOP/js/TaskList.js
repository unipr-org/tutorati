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

        getCompletedTasks() {
            return this.#tasks.filter(task => task.status === 'complete');
        }

        getIncompleteTasks() {
            return this.#tasks.filter(task => task.status === 'incomplete');
        }
    }
    App.TaskList = TaskList;

})(window.App = window.App || {});
