CC=gcc
CFLAGS=-c -Wall -g -std=gnu11 -O0 -Wno-attributes -Wno-unused-variable -Wno-unused-function -Wno-uninitialized
LDFLAGS=-lpthread
COMMON=cpu.c
PROB1=$(COMMON) problem1.c
PROB2=$(COMMON) problem2.c
PROB3=$(COMMON) problem3.c
PROB4PROCESS=$(COMMON) problem4_process.c
PROB4THREAD1=$(COMMON) problem4_thread1.c
PROB4THREAD2=$(COMMON) problem4_thread2.c
PROB5PROCESS=$(COMMON) problem5_process.c
PROB5THREAD=$(COMMON) problem5_thread.c
PIPE=$(COMMON) pipe.c
OBJECT1=$(PROB1:.c=.o)
OBJECT2=$(PROB2:.c=.o)
OBJECT3=$(PROB3:.c=.o)
OBJECT4PROCESS=$(PROB4PROCESS:.c=.o)
OBJECT4THREAD1=$(PROB4THREAD1:.c=.o)
OBJECT4THREAD2=$(PROB4THREAD2:.c=.o)
OBJECT5PROCESS=$(PROB5PROCESS:.c=.o)
OBJECT5THREAD=$(PROB5THREAD:.c=.o)
OBJECTPIPE=$(PIPE:.c=.o)	
OBJECTS = $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4PROCESS) $(OBJECT4THREAD1) $(OBJECT4THREAD2) $(OBJECT5PROCESS) $(OBJECT5THREAD) $(OBJECTPIPE)
EXECUTABLE = problem1 problem2 problem3 problem4_process problem4_thread1 problem4_thread2 problem5_process problem5_thread pipe

all: $(EXECUTABLE)

problem1: $(OBJECT1)
	$(CC) $(OBJECT1) -o $@

problem2: $(OBJECT2)
	$(CC) $(OBJECT2) -o $@

problem3: $(OBJECT3)
	$(CC) $(OBJECT3) -o $@

problem4_process: $(OBJECT4PROCESS)
	$(CC) $(OBJECT4PROCESS) $(LDFLAGS) -o $@

problem4_thread1: $(OBJECT4THREAD1)
	$(CC) $(OBJECT4THREAD1) $(LDFLAGS) -o $@

problem4_thread2: $(OBJECT4THREAD2)
	$(CC) $(OBJECT4THREAD2) $(LDFLAGS) -o $@

problem5_process: $(OBJECT5PROCESS)
	$(CC) $(OBJECT5PROCESS) $(LDFLAGS) -o $@ -lm

problem5_thread: $(OBJECT5THREAD)
	$(CC) $(OBJECT5THREAD) $(LDFLAGS) -o $@ -lm

pipe: $(OBJECTPIPE)
	$(CC) $(OBJECTPIPE) -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
