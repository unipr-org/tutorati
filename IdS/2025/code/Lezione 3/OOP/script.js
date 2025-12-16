// IIFE (Immediately Invoked Function Expression) per evitare variabili globali
(function () {
    // inizializzo le istanze necessarie
    const taskList = new App.TaskList();
    const taskStorage = new App.Task2localStorage();

    // carica le task salvate
    function loadTasksFromStorage() {
        const tasks = taskStorage.findAll();
        tasks.forEach(task => taskList.addTask(task));
        renderTasks();
    }

    // mostra le task nella tabella
    function renderTasks() {
        const tbody = document.getElementById('task-table-body');
        tbody.innerHTML = '';

        const tasks = taskList.getAllTasks();
        
        if (tasks.length === 0) {
            const emptyRow = document.createElement('tr');
            emptyRow.innerHTML = `
                <td colspan="5" class="border border-black p-2 text-center text-gray-500 italic">
                    Nessuna attività presente. Clicca sul pulsante + per aggiungerne una.
                </td>
            `;
            tbody.appendChild(emptyRow);
            return;
        }

        tasks.forEach(task => {
            const row = document.createElement('tr');
            row.dataset.taskId = task.id;
            
            // converto lo status in italiano
            const statusMap = {
                'complete': 'Completata',
                'incomplete': 'Non completata'
            };
            
            row.innerHTML = `
                <td class="border border-black p-2">${task.title}</td>
                <td class="border border-black p-2">${task.description}</td>
                <td class="border border-black p-2">${formatDate(task.dueDate)}</td>
                <td class="border border-black p-2">${task.priority}</td>
                <td class="border border-black p-2">${statusMap[task.status] || task.status}</td>
            `;
            
            tbody.appendChild(row);
        });
    }

    // formatto la data in formato italiano
    function formatDate(dateString) {
        if (!dateString) return '';
        const date = new Date(dateString);
        return date.toLocaleDateString('it-IT');
    }

    // apro il modal quando clicco sul bottone +
    $('#open-modal-btn').on('click', function() {
        $('#task-modal').removeClass('hidden');
        // reset del form
        $('#task-form')[0].reset();
    });

    $('#close-modal-btn').on('click', function() {
        $('#task-modal').addClass('hidden');
    });

    // chiusura modal cliccando fuori dall'area del form
    $('#task-modal').on('click', function(e) {
        if (e.target.id === 'task-modal') {
            $(this).addClass('hidden');
        }
    });

    // gestione submit del form
    $('#task-form').on('submit', function(e) {
        e.preventDefault();

        // lettura valori dal form
        const taskName = $('#task-name').val().trim();
        const taskDesc = $('#task-desc').val().trim();
        const taskDueDate = $('#task-due-date').val();
        const taskPriority = $('#task-priority').val();

        // controllo che tutti i campi siano compilati
        if (!taskName || !taskDesc || !taskDueDate || !taskPriority) {
            alert('Per favore compila tutti i campi obbligatori');
            return;
        }

        // creo una nuova task con un id univoco
        const taskId = App.Task.generateId();
        const newTask = new App.Task(taskId, taskName, taskDesc, taskDueDate, taskPriority);

        // aggiungo la task alla lista e la salvo
        taskList.addTask(newTask);
        taskStorage.save(newTask);

        // aggiorno la tabella
        renderTasks();

        // chiudo il modal e pulisco il form
        $('#task-modal').addClass('hidden');
        $('#task-form')[0].reset();

        // debug
        console.log('Task aggiunta con successo:', newTask.toDTO());
    });

    // chiudo il modal anche con ESC
    $(document).on('keydown', function(e) {
        if (e.key === 'Escape') {
            $('#task-modal').addClass('hidden');
        }
    });

    // cancello tutte le task
    $('#clear-all-btn').on('click', function() {
        if (taskList.getAllTasks().length === 0) {
            alert('Non ci sono task da cancellare');
            return;
        }

        if (confirm('Sei sicuro di voler cancellare tutte le attività? Questa operazione non può essere annullata.')) {
            taskStorage.clear();
            // svuoto anche la lista in memoria
            const tasks = taskList.getAllTasks();
            tasks.forEach(task => taskList.removeTask(task.id));
            renderTasks();
            console.log('Tutte le task sono state eliminate');
        }
    });

    // quando la pagina è pronta carico le task
    $(document).ready(function() {
        loadTasksFromStorage();
        console.log('App inizializzata correttamente');
    });

})();
