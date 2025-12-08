#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uvm32.h"
#include "../common/uvm32_common_custom.h"

// Precompiled binary program to print integers
// This code expects to print via syscall 0x13C (IOREQ_PRINTD in common/uvm32_common_custom.h)
uint8_t rom[] = {
    0x23, 0x26, 0x11, 0x00, 0xef, 0x00, 0x00, 0x01, 0x93, 0x08, 0x80, 0x13,
    0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x05, 0x00, 0x00,
    0x93, 0x07, 0xa0, 0x00, 0x93, 0x08, 0xc0, 0x13, 0x73, 0x00, 0x00, 0x00,
    0x13, 0x05, 0x15, 0x00, 0xe3, 0x1a, 0xf5, 0xfe, 0x67, 0x80, 0x00, 0x00
};

// Create an identifier for our host handler
typedef enum {
    F_PRINTD,
} f_code_t;

// Map VM ioreq IOREQ_PRINTD (0x13C) to F_PRINTD, tell VM to expect write of a U32
const uvm32_mapping_t env[] = {
    { .syscall = IOREQ_PRINTD, .typ = IOREQ_TYP_U32_WR, .code = F_PRINTD },
};

int main(int argc, char *argv[]) {
    uvm32_state_t vmst;
    uvm32_evt_t evt;
    bool isrunning = true;

    uvm32_init(&vmst, env, sizeof(env) / sizeof(env[0]));
    uvm32_load(&vmst, rom, sizeof(rom));

    while(isrunning) {
        uvm32_run(&vmst, &evt, 100);   // num instructions before vm considered hung

        switch(evt.typ) {
            case UVM32_EVT_END:
                isrunning = false;
            break;
            case UVM32_EVT_IOREQ:    // vm has paused to handle IOREQ
                switch((f_code_t)evt.data.ioreq.code) {
                    case F_PRINTD:
                        // Type of F_PRINTD is IOREQ_TYP_U32_WR, so expect value in evt.data.ioreq.val.u32
                        printf("%d\n", evt.data.ioreq.val.u32);
                    break;
                }
            break;
            default:
            break;
        }
    }

    return 0;
}
