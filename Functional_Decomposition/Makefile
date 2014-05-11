default: all

all:
	rm -rf build
	mkdir build
	g++ -std=c++0x -O3 -c lib/DeerThread.cpp -o build/DeerThread.o
	g++ -std=c++0x -O3 -c lib/EntityThread.cpp -o build/EntityThread.o
	g++ -std=c++0x -O3 -c lib/GrainThread.cpp -o build/GrainThread.o
	g++ -std=c++0x -O3 -c lib/HunterThread.cpp -o build/HunterThread.o
	g++ -std=c++0x -O3 -c lib/WatcherThread.cpp -o build/WatcherThread.o	
	g++ -std=c++0x -O3 -c lib/WorldState.cpp -o build/WorldState.o
	g++ -std=c++0x -O3 -c Main.cpp -o build/Main.o -lpthread
	g++ -std=c++0x -O3 build/DeerThread.o build/EntityThread.o build/HunterThread.o build/GrainThread.o build/WatcherThread.o build/WorldState.o build/Main.o -o build/FunctionalDecomposition -lpthread

clean:
	rm -rf build
