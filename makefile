Lab6.exe: lab6.o
	g++ -std=c++11 -g -Wall lab6.o -o Lab6.exe

lab6.o: lab6.cpp
	g++ -std=c++11 -g -Wall -c lab6.cpp

clean:
	rm *.o Lab6.exe
