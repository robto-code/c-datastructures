CC=gcc
CFLAGS=-Wall -g -O2

SRCS= rb_test.cpp node_test.cpp dnode_test.cpp stack_test.cpp test.cpp
OBJS= $(SRCS:%.cpp=%.o)
GTEST_DIR=../../google/
GLIBS=$(GTEST_DIR)gtest_lib/
SRC_DIR=../src/
UTIL_DIR=../util/
BUILD_DIR = ../build/
BUILD=$(addprefix ${BUILD_DIR}, ringbuffer.o node.o stack.o dnode.o)

LIB_LINKS = -L$(GLIBS) -lgtest -lstdc++ -lm -lpthread
INC_DIR = -I $(GTEST_DIR) -I $(SRC_DIR) -I $(UTIL_DIR)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC_DIR) -c $^

$(BUILD_DIR)%.o:
	cd ..; make build

test: $(OBJS) $(SRCS) $(BUILD)
	$(CC) $(CFLAGS) -I $(GTEST_DIR) -o $@ $(BUILD) $(OBJS) $(LIB_LINKS) 
