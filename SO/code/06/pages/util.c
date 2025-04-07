#include "settings.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

// variabile esterna che contiene il nome del programma
extern const char *program_name;

// funzione per terminare il programma con un messaggio di errore formattato
__attribute__((noreturn, format(printf, 1, 2)))
void fatal(const char *format, ...) {
  va_list ap;

  // inizializzazione della lista di argomenti variabili
  va_start(ap, format);

  // stampa del nome del programma seguito dall'indicazione di errore fatale
  fprintf(stderr, "%s: FATAL: ", program_name);
  
  // stampa del messaggio di errore formattato
  vfprintf(stderr, format, ap);
  
  // aggiunta di un carattere di nuova linea
  fprintf(stderr, "\n");

  // pulizia della lista di argomenti variabili
  va_end(ap);
  
  // terminazione del programma con codice di errore
  exit(1);
}

// funzione che genera un numero casuale a 32 bit nell'intervallo [min, max]
uint32_t random32(uint32_t min, uint32_t max) {


  // calcolo del numero casuale con conversione a 64 bit per evitare overflow
  uint64_t r = (uint64_t) min + rand() / (RAND_MAX / (max - min + 1ULL) + 1ULL);
  
  // verifica che il risultato sia rappresentabile in 32 bit
  assert(r <= UINT32_MAX);
  
  // conversione e restituzione del risultato
  return (uint32_t) r;
}

// funzione che genera il prossimo riferimento a una pagina di memoria
uint32_t next_page_reference(void) {

  // array statico per memorizzare i riferimenti alle pagine generati
  static uint32_t
  
  next_page_reference_array[MAX_LOCALITY_SIZE * MAX_REFERENCES_IN_PAGE];
  // indice di fine dell'array di riferimenti
  static uint32_t next_page_reference_array_end = 0;
  
  // indice corrente nell'array di riferimenti
  static uint32_t next_page_reference_array_index = 0;

  // verifica se è necessario generare un nuovo batch di riferimenti
  if (next_page_reference_array_index == next_page_reference_array_end) {

    // determinazione casuale della dimensione della località
    uint32_t locality_size = random32(1, MAX_LOCALITY_SIZE);

    // array statico per memorizzare le pagine nella località corrente
    static uint32_t locality_array[MAX_LOCALITY_SIZE];
    // generazione delle pagine che formano la località
    for (uint32_t i = 0; i < locality_size; ++i) {
      locality_array[i] = random32(0, NUM_PAGES - 1U);
    }

    // reset dell'indice di riferimento
    next_page_reference_array_index = 0;
    // calcolo del numero totale di riferimenti da generare
    uint32_t page_references
      = locality_size * random32(1, MAX_REFERENCES_IN_PAGE);

    // generazione dei riferimenti alle pagine secondo il principio di località
    for (uint32_t j = 0; j < page_references; ++j) {

      #if NOISI_PAGE_REFERENCES
        if (random32(1, 10) == 1) {
          // 10% dei riferimenti sono rumore: pagina totalmente casuale
          next_page_reference_array[next_page_reference_array_index++]
            = random32(0, NUM_PAGES - 1U);
        } else {
          // 90% dei riferimenti seguono la località
          next_page_reference_array[next_page_reference_array_index++]
            = locality_array[random32(0, locality_size - 1U)];
        }
      #else
        next_page_reference_array[next_page_reference_array_index++]
          = locality_array[random32(0, MAX_LOCALITY_SIZE - 1U)];
      #endif
      }

    // aggiornamento dell'indice di fine e reset dell'indice corrente
    next_page_reference_array_end = next_page_reference_array_index;
    next_page_reference_array_index = 0;
  }

  // verifica che l'indice non superi la dimensione massima dell'array
  assert(next_page_reference_array_index
         < MAX_LOCALITY_SIZE * MAX_REFERENCES_IN_PAGE);
  // restituzione del prossimo riferimento a una pagina
  
  return next_page_reference_array[next_page_reference_array_index++];
}
