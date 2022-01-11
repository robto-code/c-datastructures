CC=gcc
CFLAGS=-Wall -g -O2

TEST_DIR =test/
UTIL_DIR =util/
SRC_DIR=src/
BUILD_DIR=build/

INC_DIR=../$(UTIL_DIR)

UTILS=debug.h utilities.h
RB=ringbuffer.c ringbuffer.h

FILES=$(UTILS) $(RB)


.PHONY=all 
all: ringbuffer.o test

#DATASTRUCTS

build: ringbuffer.o

%.o: $(SRC_DIR)%.c
	cd $(SRC_DIR); $(CC) $(CFLAGS) -I $(INC_DIR) -c ../$^; mv $@ ../$(BUILD_DIR)

#TESTS

.PHONY = test
tester:
	cd $(TEST_DIR); make test

.PHONY=clean
clean:
	cd $(TEST_DIR); $(RM) *.o test
	cd $(BUILD_DIR); $(RM) *.o

