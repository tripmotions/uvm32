#include "uvm32_sys.h"
.section .initial_jump , "ax", %progbits
.global _start
.align 4
_start:
# sp is already setup by vm
sw	ra,12(sp)
jal	ra, main
#if 1
// rust will interpret the "#if 1" and "#include" as comments and ignore
// C, asm, zig will include the file below, which references a constant from uvm32_sys.h
#include "non-rust-crt0-hack.S"
#else
// only rust will see this
li a7, {UVM32_SYSCALL_HALT}
#endif
ecall
.section .data

