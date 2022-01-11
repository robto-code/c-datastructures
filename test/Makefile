CC=gcc
CFLAGS=-Wall -g -O2

SRCS= *.cpp
OBJS= $(SRCS:%.cpp=%.o)
GTEST_DIR=../../google/
GLIBS=$(GTEST_DIR)gtest_lib/
SRC_DIR=../src/
UTIL_DIR=../util/
BUILD_DIR = ../build/
BUILD=$(addprefix ${BUILD_DIR}, ringbuffer.o)

LIB_LINKS = -L$(GLIBS) -lgtest -lstdc++ -lm -lpthread
INC_DIR = -I $(GTEST_DIR) -I $(SRC_DIR) -I $(UTIL_DIR)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC_DIR) -c $^

$(BUILD_DIR)%.o:
	cd ..; make build

test: $(OBJS) $(BUILD)
	$(CC) $(CFLAGS) -I $(GTEST_DIR) -o $@ $(BUILD) $(OBJS) $(LIB_LINKS) 