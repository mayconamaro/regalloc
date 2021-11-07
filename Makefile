target: regalloc

all: regalloc

clean: 
	-rm build/*.o

build/program.o: src/program.cpp
	g++ -std=c++20 -c src/program.cpp -o build/program.o -Wall

build/local_search.o: src/local_search.cpp
	g++ -std=c++20 -c src/local_search.cpp -o build/local_search.o -Wall

build/construction.o: src/construction.cpp
	g++ -std=c++20 -c src/construction.cpp -o build/construction.o -Wall

build/smart_ils.o: src/metaheuristics/smart_ils.cpp
	g++ -std=c++20 -c src/metaheuristics/smart_ils.cpp -o build/smart_ils.o -Wall

regalloc: build/program.o build/construction.o build/local_search.o build/smart_ils.o src/main.cpp
	g++ -std=c++20 build/*.o src/main.cpp -o regalloc -Wall
	
	
	