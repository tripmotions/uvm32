// Common to all target code

#include "uvm32_sys.h"

// Basic types
typedef long uint32_t;
typedef char uint8_t;
typedef int bool;
#define true 1
#define false 0

static uint32_t syscall(uint32_t id, uint32_t param) {
    register uint32_t a0 asm("a0") = (uint32_t)(param);
    register uint32_t a1 asm("a1");
    register uint32_t a7 asm("a7") = (uint32_t)(id);

    asm volatile (
        "ecall"
        : "=r"(a1) // output
        : "r"(a0), "r"(a7) // input
        : "memory"
    );
    return a1;
}

#define syscall_cast(id, x) syscall((uint32_t)id, (uint32_t)x)
#define println(x) syscall_cast(IOREQ_PRINTLN, x)
#define print(x) syscall_cast(IOREQ_PRINT, x)
#define printd(x) syscall_cast(IOREQ_PRINTD, x)
#define printx(x) syscall_cast(IOREQ_PRINTX, x)
#define millis() syscall_cast(IOREQ_MILLIS, 0)
#define printc() syscall_cast(IOREQ_PRINTC, 0)
#define getc() syscall_cast(IOREQ_GETC, 0)
#define yield() syscall_cast(IOREQ_YIELD, 0)

#include "uvm32_common_custom.h"

// provide main, with setup()/loop() flow
void setup(void);
bool loop(void);

#ifndef USE_MAIN
void main(void) {
    setup();
    while(loop()) {
        yield();
    }
}
#endif

