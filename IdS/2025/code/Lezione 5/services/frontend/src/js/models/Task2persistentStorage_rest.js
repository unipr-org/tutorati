(function (App) {
    /**
     * URL base dell'API REST per la gestione delle task.
     * @constant {string}
     */
    const API_BASE_URL = "http://localhost:8080/tasks";

    /**
     * Classe che gestisce la persistenza delle task tramite API REST.
     * Implementa operazioni CRUD asincrone utilizzando chiamate AJAX.
     * @class
     */
    class Task2persistentStorage {
        /**
         * Crea una nuova istanza del gestore di persistenza REST.
         * Inizializza l'URL base per le chiamate API.
         */
        constructor() {
            this.baseUrl = API_BASE_URL;
        }

        /**
         * Carica tutte le task dal server tramite GET /api/tasks.
         * @async
         * @returns {Promise<Task[]>} Promise che risolve con l'array di task
         * @throws {Error} Se la richiesta HTTP fallisce
         */
        async findAll() {
            return new Promise((resolve, reject) => {
                $.ajax({
                    url: this.baseUrl,
                    method: 'GET',
                    dataType: 'json',
                    contentType: 'application/json',
                    success: (result) => {
                        try {
                            if (result.success && Array.isArray(result.data)) {
                                // Converte i dati dal database in oggetti Task
                                const tasks = result.data.map(taskData => {
                                    return App.Task.fromDTO({
                                        id: taskData.id,
                                        title: taskData.title,
                                        description: taskData.description,
                                        dueDate: taskData.due_date,
                                        priority: taskData.priority,
                                        status: taskData.status
                                    });
                                });
                                resolve(tasks);
                            } else {
                                resolve([]);
                            }
                        } catch (error) {
                            console.error("Errore nel parsing delle task:", error);
                            reject(error);
                        }
                    },
                    error: (xhr, status, error) => {
                        console.error("Errore nel caricamento delle task:", error);
                        reject(new Error(`HTTP error! status: ${xhr.status}`));
                    }
                });
            });
        }

        /**
         * Trova una task specifica per ID tramite GET /api/tasks/:id.
         * @async
         * @param {string|number} id - ID della task da cercare
         * @returns {Promise<Task|null>} Promise che risolve con la task trovata o null
         * @throws {Error} Se la richiesta HTTP fallisce (escluso 404)
         */
        async findById(id) {
            return new Promise((resolve, reject) => {
                $.ajax({
                    url: `${this.baseUrl}/${id}`,
                    method: 'GET',
                    dataType: 'json',
                    contentType: 'application/json',
                    success: (result) => {
                        if (result.success && result.data) {
                            const taskData = result.data;
                            const task = App.Task.fromDTO({
                                id: taskData.id,
                                title: taskData.title,
                                description: taskData.description,
                                dueDate: taskData.due_date,
                                priority: taskData.priority,
                                status: taskData.status
                            });
                            resolve(task);
                        } else {
                            resolve(null);
                        }
                    },
                    error: (xhr, status, error) => {
                        if (xhr.status === 404) {
                            resolve(null);
                        } else {
                            console.error("Errore nel recupero della task:", error);
                            reject(new Error(`HTTP error! status: ${xhr.status}`));
                        }
                    }
                });
            });
        }

        /**
         * Salva o aggiorna una task sul server.
         * Utilizza POST /api/tasks per nuove task o PUT /api/tasks/:id per aggiornamenti.
         * @async
         * @param {Task} task - Task da salvare o aggiornare
         * @returns {Promise<Task>} Promise che risolve con la task salvata (con ID assegnato)
         * @throws {Error} Se la richiesta HTTP fallisce
         */
        async save(task) {
            const dto = task.toDTO();

            // Conversione dei nomi delle proprietà per il backend (snake_case)
            const payload = {
                title: dto.title,
                description: dto.description,
                dueDate: dto.dueDate,  // Il backend si aspetta 'dueDate', convertirà in 'due_date'
                priority: dto.priority,
                status: dto.status
            };

            return new Promise((resolve, reject) => {
                let url = this.baseUrl;
                let method = 'POST';

                // Se la task ha un ID, è un update (PUT)
                if (dto.id) {
                    url = `${this.baseUrl}/${dto.id}`;
                    method = 'PUT';
                }

                $.ajax({
                    url: url,
                    method: method,
                    dataType: 'json',
                    contentType: 'application/json',
                    data: JSON.stringify(payload),
                    success: (result) => {
                        if (result.success && result.data) {
                            // Aggiorna l'oggetto task con i dati dal server (incluso l'ID generato)
                            const serverData = result.data;
                            task.setId(serverData.id);
                            resolve(task);
                        } else {
                            reject(new Error("Risposta del server non valida"));
                        }
                    },
                    error: (xhr, status, error) => {
                        let errorMessage = error;
                        try {
                            const errorData = JSON.parse(xhr.responseText);
                            errorMessage = errorData.error || error;
                        } catch (e) {
                            // Ignora errori di parsing
                        }
                        console.error("Errore nel salvataggio della task:", errorMessage);
                        reject(new Error(errorMessage));
                    }
                });
            });
        }

        /**
         * Elimina una task dal server tramite DELETE /api/tasks/:id.
         * @async
         * @param {string|number} id - ID della task da eliminare
         * @returns {Promise<boolean>} Promise che risolve con true se l'eliminazione ha successo
         * @throws {Error} Se la richiesta HTTP fallisce
         */
        async delete(id) {
            return new Promise((resolve, reject) => {
                $.ajax({
                    url: `${this.baseUrl}/${id}`,
                    method: 'DELETE',
                    dataType: 'json',
                    contentType: 'application/json',
                    success: (result) => {
                        resolve(result.success);
                    },
                    error: (xhr, status, error) => {
                        let errorMessage = error;
                        try {
                            const errorData = JSON.parse(xhr.responseText);
                            errorMessage = errorData.error || error;
                        } catch (e) {
                            // Ignora errori di parsing
                        }
                        console.error("Errore nell'eliminazione della task:", errorMessage);
                        reject(new Error(errorMessage));
                    }
                });
            });
        }

        /**
         * Genera un nuovo ID (non più necessario con auto-increment del DB).
         * Mantenuto per compatibilità con l'interfaccia di storage.
         * @returns {null} Ritorna null poiché l'ID viene generato dal database
         */
        nextId() {
            // Con il database, l'ID viene generato automaticamente
            // Questo metodo può restituire null o un ID temporaneo
            return null;
        }

        /**
         * Elimina tutte le task dal server.
         * Implementato lato client eliminando una task alla volta.
         * @async
         * @returns {Promise<boolean>} Promise che risolve con true se tutte le eliminazioni hanno successo
         * @throws {Error} Se una o più richieste HTTP falliscono
         */
        async clear() {
            return new Promise(async (resolve, reject) => {
                try {
                    const tasks = await this.findAll();
                    const deletePromises = tasks.map(task => this.delete(task.id));
                    await Promise.all(deletePromises);
                    resolve(true);
                } catch (error) {
                    console.error("Errore nella cancellazione di tutte le task:", error);
                    reject(error);
                }
            });
        }
    }

    App.Task2persistentStorage = Task2persistentStorage;

})(window.App = window.App || {});
