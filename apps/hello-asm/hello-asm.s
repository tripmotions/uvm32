.section .initial_jump , "ax", %progbits
.global _start
_start:
la     a5, str
csrrw zero,0x13b,a5 # println
csrwi 0x138,0 # halt
str:
.ascii "Hi"

