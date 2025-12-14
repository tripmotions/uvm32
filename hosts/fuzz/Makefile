TOPDIR=../..
all:
	afl-clang-fast -g3 -fsanitize=address,undefined -Wall -DUVM32_MEMORY_SIZE=4096 -I${TOPDIR}/uvm32 -I${TOPDIR}/common -o host-fuzz ${TOPDIR}/uvm32/uvm32.c fuzz.c
	afl-fuzz -i${TOPDIR}/precompiled -oo ./host-fuzz

clean:
	rm -rf host-fuzz o host-fuzz.dSYM


