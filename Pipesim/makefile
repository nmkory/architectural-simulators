pipesim: pipeline.o main.o
	g++ pipeline.o main.o -g -o pipesim

pipeline.o: pipeline.cpp
	g++ -g -c pipeline.cpp

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o pipesim
