(function (App) {
    class Task {
        #id;
        #title;
        #description;
        #dueDate;
        #priority;
        #status;

        constructor(id, title, description, dueDate, priority) {
            this.#id = id;
            this.#title = title;
            this.#description = description;
            this.#dueDate = dueDate;
            this.#priority = priority;
            this.#status = 'incomplete';
        }

        get id() {
            return this.#id;
        }

        get title() {
            return this.#title;
        }

        get description() {
            return this.#description;
        }

        get dueDate() {
            return this.#dueDate;
        }

        get priority() {
            return this.#priority;
        }

        get status() {
            return this.#status;
        }

        markComplete() {
            this.#status = 'complete';
        }

        markIncomplete() {
            this.#status = 'incomplete';
        }

        updateDetails(newTitle, newDescription, newDueDate, newPriority) {
            this.#title = newTitle;
            this.#description = newDescription;
            this.#dueDate = newDueDate;
            this.#priority = newPriority;
        }

        // converte l'oggetto in un Data Transfer Object (DTO)
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

        // metodo statico che crea un'istanza di Task a partire da un DTO
        static fromDTO(dto) {
            const task = new Task(dto.id, dto.title, dto.description, dto.dueDate, dto.priority);
            if (dto.status === 'complete') {
                task.markComplete();
            }
            return task;
        }
        
        static generateId() {
            return (crypto.randomUUID && crypto.randomUUID()) ||
                (Date.now().toString(36) + Math.random().toString(36).slice(2, 8));
        }
    }

    App.Task = Task;

})(window.App = window.App || {});