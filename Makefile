.PHONY: objDir clean

CC = g++
CFLAGS = -g -I.
LIBS = -pthread -lpthread

SRCS := ThreadEfficiency.cpp ThreadEfficiency.hpp ExecuteCoins.cpp ExecuteCoins.hpp TwelveCoins.cpp TwelveCoins.hpp
OBJS = $(patsubst %,objs/%.o,$(basename $(notdir $(SRCS))))
DEPS = ThreadPool.h SafeQueue.h

objs/%.o: %.cpp
	@echo Compiling C++ $(<F)
	@g++ -fms-extensions -c -std=c++11 $(CFLAGS) -o objs/$(*F).o $< 

all: objDir ThreadEfficiency

ThreadEfficiency: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm objs/*.o

objDir: objs/

objs/:
	mkdir -p objs
