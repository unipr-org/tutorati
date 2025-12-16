#!/bin/bash

docker build -f Dockerfile.simple -t taskapp-image .

docker run -d \
    -p 80:80 -p 8080:8080 -p 3306:3306 \
    --name taskapp \
    -v "$(pwd)/services/frontend/src:/var/www/html" \
    -v "$(pwd)/services/backend/src:/var/www/api" \
    -v "$(pwd)/storage:/var/lib/mysql" \
    taskapp-image