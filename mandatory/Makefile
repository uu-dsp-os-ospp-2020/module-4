# Change to y to enable debugging support
DEBUG:=

CC=gcc
OS := $(shell uname)

CFLAGS=-std=c99 -D_XOPEN_SOURCE=600 -Wall -Wextra -I psem

ifeq ($(DEBUG), y)
	CFLAGS += -g
	LDFLAGS += -g
else
	CFLAGS += -O2
	LDFLAGS += -O2
endif

ifeq ($(OS), Linux)
	CFLAGS += -pthread
	LDLIBS += -pthread -lrt
endif

all: $(addprefix bin/, mutex psem_test rendezvous bounded_buffer_test bounded_buffer_stress_test)

bin/mutex: obj/mutex.o obj/timing.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

bin/psem_test: psem/psem.o obj/psem_test.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

bin/rendezvous: psem/psem.o obj/rendezvous.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

bin/bounded_buffer_test: psem/psem.o obj/bounded_buffer.o obj/bounded_buffer_test.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

bin/bounded_buffer_stress_test: psem/psem.o obj/bounded_buffer.o obj/bounded_buffer_stress_test.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@


bin/%: obj/%.o
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

psem/psem.o:
	cd psem; make

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	$(RM) obj/*.o bin/*
	cd psem; make clean

.PHONY: all clean
