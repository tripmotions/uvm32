#include <string.h>
#include "unity.h"
#include "uvm32.h"
#include "../common/uvm32_common_custom.h"

#include "rom-header.h"

static uvm32_state_t vmst;
static uvm32_evt_t evt;

void setUp(void) {
    // runs before each test
    uvm32_init(&vmst);
    uvm32_load(&vmst, rom_bin, rom_bin_len);
}

void tearDown(void) {
}

void test_stackoverflow(void) {
    // run the vm
    while(1) {
        uvm32_run(&vmst, &evt, 100);
        if (evt.typ == UVM32_EVT_SYSCALL) {
            // ignore syscalls
        } else {
            TEST_ASSERT_EQUAL(UVM32_EVT_ERR, evt.typ);
            TEST_ASSERT_EQUAL(UVM32_ERR_INTERNAL_CORE, evt.data.err.errcode);
            break;
        }
    }
}


