pipesim: pipeline.o main.o
	g++ pipeline.o main.o -g -o pipesim

pipeline.o: pipeline.cpp
	g++ -c -g pipeline.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o pipesim
