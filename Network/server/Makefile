CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-unused-variable -Wno-unused-function -Wno-uninitialized
SERVER_RT=$(COMMON) roundtrip_server.c
SERVER_BW=$(COMMON) bandwidth_server.c
OBJECT1=$(SERVER_RT:.c=.o)
OBJECT2=$(SERVER_BW:.c=.o)
OBJECTS = $(OBJECT1) $(OBJECT2)
EXECUTABLE = server_rt server_bw

all: $(EXECUTABLE)

server_rt: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@ -lm

server_bw: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@ -lm

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
