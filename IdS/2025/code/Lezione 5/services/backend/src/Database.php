<?php

class Database
{
    private $conn;
    private $host;
    private $db_name;
    private $username;
    private $password;
    
    public function __construct()
    {
        // Configurazione database (da ambiente o default)
        $this->host = getenv('DB_HOST') ?: 'localhost';
        $this->db_name = getenv('DB_NAME') ?: 'todolist_db';
        $this->username = getenv('DB_USER') ?: 'root';
        $this->password = getenv('DB_PASSWORD') ?: 'root';
        
        $this->connect();
    }
    
    /**
     * Stabilisce la connessione al database
     */
    private function connect()
    {
        $this->conn = null;
        
        try {
            $dsn = "mysql:host=" . $this->host . ";dbname=" . $this->db_name . ";charset=utf8mb4";
            $this->conn = new PDO($dsn, $this->username, $this->password);
            $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            $this->conn->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
        } catch(PDOException $e) {
            error_log("Errore connessione database: " . $e->getMessage());
            throw new Exception("Impossibile connettersi al database");
        }
    }
    
    /**
     * GET - Recupera tutte le task
     */
    public function getAllTasks()
    {
        $query = "SELECT * FROM tasks ORDER BY created_at DESC";
        
        try {
            $stmt = $this->conn->prepare($query);
            $stmt->execute();
            return $stmt->fetchAll();
        } catch(PDOException $e) {
            error_log("Errore getAllTasks: " . $e->getMessage());
            return [];
        }
    }
    
    /**
     * GET - Recupera una task per ID
     */
    public function getTaskById($id)
    {
        $query = "SELECT * FROM tasks WHERE id = :id LIMIT 1";
        
        try {
            $stmt = $this->conn->prepare($query);
            $stmt->bindParam(':id', $id);
            $stmt->execute();
            return $stmt->fetch();
        } catch(PDOException $e) {
            error_log("Errore getTaskById: " . $e->getMessage());
            return null;
        }
    }
    
    /**
     * POST - Crea una nuova task
     */
    public function createTask($title, $description, $dueDate, $priority, $status)
    {
        $query = "INSERT INTO tasks (title, description, due_date, priority, status) 
                  VALUES (:title, :description, :due_date, :priority, :status)";
        
        try {
            $stmt = $this->conn->prepare($query);
            
            // Sanitizzazione parametri
            $stmt->bindParam(':title', $title);
            $stmt->bindParam(':description', $description);
            $stmt->bindParam(':due_date', $dueDate);
            $stmt->bindParam(':priority', $priority);
            $stmt->bindParam(':status', $status);
            
            $stmt->execute();
            return $this->conn->lastInsertId();
        } catch(PDOException $e) {
            error_log("Errore createTask: " . $e->getMessage());
            return false;
        }
    }
    
    /**
     * PUT - Aggiorna una task esistente
     */
    public function updateTask($id, $title, $description, $dueDate, $priority, $status)
    {
        $query = "UPDATE tasks 
                  SET title = :title, 
                      description = :description, 
                      due_date = :due_date, 
                      priority = :priority, 
                      status = :status,
                      updated_at = NOW()
                  WHERE id = :id";
        
        try {
            $stmt = $this->conn->prepare($query);
            
            $stmt->bindParam(':id', $id);
            $stmt->bindParam(':title', $title);
            $stmt->bindParam(':description', $description);
            $stmt->bindParam(':due_date', $dueDate);
            $stmt->bindParam(':priority', $priority);
            $stmt->bindParam(':status', $status);
            
            $stmt->execute();
            return true;
        } catch(PDOException $e) {
            error_log("Errore updateTask: " . $e->getMessage());
            return false;
        }
    }
    
    /**
     * DELETE - Elimina una task
     */
    public function deleteTask($id)
    {
        $query = "DELETE FROM tasks WHERE id = :id";
        
        try {
            $stmt = $this->conn->prepare($query);
            $stmt->bindParam(':id', $id);
            $stmt->execute();
            return $stmt->rowCount() > 0;
        } catch(PDOException $e) {
            error_log("Errore deleteTask: " . $e->getMessage());
            return false;
        }
    }
    
    /**
     * Chiude la connessione
     */
    public function __destruct()
    {
        $this->conn = null;
    }
}
