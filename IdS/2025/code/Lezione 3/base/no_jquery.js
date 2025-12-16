
// ottengo il riferimento al corpo della tabella dei task
const taskTableBody = document.getElementById('task-table-body');
const taskForm = document.getElementById('task-form');
const taskModal = document.getElementById('task-modal');
const openModalBtn = document.getElementById('open-modal-btn');
const closeModalBtn = document.getElementById('close-modal-btn');

// array per memorizzare i task
let tasks = [];


function renderTasks() {
    console.log("Rendering tasks");
    // svuoto il corpo della tabella
    taskTableBody.innerHTML = '';
    
    // ciclo attraverso i task e creo le righe della tabella
    tasks.forEach((task, index) => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td class="border border-black p-2">${task.name}</td>
            <td class="border border-black p-2">${task.description}</td>
            <td class="border border-black p-2">${task.dueDate}</td>
            <td class="border border-black p-2">${task.priority}</td>
            <td class="border border-black p-2">${task.status}</td>
        `;
        taskTableBody.appendChild(row);
    });
}


function addTask(event) {
    event.preventDefault(); // previene il comportamento di default del form

    // ottengo i valori dai campi del form
    const name = document.getElementById('task-name').value;
    const description = document.getElementById('task-desc').value;
    const dueDate = document.getElementById('task-due-date').value;
    const priority = document.getElementById('task-priority').value;
    const status = document.getElementById('task-status').value;

    // creo un nuovo task e lo aggiungo all'array
    const newTask = { name, description, dueDate, priority, status };
    tasks.push(newTask);

    // resetto il form
    taskForm.reset();

    // chiudo il modal
    closeModal();

    // aggiorno la visualizzazione dei task
    renderTasks();
}

function openModal() {
    taskModal.classList.remove('hidden');
}

function closeModal() {
    taskModal.classList.add('hidden');
    taskForm.reset();
}

function main() {
    console.log("Scrittura console")
    // aggiungo l'evento di submit al form
    taskForm.addEventListener('submit', addTask);

    // aggiungo gli eventi per aprire e chiudere il modal
    openModalBtn.addEventListener('click', openModal);
    closeModalBtn.addEventListener('click', closeModal);
    
    // chiudo il modal quando si clicca fuori dal contenuto
    taskModal.addEventListener('click', function (event) {
        if (event.target === taskModal) {
            closeModal();
        }
    });

    // inizializzo la visualizzazione dei task
    renderTasks();
}

// avvio l'applicazione quando il DOM è completamente caricato
main();
