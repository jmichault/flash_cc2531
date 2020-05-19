LDLIBS=-lwiringPi -lcrypt -lm -lrt
CFLAGS=-g
LDFLAGS=-g

all: cc_chipid cc_read cc_write cc_erase

cc_erase : cc_erase.o CCDebugger.o
	gcc $(LDFLAGS) -o $@ $^ $(LDLIBS)

cc_write : cc_write.o CCDebugger.o
	gcc $(LDFLAGS) -o $@ $^ $(LDLIBS)

cc_read : cc_read.o CCDebugger.o
	gcc $(LDFLAGS) -o $@ $^ $(LDLIBS)

cc_chipid : cc_chipid.o CCDebugger.o
	gcc $(LDFLAGS) -o $@ $^ $(LDLIBS)

cc_chipid.o : cc_chipid.c CCDebugger.h
	gcc $(CFLAGS) -c $*.c

CCDebugger.o : CCDebugger.c CCDebugger.h
	gcc $(CFLAGS) -c $*.c
