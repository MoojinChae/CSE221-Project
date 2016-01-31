CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-unused-variable -Wno-unused-function
COMMON=cpu.c
PROB1=$(COMMON) problem1.c
PROB2=$(COMMON) problem2.c
PROB3=$(COMMON) problem3.c
PROB4=$(COMMON) problem4.c
PROB5=$(COMMON) problem5.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2=$(PROB2:.c=.o)
OBJECT3=$(PROB3:.c=.o)
OBJECT4=$(PROB4:.c=.o)
OBJECT5=$(PROB5:.c=.o)
OBJECTS = $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4) $(OBJECT5)
EXECUTABLE = problem1 problem2 problem3 problem4 problem5

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@

problem2: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@

problem3: $(OBJECT3)
	$(CC) $(OBJECT3) -o $@

problem4: $(OBJECT4)
	$(CC) $(OBJECT4) -o $@

problem5: $(OBJECT5)
	$(CC) $(OBJECT5) -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
