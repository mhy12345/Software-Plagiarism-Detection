all: kmp.o karp_rabin.o main.o
	g++ kmp.o karp_rabin.o main.o -o main -O2

kmp.o: kmp.cpp kmp.h match_strategy.h
	g++ kmp.cpp -o kmp.o -c -O2 -std=c++11

karp_rabin.o: karp_rabin.cpp karp_rabin.h match_strategy.h
	g++ karp_rabin.cpp -o karp_rabin.o -c -O2 -std=c++11

main.o: main.cpp kmp.h karp_rabin.h match_strategy.h
	g++ main.cpp -o main.o -c -O2 -std=c++11

.PHONY clean:
	rm main.o
	rm kmp.o
	rm karp_rabin.o
	rm main
