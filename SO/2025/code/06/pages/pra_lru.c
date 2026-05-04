#include "settings.h"
#include "pra.h"
#include <stdio.h>
#include <stdbool.h>

static uint32_t num_page_faults = 0U;

struct page_table_entry {
  uint32_t frame;
  bool valid;
  uint32_t used_time;
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

  // All frames have been initially assigned: need to select a victim.
  uint32_t lowest_time_page = 0U;
  uint32_t lowest_time = UINT32_MAX;
  for (uint32_t page = 0; page < NUM_PAGES; ++page) {
    if (page_table[page].valid && page_table[page].used_time < lowest_time) {
      lowest_time = page_table[page].used_time;
      lowest_time_page = page;
    }
  }

#if VERBOSE
  printf("At time %u, assign frame %u from page %u (last used at time %u) to page %u\n",
         time,
         page_table[lowest_time_page].frame,
         lowest_time_page,
         lowest_time,
         page_in_need);
#else
  (void) page_in_need;
#endif

  // lowest_time_page is the index of the victim page.
  page_table[lowest_time_page].valid = false;
  return page_table[lowest_time_page].frame;
}

uint32_t pra_reference(uint32_t logical_page) {
  uint32_t physical_frame = 0U;

  if (page_table[logical_page].valid) {
    physical_frame = page_table[logical_page].frame;
  }
  else {
    // Page fault.
    ++num_page_faults;
    physical_frame = select_frame(logical_page);
    page_table[logical_page].frame = physical_frame;
    page_table[logical_page].valid = true;
  }
  page_table[logical_page].used_time = time;
  ++time;
  return physical_frame;
}

uint32_t pra_page_faults(void) {
  return num_page_faults;
}
