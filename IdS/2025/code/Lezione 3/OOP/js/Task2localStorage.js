(function (App) {
    const STORAGE_KEY = "tasks";

    class Task2localStorage {
        constructor() {}

        // carica tutte le task da localStorage
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

        // trova una task per id
        findById(id) {
            const all = this.findAll();
            return all.find(t => t.id === id) || null;
        }

        // salva o aggiorna una task
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

        // elimina una task per id
        delete(id) {
            const filtered = this.findAll().filter(t => t.id !== id);
            localStorage.setItem(STORAGE_KEY, JSON.stringify(filtered));
        }

        nextId() {
            return Task.generateId();
        }

        clear() {
            localStorage.removeItem(STORAGE_KEY);
        }
    }

    App.Task2localStorage = Task2localStorage;

})(window.App = window.App || {});