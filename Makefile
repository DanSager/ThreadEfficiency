.PHONY: objDir clean

CC = g++
CFLAGS = -g -I.
LIBS = -lboost_system -lpthread -lboost_thread

SRCS := main.cpp main.hpp
OBJS = $(patsubst %,objs/%.o,$(basename $(notdir $(SRCS))))

objs/%.o: %.cpp
	@echo Compiling C++ $(<F)
	@g++ -fms-extensions -c -std=c++11 $(CFLAGS) -o objs/$(*F).o $< 

all: objDir main

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm objs/*.o

objDir: objs/

objs/:
	mkdir -p objs
