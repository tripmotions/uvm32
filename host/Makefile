all:
	gcc -Wall -pedantic -std=c99 -O2 -DUVM32_MEMORY_SIZE=32768 -I../uvm32 -I../common -o host ../uvm32/uvm32.c host.c

clean:
	rm -f host
