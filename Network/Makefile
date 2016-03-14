CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-unused-variable -Wno-unused-function -Wno-uninitialized
COMMON=cpu.c
PROBLEM1=$(COMMON) roundtrip.c
PROBLEM2=$(COMMON) bandwidth.c
PROBLEM3=$(COMMON) setup_overhead.c
PROBLEM4=$(COMMON) teardown_overhead.c
OBJECT1=$(PROBLEM1:.c=.o)
OBJECT2=$(PROBLEM2:.c=.o)
OBJECT3=$(PROBLEM4:.c=.o)
OBJECT4=$(PROBLEM4:.c=.o)
OBJECTS = $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4)
EXECUTABLE = problem1 problem2 problem3 problem4

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@ -lm

problem2: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@ -lm

problem3: $(OBJECT3)
	$(CC) $(OBJECT3) -o $@ -lm

problem4: $(OBJECT4)
	$(CC) $(OBJECT4) -o $@ -lm

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
