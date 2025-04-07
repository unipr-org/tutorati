#include "pra.h"
#include <stdio.h>

void pra_initialize(uint32_t num_refs) {
  (void) num_refs;
}

static uint64_t previous_logical_page = UINT64_MAX;
static uint32_t previous_repeat_count = 0U;

uint32_t pra_reference(uint32_t logical_page) {
  if (logical_page == previous_logical_page) {
    ++previous_repeat_count;
  }
  else {
    if (previous_logical_page != UINT64_MAX) {
      printf("%lu repeated %u times\n",
             previous_logical_page,
             previous_repeat_count);
    }
    previous_logical_page = logical_page;
    previous_repeat_count = 1U;
  }
  return 0U;
}

uint32_t pra_page_faults(void) {
  if (previous_logical_page != UINT64_MAX) {
    printf("%lu repeated %u times\n",
           previous_logical_page,
           previous_repeat_count);
  }
  return 0U;
}
