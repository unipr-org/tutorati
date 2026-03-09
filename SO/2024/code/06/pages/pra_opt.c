#include "settings.h"
#include "pra.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static uint32_t num_page_faults = 0U;

struct page_table_entry {
  uint32_t frame;
  bool valid;
  uint32_t time_of_first_use;
};

static struct page_table_entry page_table[NUM_PAGES] = { 0 };

static uint32_t time = 0U;

static uint32_t next_free_frame = 0U;

static uint32_t *recorded_references;
static uint32_t num_recorded_references = 0U;

void pra_initialize(uint32_t num_refs) {
  recorded_references = malloc(num_refs * sizeof(uint32_t));
  if (recorded_references == NULL) {
    fatal("cannot allocate memory");
  }
  num_recorded_references = num_refs;
}

uint32_t select_frame(uint32_t page_in_need) {
  if (next_free_frame < NUM_FRAMES) {
    return next_free_frame++;
  }

  // All frames have been initially assigned: need to select a victim:
  // select the page that will be unused for the longest period of time
  // in the future.

  // Initialize time_of_first_use to 0 for all valid pages.
  for (uint32_t p = 0U; p < NUM_PAGES; ++p) {
    if (page_table[p].valid) {
      page_table[p].time_of_first_use = 0;
    }
  }

  // Set time_of_first_use for all valid pages used in the future.
  for (uint32_t t = time + 1U; t < num_recorded_references; ++t) {
    uint32_t p = recorded_references[t];
    if (page_table[p].valid && page_table[p].time_of_first_use == 0) {
      page_table[p].time_of_first_use = t;
    }
  }

  // Set victim_page to a valid one which will never be used in the future,
  // if any, or one with maximal time_of_first_use in the future.
  uint32_t victim_page = UINT32_MAX;
  uint32_t victim_page_time_of_first_use = 0U;
  for (uint32_t p = 0U; p < NUM_PAGES; ++p) {
    if (page_table[p].valid) {
      uint32_t p_time_of_first_use = page_table[p].time_of_first_use;
      if (p_time_of_first_use == 0U) {
        // Page p will never be used again: it is the ideal victim.
        victim_page = p;
        victim_page_time_of_first_use = UINT32_MAX;
        break;
      }
      if (p_time_of_first_use > victim_page_time_of_first_use) {
        victim_page = p;
        victim_page_time_of_first_use = p_time_of_first_use;
      }
    }
  }

  if (victim_page == UINT32_MAX) {
    // No valid page will be used in the future: just pick up any valid page.
    for (uint32_t p = 0U; p < NUM_PAGES; ++p) {
      if (page_table[p].valid) {
        victim_page = p;
        victim_page_time_of_first_use = page_table[p].time_of_first_use;
        break;
      }
    }
  }

#if VERBOSE
  printf("At time %u, assign frame %u from page %u (will be used first at time %u) to page %u\n",
         time,
         page_table[victim_page].frame,
         victim_page,
         victim_page_time_of_first_use,
         page_in_need);
#else
  (void) page_in_need;
  (void) victim_page_time_of_first_use;
#endif

  page_table[victim_page].valid = false;
  return page_table[victim_page].frame;
}

uint32_t pra_reference(uint32_t logical_page) {
  recorded_references[time] = logical_page;
  ++time;
  return 0U;
}

uint32_t pra_deferred_reference(uint32_t logical_page) {
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
  ++time;
  return physical_frame;
}

uint32_t pra_page_faults(void) {
  // Reset time.
  time = 0U;
  for (uint32_t i = 0; i < num_recorded_references; ++i) {
    (void) pra_deferred_reference(recorded_references[i]);
  }

  return num_page_faults;
}
