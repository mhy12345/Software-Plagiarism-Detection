CXXFLAGS = -g -Wall
target: main.o KMPSearchStrategy.o KRSearchStrategy.o SearchEngine.o SearchStrategy.o
	g++ ${CXXFLAGS} \
		-o main \
		SearchEngine.o \
		KMPSearchStrategy.o \
		KRSearchStrategy.o \
		SearchStrategy.o \
		main.o

main.o : main.cpp

KMPSearchStrategy.o : KMPSearchStrategy.cpp KMPSearchStrategy.h

KRSearchStrategy.o : KRSearchStrategy.cpp KRSearchStrategy.h

SearchEngine.o : SearchEngine.cpp SearchEngine.h

SearchStrategy.o : SearchStrategy.cpp SearchStrategy.h

clean:
	rm *.o
	rm main
