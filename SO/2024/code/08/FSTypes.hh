/**
 * @file FSTypes.hh
 * @brief Definizione delle strutture dati base del file system
 */
#include <cstdint>
#include <cstring>


/** Dimensione di un blocco dati in byte */
constexpr uint32_t BLOCK_SIZE = 512;  // Dimensione di un blocco dati
/** Numero massimo di inode supportati dal filesystem */
constexpr uint32_t MAX_INODES = 64;   // Numero massimo di inode
/** Numero massimo di blocchi dati supportati dal filesystem */
constexpr uint32_t MAX_BLOCKS = 1024; // Numero massimo di blocchi dati


/**
 * @brief Struttura del SuperBlock che contiene i metadati principali del filesystem
 */
struct SuperBlock
{
    uint32_t blockSize;      // Dimensione blocchi
    uint32_t inodeCount;     // Numero totale di inode
    uint32_t dataBlockCount; // Numero totale di blocchi dati
};

/**
 * @brief Struttura Inode che rappresenta i metadati di un file
 * 
 * Ogni inode contiene le informazioni di un singolo file nel filesystem
 */
struct Inode
{
    bool used;           // true se l'inode è in uso
    uint32_t size;       // Dimensione del file (byte)
    uint32_t blockIndex; // Blocco dati diretto (uno solo, modello semplificato)
    char name[32];       // Nome del file

    /**
     * @brief Costruttore che inizializza un inode vuoto
     */
    Inode() : used(false), size(0), blockIndex(0)
    {
        std::memset(name, 0, sizeof(name));
    }
};