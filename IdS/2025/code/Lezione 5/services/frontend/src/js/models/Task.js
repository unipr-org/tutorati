(function (App) {
    /**
     * Classe che rappresenta una singola task/attività.
     * Utilizza campi privati per l'incapsulamento dei dati.
     * @class
     */
    class Task {
        #id;
        #title;
        #description;
        #dueDate;
        #priority;
        #status;

        /**
         * Crea una nuova istanza di Task.
         * @param {string|number} id - Identificatore univoco della task
         * @param {string} title - Titolo della task
         * @param {string} description - Descrizione dettagliata della task
         * @param {string} dueDate - Data di scadenza (formato YYYY-MM-DD)
         * @param {string} priority - Priorità della task (high, medium, low)
         */
        constructor(id, title, description, dueDate, priority) {
            this.#id = id;
            this.#title = title;
            this.#description = description;
            this.#dueDate = dueDate;
            this.#priority = priority;
            this.#status = 'pending';
        }

        /**
         * Restituisce l'ID della task.
         * @returns {string|number} ID della task
         */
        get id() {
            return this.#id;
        }

        /**
         * Restituisce il titolo della task.
         * @returns {string} Titolo della task
         */
        get title() {
            return this.#title;
        }

        /**
         * Restituisce la descrizione della task.
         * @returns {string} Descrizione della task
         */
        get description() {
            return this.#description;
        }

        /**
         * Restituisce la data di scadenza della task.
         * @returns {string} Data di scadenza
         */
        get dueDate() {
            return this.#dueDate;
        }

        /**
         * Restituisce la priorità della task.
         * @returns {string} Priorità della task
         */
        get priority() {
            return this.#priority;
        }

        /**
         * Restituisce lo stato corrente della task.
         * @returns {string} Stato della task (pending, complete, in_progress)
         */
        get status() {
            return this.#status;
        }

        /**
         * Imposta l'ID della task.
         * @param {string|number} id - Nuovo ID da assegnare
         */
        setId(id) {
            this.#id = id;
        }

        /**
         * Metodo privato per impostare lo stato della task.
         * @private
         * @param {string} status - Nuovo stato
         */
        #setStatus(status) {
            this.#status = status;
        }

        /**
         * Segna la task come completata.
         */
        markComplete() {
            this.#status = 'complete';
        }

        /**
         * Segna la task come non completata (pending).
         */
        markIncomplete() {
            this.#status = 'pending';
        }

        /**
         * Aggiorna tutti i dettagli della task.
         * @param {string} newTitle - Nuovo titolo
         * @param {string} newDescription - Nuova descrizione
         * @param {string} newDueDate - Nuova data di scadenza
         * @param {string} newPriority - Nuova priorità
         * @param {string} newStatus - Nuovo stato
         */
        updateDetails(newTitle, newDescription, newDueDate, newPriority, newStatus) {
            this.#title = newTitle;
            this.#description = newDescription;
            this.#dueDate = newDueDate;
            this.#priority = newPriority;
            this.#status = newStatus;
        }

        /**
         * Converte l'oggetto Task in un Data Transfer Object (DTO).
         * @returns {{id: (string|number), title: string, description: string, dueDate: string, priority: string, status: string}} DTO della task
         */
        toDTO() {
            return {
                id: this.#id,
                title: this.#title,
                description: this.#description,
                dueDate: this.#dueDate,
                priority: this.#priority,
                status: this.#status
            };
        }

        /**
         * Metodo statico che crea un'istanza di Task a partire da un DTO.
         * @static
         * @param {{id: (string|number), title: string, description: string, dueDate: string, priority: string, status: string}} dto - Data Transfer Object della task
         * @returns {Task} Nuova istanza di Task
         */
        static fromDTO(dto) {
            const task = new Task(dto.id, dto.title, dto.description, dto.dueDate, dto.priority);
            task.#setStatus(dto.status);
            return task;
        }
        
        /**
         * Genera un ID univoco per una nuova task.
         * Utilizza crypto.randomUUID se disponibile, altrimenti genera un ID basato su timestamp.
         * @static
         * @returns {string} ID univoco generato
         */
        static generateId() {
            return (crypto.randomUUID && crypto.randomUUID()) ||
                (Date.now().toString(36) + Math.random().toString(36).slice(2, 8));
        }
    }

    App.Task = Task;

})(window.App = window.App || {});