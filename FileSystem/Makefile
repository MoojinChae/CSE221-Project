CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-implicit-function-declaration -Wno-unused-variable -Wno-unused-but-set-variable
PROB1=file_cache_size.c
PROB2SEQ=file_read_seq.c
PROB2RAND=file_read_rand.c
PROB3=nfs_client.c
PROB4=file_contention.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2SEQ=$(PROB2SEQ:.c=.o)
OBJECT2RAND=$(PROB2RAND:.c=.o)
OBJECT3=$(PROB3:.c=.o)
OBJECT4=$(PROB4:.c=.o)
OBJECTS=$(OBJECT1) $(OBJECT2SEQ) $(OBJECT2RAND) $(OBJECT3) $(OBJECT4)
EXECUTABLE=problem1 problem2_seq problem2_rand problem3_client problem4

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@ -lm

problem2_seq: $(OBJECT2SEQ)
	$(CC) $(OBJECT2SEQ) -o $@ -lm

problem2_rand: $(OBJECT2RAND)
	$(CC) $(OBJECT2RAND) -o $@ -lm

problem3_client: $(OBJECT3)
	$(CC) $(OBJECT3) -o $@ -lm

problem4: $(OBJECT4)
	$(CC) $(OBJECT4) -o $@ -lm

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
