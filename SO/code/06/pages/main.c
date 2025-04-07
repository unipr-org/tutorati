#include "util.h"
#include "pra.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// variabile globale che memorizza il nome del programma
const char* program_name;

__attribute__((noreturn))
void usage(void) {
  // stampa un messaggio di errore con le istruzioni per l'uso corretto del programma
  fprintf(stderr, "usage: %s N, where 0 <= N < %u\n",
          program_name, UINT32_MAX);
  exit(1);
}

int main(int argc, char *argv[]) {

  // inizializzazione del nome del programma con il primo argomento
  program_name = argv[0];

  // verifica che il numero di argomenti sia corretto
  if (argc != 2) {
    usage();
  }

  // conversione dell'argomento da stringa a numero
  char* endptr;
  long N = strtol(argv[1], &endptr, 10);
  // controllo della validità del numero inserito
  if (*endptr != '\0' || N < 0 || N >= UINT32_MAX) {
    usage();
  }

  uint32_t num_refs = N;

  // inizializzazione dell'algoritmo di page replacement
  pra_initialize(num_refs);

  // simulazione di N riferimenti a pagine di memoria
  for (uint32_t num_ref = 0; num_ref < num_refs; ++num_ref) {
    pra_reference(next_page_reference());
  }

  // stampa del numero totale di page fault verificatisi
  printf("page_faults = %u\n", pra_page_faults());
}
