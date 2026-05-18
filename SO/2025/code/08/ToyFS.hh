/**
 * @file ToyFS.hh
 * @brief Implementazione di un file system semplificato per scopi didattici
 * 
 * ToyFS implementa un file system minimale in memoria con supporto per
 * operazioni di base come creazione, lettura ed eliminazione di file.
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>

#include "FSTypes.hh"

/**
 * @class ToyFS
 * @brief Classe principale che implementa il file system toy
 * 
 * Gestisce una struttura di file system semplificata con un SuperBlock,
 * una tabella di inode e blocchi dati, tutto mantenuto in memoria RAM.
 */
class ToyFS
{
    SuperBlock sb{};                           // Superblock
    std::vector<Inode> inodes;                 // Tabella inode
    std::vector<std::vector<char>> dataBlocks; // "Disco" in RAM

    /**
     * @brief Cerca un inode per nome
     * @param name Nome del file da cercare
     * @return Puntatore all'inode trovato o nullptr se non esiste
     */
    Inode *findInode(const std::string &name)
    {
        for (auto &inode : inodes)
        {
            if (inode.used && name == inode.name)
                return &inode;
        }
        return nullptr;
    }

    /**
     * @brief Alloca un inode libero dalla tabella
     * @return Puntatore all'inode allocato o nullptr se non ci sono inode disponibili
     */
    Inode *allocateInode()
    {
        for (auto &inode : inodes)
        {
            if (!inode.used)
            {
                inode.used = true;
                return &inode;
            }
        }
        return nullptr;
    }

    /**
     * @brief Alloca un blocco dati libero
     * @return Indice del blocco allocato o -1 se non ci sono blocchi disponibili
     */
    int allocateBlock()
    {
        for (uint32_t i = 0; i < dataBlocks.size(); ++i)
        {
            if (std::all_of(dataBlocks[i].begin(), dataBlocks[i].end(), [](char c)
                            { return c == 0; }))
                return static_cast<int>(i);
        }
        return -1;
    }

public:
    /**
     * @brief Costruttore che inizializza il file system
     * 
     * Inizializza il SuperBlock, alloca la tabella degli inode e i blocchi dati
     */
    ToyFS()
    {
        sb.blockSize = BLOCK_SIZE;
        sb.inodeCount = MAX_INODES;
        sb.dataBlockCount = MAX_BLOCKS;
        inodes.resize(MAX_INODES);
        dataBlocks.resize(MAX_BLOCKS, std::vector<char>(BLOCK_SIZE, 0));
    }

    /**
     * @brief Crea un nuovo file nel file system
     * 
     * @param name Nome del file da creare
     * @param content Contenuto del file
     * @return true se la creazione è avvenuta con successo, false altrimenti
     */
    bool createFile(const std::string &name, const std::string &content)
    {
        if (name.empty() || name.size() >= 32)
        {
            std::cerr << "Nome non valido (1-31 caratteri)\n";
            return false;
        }

        if (findInode(name))
        {
            std::cerr << "File già esistente\n";
            return false;
        }

        Inode *inode = allocateInode();
        int blk = allocateBlock();
        if (!inode || blk < 0)
        {
            std::cerr << "Spazio finito per inode o blocchi\n";
            return false;
        }

        inode->size = std::min<size_t>(content.size(), BLOCK_SIZE);
        inode->blockIndex = blk;
        
        std::strcpy(inode->name, name.c_str());
        std::fill(dataBlocks[blk].begin(), dataBlocks[blk].end(), 0);
        std::copy_n(content.begin(), inode->size, dataBlocks[blk].begin());
        
        return true;
    }

    /**
     * @brief Legge il contenuto di un file
     * 
     * @param name Nome del file da leggere
     * @return Il contenuto del file come stringa o stringa vuota in caso di errore
     */
    std::string readFile(const std::string &name)
    {
        Inode *inode = findInode(name);
        if (!inode)
        {
            std::cerr << "File non trovato\n";
            return {};
        }
        return std::string(dataBlocks[inode->blockIndex].begin(),
                           dataBlocks[inode->blockIndex].begin() + inode->size);
    }

    /**
     * @brief Elimina un file dal file system
     * 
     * @param name Nome del file da eliminare
     * @return true se l'eliminazione è avvenuta con successo, false altrimenti
     */
    bool deleteFile(const std::string &name)
    {
        Inode *inode = findInode(name);
        if (!inode)
        {
            std::cerr << "File non trovato\n";
            return false;
        }
        std::fill(dataBlocks[inode->blockIndex].begin(), dataBlocks[inode->blockIndex].end(), 0);
        *inode = Inode{}; // reset inode
        return true;
    }

    /**
     * @brief Visualizza l'elenco dei file presenti nel file system
     * 
     * Mostra una tabella con i nomi dei file, la loro dimensione e il blocco di dati assegnato
     */
    void listFiles() const
    {
        std::cout << "\n"
                  << std::left << std::setw(20) << "Nome" << "Dimensione  Blocco" << "\n";
        std::cout << std::string(38, '-') << "\n";
        for (const auto &inode : inodes)
        {
            if (inode.used)
            {
                std::cout << std::left << std::setw(20) << inode.name
                          << std::setw(10) << inode.size << inode.blockIndex << "\n";
            }
        }
    }
};
