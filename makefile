CXX = g++
CXXFLAGS 	= -g -Wall -O3 -std=c++11

all: main

main: obj/main.o obj/methody.o
	$(CXX) obj/main.o obj/methody.o -o $@
obj/main.o: main.cpp itemcf.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/methody.o: MethodY.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

transform: obj/transform.o
	$(CXX) obj/transform.o -o $@
obj/transform.o: transform.cpp itemcf.h
	$(CXX) $(CXXFLAGS) -c $< -o $@