(function (App) {

    /**
     * Classe che gestisce una collezione di task.
     * Fornisce metodi per aggiungere, rimuovere, filtrare e ordinare le task.
     * @class
     */
    class TaskList {
        #tasks;
        
        /**
         * Crea una nuova istanza di TaskList.
         * Inizializza un array vuoto per contenere le task.
         */
        constructor() {
            this.#tasks = [];
        }

        /**
         * Aggiunge una task alla lista.
         * @param {Task} task - Task da aggiungere
         */
        addTask(task) {
            this.#tasks.push(task);
        }

        /**
         * Rimuove una task dalla lista dato il suo ID.
         * @param {string|number} id - ID della task da rimuovere
         */
        removeTask(id) {
            this.#tasks = this.#tasks.filter(t => t.id !== id);
        }

        /**
         * Restituisce tutte le task presenti nella lista.
         * @returns {Task[]} Array di tutte le task
         */
        getAllTasks() {
            return this.#tasks;
        }

        /**
         * Cerca e restituisce una task specifica dato il suo ID.
         * @param {string|number} id - ID della task da cercare
         * @returns {Task|undefined} Task trovata o undefined se non esiste
         */
        getTaskById(id) {
            return this.#tasks.find(t => t.id === id);
        }

        /**
         * Restituisce tutte le task completate.
         * @returns {Task[]} Array delle task con stato 'complete'
         */
        getCompletedTasks() {
            return this.#tasks.filter(task => task.status === 'complete');
        }

        /**
         * Restituisce tutte le task incomplete.
         * @returns {Task[]} Array delle task con stato 'incomplete'
         */
        getIncompleteTasks() {
            return this.#tasks.filter(task => task.status === 'incomplete');
        }

        /**
         * Rimuove tutte le task dalla lista.
         */
        clear() {
            this.#tasks = [];
        }

        /**
         * Restituisce il numero totale di task nella lista.
         * @returns {number} Conteggio delle task
         */
        getTaskCount() {
            return this.#tasks.length;
        }

        /**
         * Restituisce le task ordinate per priorità (Alta, Media, Bassa).
         * @returns {Task[]} Array ordinato di task
         */
        getTasksByPriority() {
            const priorityOrder = { 'Alta': 1, 'Media': 2, 'Bassa': 3 };
            return [...this.#tasks].sort((a, b) => 
                priorityOrder[a.priority] - priorityOrder[b.priority]
            );
        }

        /**
         * Restituisce le task ordinate per data di scadenza.
         * @returns {Task[]} Array ordinato di task per data crescente
         */
        getTasksByDueDate() {
            return [...this.#tasks].sort((a, b) => 
                new Date(a.dueDate) - new Date(b.dueDate)
            );
        }
    }
    App.TaskList = TaskList;

})(window.App = window.App || {});
