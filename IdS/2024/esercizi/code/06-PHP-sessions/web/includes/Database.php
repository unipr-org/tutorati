<?php
class Database
{
    private $host;
    private $username;
    private $password;
    private $dbname;
    private $connection;

    public function __construct()
    {
        $this->host = getenv('MYSQL_HOST');
        $this->username = getenv('MYSQL_USER');
        $this->password = getenv('MYSQL_PASSWORD');
        $this->dbname = getenv('MYSQL_DATABASE');


        $this->connect();
    }

    private function connect()
    {
        // echo "Tentativo di connessione a {$this->host}, {$this->username}, {$this->dbname}...<br>";
        $this->connection = new mysqli($this->host, $this->username, $this->password, $this->dbname);

        if ($this->connection->connect_error) {
            die("Connessione fallita: " . $this->connection->connect_error);
        }
    }

    public function query($sql, $params = [])
    {
        $stmt = $this->connection->prepare($sql);

        if ($params) {
            $types = str_repeat('s', count($params));
            $stmt->bind_param($types, ...$params);
        }

        $stmt->execute();
        $result = $stmt->get_result();
        $stmt->close();

        return $result;
    }

    public function close()
    {
        $this->connection->close();
    }
}
