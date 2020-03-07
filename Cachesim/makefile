cachesim: cachesim.o main.o
	g++ cachesim.o main.o -g -o cachesim

cachesim.o: cachesim.cpp
	g++ -c -g cachesim.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o cachesim
