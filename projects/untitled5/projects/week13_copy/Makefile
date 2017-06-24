CXXFLAGS = -g -Wall
target: main.o KMPS.o KRS.o SearchEngine.o SearchStrategy.o
	g++ ${CXXFLAGS} \
		-o main \
		SearchEngine.o \
		KMPS.o \
		KRS.o \
		SearchStrategy.o \
		main.o

main.o : main.cpp

KMPS.o : KMPS.cpp KMPS.h

KRS.o : KRS.cpp KRS.h

SearchEngine.o : SearchEngine.cpp SearchEngine.h

SearchStrategy.o : SearchStrategy.cpp SearchStrategy.h

clean:
	rm *.o
	rm main
