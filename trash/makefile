CXXFLAGS=-g -std=c++11
OBJECTS= main.o \
		 project.o
target : ${OBJECTS}
	g++ ${CXXFLAGS} -o main ${OBJECTS}

main.o : main.cpp

project.o : project.cpp project.h

