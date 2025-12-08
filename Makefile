all:
	cat uvm32/uvm32.h uvm32/uvm32.c uvm32/mini-rv32ima.h common/*.h > uvm32-single-file.c
	(cd host && make)
	(cd host-mini && make)
	(cd host-parallel && make)
	#(cd apps && make)  # do not build apps by default, as they require a variety of dev tools

clean:
	(cd host && make clean)
	(cd host-mini && make clean)
	(cd host-parallel && make clean)
	(cd apps && make clean)

