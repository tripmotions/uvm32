all:
	gcc -Wall -DUVM32_MEMORY_SIZE=512 -O2 -I../uvm32 -I../common -o host-mini ../uvm32/uvm32.c host-mini.c

clean:
	rm -f host-mini
