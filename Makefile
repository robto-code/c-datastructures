CC=gcc
CFLAGS=-Wall -g -O2 -DDEBUG

TEST_DIR =test/
UTIL_DIR =util/
SRC_DIR=src/
BUILD_DIR=build/

INC_DIR=../$(UTIL_DIR)

UTILS=debug.h utilities.h
#SRC = ringbuffer.c linkedlist.c node.c ringbuffer.h linkedlist.h node.h
SRC = ringbuffer.c node.c ringbuffer.h node.h
BUILD = ringbuffer.o  node.o stack.o
BUILD_REQ = $(addprefix ${BUILD_DIR}, ${BUILD})
SRC_REQ = $(addprefix ${SRC_DIR}, ${SRC})

.PHONY=all 
all: $(BUILD) $(TEST_DIR)test

#DATASTRUCTS

build: $(BUILD)

%.o: $(SRC_DIR)%.c
	cd $(SRC_DIR); $(CC) $(CFLAGS) -I $(INC_DIR) -c ../$^; mv $@ ../$(BUILD_DIR)

#TESTS

.PHONY = tester
tester: $(TEST_DIR)test $(BUILD_REQ) $(SRC_REQ)

$(TEST_DIR)test: $(SRC_REQ)
	cd $(TEST_DIR); make test 

.PHONY=clean
clean:
	cd $(TEST_DIR); $(RM) *.o test
	cd $(BUILD_DIR); $(RM) *.o

