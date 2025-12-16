<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, OPTIONS, DELETE");
header("Content-Type: application/json; charset=UTF-8");

class TaskGateway extends Gateway
{
    private $db;
    
    public function __construct()
    {
        // Inizializzazione connessione database
        $this->db = new Database();
    }
    
    public function handle_request($parts)
    {
        // Gestione preflight request CORS
        if ($_SERVER['REQUEST_METHOD'] === "OPTIONS") {
            http_response_code(204);
            exit();
        }
        
        $method = $_SERVER['REQUEST_METHOD'];
        
        // Routing degli endpoint
        // $parts[0] = 'tasks'
        // $parts[1] = taskId (opzionale)
        
        try {
            switch ($method) {
                case 'GET':
                    if (isset($parts[1]) && !empty($parts[1])) {
                        // GET /tasks/:id - Recupera singola task
                        $this->getTaskById($parts[1]);
                    } else {
                        // GET /tasks - Lista tutte le task
                        $this->getAllTasks();
                    }
                    break;
                    
                case 'POST':
                    // POST /tasks - Creazione nuova task
                    $this->createTask();
                    break;
                    
                case 'PUT':
                    // PUT /tasks/:id - Modifica task esistente
                    if (!isset($parts[1]) || empty($parts[1])) {
                        $this->sendError("ID task mancante", 400);
                        return;
                    }
                    $this->updateTask($parts[1]);
                    break;
                    
                case 'DELETE':
                    // DELETE /tasks/:id - Eliminazione task
                    if (!isset($parts[1]) || empty($parts[1])) {
                        $this->sendError("ID task mancante", 400);
                        return;
                    }
                    $this->deleteTask($parts[1]);
                    break;
                    
                default:
                    $this->sendError("Metodo non supportato", 405);
                    break;
            }
        } catch (Exception $e) {
            $this->sendError("Errore del server: " . $e->getMessage(), 500);
        }
    }
    
    /**
     * GET /tasks
     * Recupera tutte le task dal database
     */
    private function getAllTasks()
    {
        $tasks = $this->db->getAllTasks();
        $this->sendResponse($tasks, 200);
    }
    
    /**
     * GET /tasks/:id
     * Recupera una singola task per ID
     */
    private function getTaskById($id)
    {
        $task = $this->db->getTaskById($id);
        
        if ($task) {
            $this->sendResponse($task, 200);
        } else {
            $this->sendError("Task non trovata", 404);
        }
    }
    
    /**
     * POST /tasks
     * Crea una nuova task
     */
    private function createTask()
    {
        $data = $this->getRequestBody();
        
        // Validazione campi obbligatori
        if (!isset($data['title']) || empty($data['title'])) {
            $this->sendError("Il campo 'title' è obbligatorio", 400);
            return;
        }
        
        if (!isset($data['description'])) {
            $data['description'] = '';
        }
        
        if (!isset($data['dueDate'])) {
            $data['dueDate'] = null;
        }
        
        if (!isset($data['priority'])) {
            $data['priority'] = 'medium';
        }
        
        if (!isset($data['status'])) {
            $data['status'] = 'pending';
        }
        
        // Creazione task nel database
        $taskId = $this->db->createTask(
            $data['title'],
            $data['description'],
            $data['dueDate'],
            $data['priority'],
            $data['status']
        );
        
        if ($taskId) {
            $newTask = $this->db->getTaskById($taskId);
            $this->sendResponse($newTask, 201);
        } else {
            $this->sendError("Impossibile creare la task", 500);
        }
    }
    
    /**
     * PUT /tasks/:id
     * Aggiorna una task esistente
     */
    private function updateTask($id)
    {
        // Verifica esistenza task
        $existingTask = $this->db->getTaskById($id);
        if (!$existingTask) {
            $this->sendError("Task non trovata", 404);
            return;
        }
        
        $data = $this->getRequestBody();
        
        // Merge con dati esistenti (patch update)
        $updatedData = [
            'title' => isset($data['title']) ? $data['title'] : $existingTask['title'],
            'description' => isset($data['description']) ? $data['description'] : $existingTask['description'],
            'dueDate' => isset($data['dueDate']) ? $data['dueDate'] : $existingTask['due_date'],
            'priority' => isset($data['priority']) ? $data['priority'] : $existingTask['priority'],
            'status' => isset($data['status']) ? $data['status'] : $existingTask['status']
        ];
        
        // Aggiornamento nel database
        $success = $this->db->updateTask(
            $id,
            $updatedData['title'],
            $updatedData['description'],
            $updatedData['dueDate'],
            $updatedData['priority'],
            $updatedData['status']
        );
        
        if ($success) {
            $updatedTask = $this->db->getTaskById($id);
            $this->sendResponse($updatedTask, 200);
        } else {
            $this->sendError("Impossibile aggiornare la task", 500);
        }
    }
    
    /**
     * DELETE /tasks/:id
     * Elimina una task
     */
    private function deleteTask($id)
    {
        // Verifica esistenza task
        $existingTask = $this->db->getTaskById($id);
        if (!$existingTask) {
            $this->sendError("Task non trovata", 404);
            return;
        }
        
        $success = $this->db->deleteTask($id);
        
        if ($success) {
            $this->sendResponse([
                'message' => 'Task eliminata con successo',
                'id' => $id
            ], 200);
        } else {
            $this->sendError("Impossibile eliminare la task", 500);
        }
    }
    
    /**
     * Recupera il body della richiesta e lo decodifica da JSON
     */
    private function getRequestBody()
    {
        $json = file_get_contents('php://input');
        $data = json_decode($json, true);
        
        if (json_last_error() !== JSON_ERROR_NONE) {
            $this->sendError("JSON non valido", 400);
            exit();
        }
        
        return $data ?: [];
    }
    
    /**
     * Invia una risposta di successo
     */
    private function sendResponse($data, $statusCode = 200)
    {
        http_response_code($statusCode);
        echo json_encode([
            'success' => true,
            'data' => $data
        ]);
    }
    
    /**
     * Invia una risposta di errore
     */
    private function sendError($message, $statusCode = 400)
    {
        http_response_code($statusCode);
        echo json_encode([
            'success' => false,
            'error' => $message
        ]);
    }
}
