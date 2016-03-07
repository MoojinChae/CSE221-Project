CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-implicit-function-declaration -Wno-unused-variable -Wno-unused-but-set-variable
PROB1=file_cache_size.c
PROB2SEQ=file_read_seq.c
PROB2RAND=file_read_rand.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2SEQ=$(PROB2SEQ:.c=.o)
OBJECT2RAND=$(PROB2RAND:.c=.o)
OBJECTS=$(OBJECT1) $(OBJECT2SEQ) $(OBJECT2RAND)
EXECUTABLE=problem1 problem2_seq problem2_rand

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@ -lm

problem2_seq: $(OBJECT2SEQ)
	$(CC) $(OBJECT2SEQ) -o $@ -lm

problem2_rand: $(OBJECT2RAND)
	$(CC) $(OBJECT2RAND) -o $@ -lm

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
