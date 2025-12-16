#!/bin/bash
# avvio MySQL
service mariadb start

# creazione database e utente (opzionale)
mysql -e "CREATE DATABASE IF NOT EXISTS app_db;"
mysql -e "CREATE USER IF NOT EXISTS 'app_user'@'localhost' IDENTIFIED BY 'app_password';"
mysql -e "GRANT ALL PRIVILEGES ON app_db.* TO 'app_user'@'localhost';"
mysql -e "FLUSH PRIVILEGES;"

# avvio Apache in foreground
apache2ctl -D FOREGROUND