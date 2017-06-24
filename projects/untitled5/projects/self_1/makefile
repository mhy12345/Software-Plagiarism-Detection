CXXFLAGS= -Wall -Wextra -g -std=c++11
target: main.o file.o project.o detectors.o cost_flow.o
	g++ -o main main.o file.o project.o cost_flow.o detectors.o

main.o : main.cpp

file.o : file.cpp file.h

project.o : project.cpp project.h

detectors.o : detectors.cpp detectors.h

cost_flow.o : cost_flow.cpp cost_flow.h

clean :
	rm *.o main
