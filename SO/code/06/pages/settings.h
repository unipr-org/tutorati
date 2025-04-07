#ifndef settings_h
#define settings_h 1

#ifndef VERBOSE
#define VERBOSE 0
#endif

#ifndef NOISI_PAGE_REFERENCES
#define NOISI_PAGE_REFERENCES 0
#endif

#include <assert.h>
#include <stdint.h>

// numero di riferimenti di memoria da processare in un singolo quanto di tempo di simulazione
#ifndef NUM_REFERENCES_IN_QUANTUM
#define NUM_REFERENCES_IN_QUANTUM 1000U
#endif

// numero di frame di memoria fisica disponibili nel sistema
#ifndef NUM_FRAMES
#define NUM_FRAMES 128U
#endif

// numero totale di pagine di memoria virtuale nello spazio degli indirizzi
#ifndef NUM_PAGES
#define NUM_PAGES 2048U
#endif

// dimensione di ogni pagina di memoria in byte
#ifndef PAGE_SIZE
#define PAGE_SIZE 4096U
#endif

// tendenza ad effettuare un accesso ad un indirizzo di memoria vicino

// dimensione massima della finestra di località per i riferimenti di memoria
// controlla la tendenza ad accedere a indirizzi di memoria vicini
// impostata a metà del numero di frame disponibili
#ifndef MAX_LOCALITY_SIZE
#define MAX_LOCALITY_SIZE (NUM_FRAMES/2U)
#endif


// numero massimo di riferimenti all'interno di una singola pagina
// si assume che ogni riferimento occupi 8 byte (64 bit)
#ifndef MAX_REFERENCES_IN_PAGE
#define MAX_REFERENCES_IN_PAGE (PAGE_SIZE/8U)
#endif

static_assert(NUM_FRAMES <= NUM_PAGES,
              "NUM_FRAMES must be less than or equal NUM_PAGES");

static_assert(UINT32_MAX >= NUM_PAGES,
              "NUM_PAGES is too large for uint32_t");

#endif // ifndef settings_h
