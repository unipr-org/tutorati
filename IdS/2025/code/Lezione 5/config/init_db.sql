-- Creazione database per Task Manager
CREATE DATABASE IF NOT EXISTS todolist_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- Selezione database
USE todolist_db;

-- Creazione tabella tasks
CREATE TABLE IF NOT EXISTS tasks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    description TEXT,
    due_date DATE,
    priority ENUM('low', 'medium', 'high') DEFAULT 'medium',
    status ENUM('pending', 'in_progress', 'complete') DEFAULT 'pending',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    INDEX idx_status (status),
    INDEX idx_priority (priority),
    INDEX idx_due_date (due_date)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Inserimento dati di esempio (opzionale)
INSERT INTO tasks (title, description, due_date, priority, status) VALUES
('Studiare Ingegneria del Software', 'Rivedere design patterns e architetture software', '2025-12-15', 'high', 'in_progress'),
('Completare progetto Task Manager', 'Implementare REST API con PHP e SQL', '2025-12-20', 'high', 'pending'),
('Preparare presentazione', 'Creare slide per il tutorato', '2025-12-10', 'medium', 'complete');
