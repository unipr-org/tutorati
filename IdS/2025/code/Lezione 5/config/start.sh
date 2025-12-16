#!/bin/bash

# Variabili d'ambiente con valori di default
MYSQL_ROOT_PASSWORD="${MYSQL_ROOT_PASSWORD:-root}"

# Inizializza database MySQL se non esiste
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Inizializzazione database MySQL..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# Avvio MariaDB
echo "Avvio MariaDB..."
service mariadb start

# Attendi che MySQL sia pronto
echo "Attendo che MySQL sia pronto..."
for i in {1..30}; do
    if mysqladmin ping &>/dev/null; then
        echo "MySQL è pronto!"
        break
    fi
    echo "Attesa MySQL... ($i/30)"
    sleep 1
done

# Imposta password root se non già impostata
echo "Configurazione password MySQL..."
mysql -u root <<-EOSQL
    -- Imposta password root per localhost
    ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

    -- Crea utente root per connessioni remote (se non esiste)
    CREATE USER IF NOT EXISTS 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
    GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;

    FLUSH PRIVILEGES;
EOSQL

# Esegui script di inizializzazione database applicativo
if [ -f /config/init_db.sql ]; then
    echo "Esecuzione script inizializzazione database applicativo..."
    mysql -u root -p"${MYSQL_ROOT_PASSWORD}" < /config/init_db.sql
    echo "Database applicativo inizializzato con successo"
fi

# Avvio Apache in foreground
echo "Avvio Apache..."
apache2ctl -D FOREGROUND