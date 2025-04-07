#ifndef util_h
#define util_h 1

#include <stdint.h>
#include <stdarg.h>

extern uint32_t next_page_reference(void);
__attribute__((noreturn, format(printf, 1, 2)))
extern void fatal(const char *format, ...);

#endif // ifndef util_h
