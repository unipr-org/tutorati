#ifndef pra_h
#define pra_h 1

#include <stdint.h>

extern void pra_initialize(uint32_t num_refs);
extern uint32_t pra_reference(uint32_t logical_page);
extern uint32_t pra_page_faults(void);

#endif // ifndef pra_h
