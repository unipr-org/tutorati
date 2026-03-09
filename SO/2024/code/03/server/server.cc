#include <iostream>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>

void handle_connection(int client_socket) {
    const int buffer_size = 1024;
    char buffer[buffer_size];
    bool running = true;

    std::string welcome = "Benvenuto nel server! Digita 'help' per la lista dei comandi disponibili.\n";
    std::string help_msg = "Comandi disponibili: help, date, close\n";
    std::string close_msg = "Chiusura della connessione...\n";
    std::string unknown = "Comando non riconosciuto. Usa 'help' per la lista dei comandi.\n";

    while (running) {
        write(client_socket, welcome.c_str(), welcome.size());

        int bytes_read = read(client_socket, buffer, buffer_size - 1);
        if (bytes_read <= 0) {
            std::cerr << "Errore nella lettura o client disconnesso.\n";
            break;
        }
        buffer[bytes_read] = '\0';
        std::string command(buffer);

        // rimozione di caratteri di newline o spazi in eccesso
        command.erase(command.find_last_not_of(" \n\r\t") + 1);

        if (command == "help") {
            write(client_socket, help_msg.c_str(), help_msg.size());
        }
        else if (command == "date") {
            std::time_t now = std::time(nullptr);
            std::string date_str = std::string("Data corrente: ") + std::ctime(&now);
            write(client_socket, date_str.c_str(), date_str.size());
        }
        else if (command == "close") {
            write(client_socket, close_msg.c_str(), close_msg.size());
            running = false;
        }
        else {
            write(client_socket, unknown.c_str(), unknown.size());
        }
    }

    close(client_socket);
}

int main() {
    // Creazione del socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Impossibile creare il socket.\n";
        return 1;
    }

    // configurazione del server dell'indirizzo del server
    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // binding socket all'indirizzo e porta specificati
    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind fallito.\n";
        close(server_socket);
        return 1;
    }

    // messa in ascolto del server
    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listen fallito.\n";
        close(server_socket);
        return 1;
    }

    std::cout << "Server in ascolto sulla porta 8080...\n";

    // ciclo per accettare le connessioni in entrata
    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Accept fallito.\n";
            continue;
        }
        std::cout << "Nuovo client connesso da: " << inet_ntoa(client_addr.sin_addr) << "\n";

        // crazione di un thread per gestire la comunicazione con il client
        std::thread t(handle_connection, client_socket);

        // esecuzione in background
        t.detach();
    }

    close(server_socket);
    return 0;
}
