branchsim: branchprediction.o main.o
	g++ branchprediction.o main.o -g -o branchsim

branchprediction.o: branchprediction.cpp
	g++ -c -g branchprediction.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o branchsim
