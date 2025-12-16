(function (App) {
    /**
     * Chiave utilizzata per memorizzare le task nel localStorage.
     * @constant {string}
     */
    const STORAGE_KEY = "tasks";

    /**
     * Classe che gestisce la persistenza delle task utilizzando localStorage.
     * Implementa operazioni CRUD (Create, Read, Update, Delete) per le task.
     * @class
     */
    class Task2localStorage {
        /**
         * Crea una nuova istanza del gestore di persistenza localStorage.
         */
        constructor() {}

        /**
         * Carica tutte le task dal localStorage.
         * @returns {Task[]} Array di task caricate dal localStorage
         */
        findAll() {
            const data = localStorage.getItem(STORAGE_KEY);
            if (!data) return [];
            try {
                const arr = JSON.parse(data);
                return arr.map(App.Task.fromDTO);
            } catch (e) {
                console.error("Errore parsing localStorage:", e);
                return [];
            }
        }

        /**
         * Trova una task specifica per ID.
         * @param {string|number} id - ID della task da cercare
         * @returns {Task|null} Task trovata o null se non esiste
         */
        findById(id) {
            const all = this.findAll();
            return all.find(t => t.id === id) || null;
        }

        /**
         * Salva o aggiorna una task nel localStorage.
         * Se la task esiste già (stesso ID), viene aggiornata; altrimenti viene aggiunta.
         * @param {Task} task - Task da salvare
         */
        save(task) {
            const all = this.findAll();
            const dto = task.toDTO();
            const i = all.findIndex(t => t.id === dto.id);
            if (i >= 0) {
                all[i] = dto;
            } else {
                all.push(dto);
            }
            localStorage.setItem(STORAGE_KEY, JSON.stringify(all));
        }

        /**
         * Elimina una task dal localStorage dato il suo ID.
         * @param {string|number} id - ID della task da eliminare
         */
        delete(id) {
            const filtered = this.findAll().filter(t => t.id !== id);
            localStorage.setItem(STORAGE_KEY, JSON.stringify(filtered));
        }

        /**
         * Genera un nuovo ID per una task.
         * @returns {string} ID univoco generato
         */
        nextId() {
            return Task.generateId();
        }

        /**
         * Rimuove tutte le task dal localStorage.
         */
        clear() {
            localStorage.removeItem(STORAGE_KEY);
        }
    }

    App.Task2localStorage = Task2localStorage;

})(window.App = window.App || {});