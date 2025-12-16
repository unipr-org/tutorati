
// array per memorizzare i task
let tasks = [];


function renderTasks() {
    // svuoto il corpo della tabella
    $('#task-table-body').empty();
    
    // ciclo attraverso i task e creo le righe della tabella
    tasks.forEach((task, index) => {
        const row = $('<tr>').html(`
            <td class="border border-black p-2">${task.name}</td>
            <td class="border border-black p-2">${task.description}</td>
            <td class="border border-black p-2">${task.dueDate}</td>
            <td class="border border-black p-2">${task.priority}</td>
            <td class="border border-black p-2">${task.status}</td>
        `);
        $('#task-table-body').append(row);
    });
}


function addTask(event) {
    event.preventDefault(); // previene il comportamento di default del form

    // ottengo i valori dai campi del form
    const name = $('#task-name').val();
    const description = $('#task-desc').val();
    const dueDate = $('#task-due-date').val();
    const priority = $('#task-priority').val();
    const status = $('#task-status').val();

    // creo un nuovo task e lo aggiungo all'array
    const newTask = { name: name, description: description, dueDate: dueDate, priority: priority, status: status };
    tasks.push(newTask);

    // resetto il form
    $('#task-form')[0].reset();

    // chiudo il modal
    closeModal();

    // aggiorno la visualizzazione dei task
    renderTasks();
}

function openModal() {
    $('#task-modal').removeClass('hidden');
}

function closeModal() {
    $('#task-modal').addClass('hidden');
    $('#task-form')[0].reset();
}

function main() {

    // aggiungo l'evento di submit al form
    $('#task-form').on('submit', addTask);

    // aggiungo gli eventi per aprire e chiudere il modal
    $('#open-modal-btn').on('click', openModal);
    $('#close-modal-btn').on('click', closeModal);
    
    // chiudo il modal quando si clicca fuori dal contenuto
    $('#task-modal').on('click', function(event) {
        if (event.target === this) {
            closeModal();
        }
    });

    // inizializzo la visualizzazione dei task
    renderTasks();
}

// avvio l'applicazione quando il DOM è completamente caricato
$(document).ready(main);
