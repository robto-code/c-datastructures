CC=gcc
CFLAGS=-Wall -g -O2 -DDEBUG

TEST_DIR =test/
UTIL_DIR =util/
SRC_DIR=src/
BUILD_DIR=build/

INC_DIR=../$(UTIL_DIR)

UTILS=debug.h utilities.h
SRC = ringbuffer.c linkedlist.c node.c ringbuffer.h linkedlist.h node.h

FILES=$(UTILS) $(RB)


.PHONY=all 
all: ringbuffer.o $(TEST_DIR)test

#DATASTRUCTS

build: ringbuffer.o linkedlist.o node.o

%.o: $(SRC_DIR)%.c
	cd $(SRC_DIR); $(CC) $(CFLAGS) -I $(INC_DIR) -c ../$^; mv $@ ../$(BUILD_DIR)

#TESTS

.PHONY = tester
tester: $(TEST_DIR)test; 

$(TEST_DIR)test:
	cd $(TEST_DIR); make test 

.PHONY=clean
clean:
	cd $(TEST_DIR); $(RM) *.o test
	cd $(BUILD_DIR); $(RM) *.o

