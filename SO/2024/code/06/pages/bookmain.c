#include "util.h"
#include "pra.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const char* program_name;

__attribute__((noreturn))
void usage(void) {
  fprintf(stderr, "usage: %s\n", program_name);
  exit(1);
}

int main(int argc, char *argv[]) {
  program_name = argv[0];

  if (argc != 1) {
    usage();
  }

  uint32_t page_refs[] = {
    7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1
  };

  const uint32_t num_refs = sizeof(page_refs) / sizeof(page_refs[0]);
  pra_initialize(num_refs);

  for (uint32_t num_ref = 0; num_ref < num_refs; ++num_ref) {
    pra_reference(page_refs[num_ref]);
  }

  printf("page_faults = %u\n", pra_page_faults());
}
