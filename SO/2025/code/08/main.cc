/**
 * @file main.cc
 * @brief Programma principale con shell interattiva per ToyFS
 * 
 * Implementa una shell interattiva che permette all'utente di
 * interagire con il file system ToyFS attraverso comandi testuali.
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>

#include "ToyFS.hh"

// ------------------------------ File system ---------------------------------

// ------------------------------ Shell CLI -----------------------------------

/**
 * @brief Mostra l'elenco dei comandi disponibili nella shell
 */
void printHelp()
{
    std::cout << "\nComandi disponibili:\n"
              << "  ls                         - Elenca i file\n"
              << "  create <nome> <contenuto>  - Crea un file\n"
              << "  read   <nome>              - Mostra il contenuto\n"
              << "  rm     <nome>              - Elimina il file\n"
              << "  help                       - Mostra questo aiuto\n"
              << "  exit | quit                - Esce dalla shell\n\n";
}

/**
 * @brief Funzione principale che avvia la shell interattiva di ToyFS
 * 
 * Inizializza il file system e gestisce il ciclo di input/output della shell,
 * interpretando ed eseguendo i comandi inseriti dall'utente.
 * 
 * @return 0 in caso di terminazione normale
 */
int main()
{
    ToyFS fs;
    std::string line;
    std::cout << "ToyFS shell (digita 'help' per i comandi).\n";

    while (true)
    {
        std::cout << "toyfs> " << std::flush;
        if (!std::getline(std::cin, line))
            break;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd.empty())
            continue;

        if (cmd == "ls")
        {
            fs.listFiles();
        }
        else if (cmd == "create")
        {
            std::string name;
            iss >> name;
            std::string content;
            std::getline(iss, content);
            if (!content.empty() && content[0] == ' ')
                content.erase(0, 1);
            fs.createFile(name, content);
        }
        else if (cmd == "read")
        {
            std::string name;
            iss >> name;
            std::string data = fs.readFile(name);
            if (!data.empty())
                std::cout << data << "\n";
        }
        else if (cmd == "rm")
        {
            std::string name;
            iss >> name;
            fs.deleteFile(name);
        }
        else if (cmd == "help")
        {
            printHelp();
        }
        else if (cmd == "exit" || cmd == "quit")
        {
            break;
        }
        else
        {
            std::cerr << "Comando sconosciuto. Digita 'help' per elenco.\n";
        }
    }

    return 0;
}

