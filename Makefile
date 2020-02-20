.PHONY: objDir clean

CC = g++
CFLAGS = -g -I. -I./coins/ -I./sort/
LIBS = -pthread -lpthread

SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
# SRCS = ThreadEfficiency.cpp ThreadEfficiency.hpp ExecuteCoins.cpp ExecuteCoins.hpp TwelveCoins.cpp TwelveCoins.hpp MergeSort.cpp MergeSort.hpp
# OBJS = $(patsubst %.cpp,objs/%.o,$(SRCS))
OBJS = $(SRCS:%.cpp=objs/%.o)
DEPS = ThreadPool.h SafeQueue.h

objs/%.o: %.cpp
	@echo Compiling C++ $(<F)
	@mkdir -p '$(@D)'
	@g++ -fms-extensions -c -std=c++11 $(CFLAGS) $< -o $@

all: objDir ThreadEfficiency

ThreadEfficiency: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm objs/*.o

objDir: objs/

objs/:
	mkdir -p objs