#include "uvm32_sys.h"
#include "uvm32_common_custom.h"
.section .initial_jump , "ax", %progbits
.global _start
_start:
la     a0, str
li a7, UVM32_SYSCALL_PRINTLN
ecall
li a7, UVM32_SYSCALL_HALT
ecall
str:
.ascii "Hi\0"
