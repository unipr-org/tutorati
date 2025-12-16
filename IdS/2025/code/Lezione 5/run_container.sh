#!/bin/bash

echo "Avvio Task Manager Application..."

# Pulisci container esistenti se presenti
echo "Pulizia container esistenti..."
docker rm -f taskapp 2>/dev/null || true
docker rm -f phpmyadmin 2>/dev/null || true

# Crea network per comunicazione tra container (se non esiste)
echo "Creazione network Docker..."
docker network create taskapp-network 2>/dev/null || echo "Network già esistente"

# Password MySQL
MYSQL_ROOT_PASSWORD="root"

# Build immagine principale
echo "Build immagine Task Manager..."
docker build --no-cache -f Dockerfile.simple -t taskapp-image .

# Run container principale
echo "Avvio container Task Manager..."
docker run -d \
    -p 80:80 \
    -p 8080:8080 \
    -p 3306:3306 \
    --name taskapp \
    --network taskapp-network \
    -e MYSQL_ROOT_PASSWORD="${MYSQL_ROOT_PASSWORD}" \
    -e DB_HOST="localhost" \
    -e DB_NAME="todolist_db" \
    -e DB_USER="root" \
    -e DB_PASSWORD="${MYSQL_ROOT_PASSWORD}" \
    -v "$(pwd)/services/frontend/src:/var/www/html" \
    -v "$(pwd)/services/backend/src:/var/www/api" \
    -v "$(pwd)/storage:/var/lib/mysql" \
    taskapp-image

# Attendi che MySQL sia pronto
echo "Attendo che MySQL sia pronto..."
sleep 10

# Run phpMyAdmin
echo "Avvio phpMyAdmin..."
docker run -d \
    --name phpmyadmin \
    --network taskapp-network \
    -e PMA_HOST=taskapp \
    -e PMA_PORT=3306 \
    -p 8081:80 \
    phpmyadmin/phpmyadmin:latest

echo ""
echo "Tutti i servizi sono stati avviati!"
echo ""
echo "Servizi disponibili:"
echo "  Frontend:      http://localhost:80"
echo "  Backend API:   http://localhost:8080/tasks"
echo "  phpMyAdmin:    http://localhost:8081"
echo "  MySQL:         localhost:3306"
echo ""
echo "Credenziali MySQL:"
echo "  User:     root"
echo "  Password: root"
echo "  Database: todolist_db"
echo ""
echo "Comandi utili:"
echo "  docker logs -f taskapp      # Logs applicazione"
echo "  docker logs -f phpmyadmin   # Logs phpMyAdmin"
echo "  docker exec -it taskapp bash # Shell nel container"
echo "  docker stop taskapp phpmyadmin # Ferma servizi"
echo ""