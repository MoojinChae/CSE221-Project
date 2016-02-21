CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-implicit-function-declaration -Wno-unused-variable -Wno-unused-but-set-variable
PROB1=ram_access.c
PROB2=ram_readwrite.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2=$(PROB2:.c=.o)
OBJECTS=$(OBJECT1) $(OBJECT2)
EXECUTABLE=problem1 problem2

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@ -lm

problem2: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)