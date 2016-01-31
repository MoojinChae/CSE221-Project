CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-unused-variable -Wno-unused-function
PROB1=cpu.c problem1.c
PROB2=cpu.c problem2.c
PROB3=cpu.c problem3.c
PROB4=cpu.c problem4.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2=$(PROB2:.c=.o)
OBJECT3=$(PROB3:.c=.o)
OBJECT4=$(PROB4:.c=.o)
OBJECTS = $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4)
EXECUTABLE = problem1 problem2 problem3 problem4

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@

problem2: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@

problem3: $(OBJECT3)
	$(CC) $(OBJECT3) -o $@

problem4: $(OBJECT4)
	$(CC) $(OBJECT4) -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
