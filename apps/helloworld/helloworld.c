#define USE_MAIN
#include "uvm32_target.h"

void main(void) {
    for (int i=0;i<10;i++) {
        printd(i);
    }
#if 0
    uint32_t c;
    while(c = getc()) {
        if (c != 0xFFFFFFFF) {
            print("Got: ");
            printx(c);
            println("");
        }
    }
#endif
}

