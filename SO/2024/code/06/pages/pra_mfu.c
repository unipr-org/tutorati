#include "settings.h"
#include "pra.h"
#include <stdio.h>
#include <stdbool.h>

static uint32_t num_page_faults = 0U;

struct page_table_entry {
  uint32_t frame;
  bool valid;
  uint32_t use_count;  // contatore di utilizzo della pagina
};

static struct page_table_entry page_table[NUM_PAGES] = { 0 };

static uint32_t time = 0U;

static uint32_t next_free_frame = 0U;

void pra_initialize(uint32_t num_refs) {
  (void) num_refs;
}

uint32_t select_frame(uint32_t page_in_need) {
  if (next_free_frame < NUM_FRAMES) {
    return next_free_frame++;
  }

  // frames have been initially assigned: need to select a victim.
  uint32_t highest_use_count_page = 0U;
  uint32_t highest_use_count = 0U;
  for (uint32_t page = 0; page < NUM_PAGES; ++page) {
    if (page_table[page].valid && page_table[page].use_count > highest_use_count) {
      highest_use_count = page_table[page].use_count;
      highest_use_count_page = page;
    }
  }

#if VERBOSE
  printf("At time %u, assign frame %u from page %u (used %u times) to page %u\n",
         time,
         page_table[highest_use_count_page].frame,
         highest_use_count_page,
         highest_use_count,
         page_in_need);
#else
  (void) page_in_need;
#endif

  // highest_use_count_page is the index of the victim page.
  page_table[highest_use_count_page].valid = false;
  return page_table[highest_use_count_page].frame;
}

uint32_t pra_reference(uint32_t logical_page) {
  uint32_t physical_frame = 0U;

  if (page_table[logical_page].valid) {
    physical_frame = page_table[logical_page].frame;
    // Incremento il contatore di utilizzo
    page_table[logical_page].use_count++;
  }
  else {
    // fagefault fault.
    ++num_page_faults;
    physical_frame = select_frame(logical_page);
    page_table[logical_page].frame = physical_frame;
    page_table[logical_page].valid = true;

    // contatore di utilizzo a 1
    page_table[logical_page].use_count = 1U;
  }
  ++time;
  return physical_frame;
}

uint32_t pra_page_faults(void) {
  return num_page_faults;
}