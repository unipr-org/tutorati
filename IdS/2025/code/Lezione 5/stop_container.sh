#!/bin/bash

echo "Arresto Task Manager Application..."

# Ferma container
echo "Fermando container..."
docker stop taskapp phpmyadmin 2>/dev/null || true

# Rimuovi container
echo "Rimuovendo container..."
docker rm taskapp phpmyadmin 2>/dev/null || true

echo ""
echo "Tutti i servizi sono stati fermati!"
echo ""
echo "Per riavviare: ./run_container.sh"
echo ""
