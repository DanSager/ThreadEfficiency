.PHONY: objDir clean

CC = g++
CFLAGS = -g -I.
LIBS = -lpthread

SRCS := ThreadEfficiency.cpp ThreadEfficiency.hpp ExecuteSingle.cpp ExecuteSingle.hpp WeighingBalls.cpp	WeighingBalls.hpp
OBJS = $(patsubst %,objs/%.o,$(basename $(notdir $(SRCS))))

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
