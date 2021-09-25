#all:
#	clang++ -std=c++1y -stdlib=libc++ -Wall Matrix/Matrix.cpp Graph/Graph.cpp -o main
#test:
#	clang++ -std=c++1y -stdlib=libc++ -Wall cs225/catch/catchmain.cpp  Tests/GraphTests.cpp -o tests
#exec:
#	./main
# -stdlib=libc++ 

#CC = clang++ 
#CFLAGS  = -g -Wall
OBJS = Matrix.o MatrixTest.o LLE.o PNG.o lodepng.o HSLAPixel.o GraphTests.o LLEtest.o Graph.o


CXX = clang++ -std=c++1y -stdlib=libc++
CXXFLAGS  = -Wall -Wextra -Werror -g
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ $(CS225) -lc++abi

default: main

main: PNG.o lodepng.o HSLAPixel.o Graph.o LLE.o Matrix.o Animation.o main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o main	PNG.o lodepng.o Animation.o HSLAPixel.o Graph.o LLE.o Matrix.o main.o

test:  PNG.o lodepng.o HSLAPixel.o Graph.o LLE.o Matrix.o cs225/catch/catchmain.o Tests/LLEtest.o Tests/GraphTests.o Tests/MatrixTest.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o test PNG.o lodepng.o Graph.o LLE.o HSLAPixel.o Matrix.o cs225/catch/catchmain.o Tests/LLEtest.o Tests/GraphTests.o Tests/MatrixTest.o

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp
Matrix.o:  Matrix/Matrix.h Matrix/Matrix.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Matrix/Matrix.cpp

MatrixTest.o:  Tests/MatrixTest.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Tests/MatrixTest.cpp

LLE.o:  LLE/LLE.h LLE/LLE.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c LLE/LLE.cpp

PNG.o: cs225/PNG.h cs225/PNG.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/PNG.cpp

lodepng.o: cs225/lodepng/lodepng.h cs225/lodepng/lodepng.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/lodepng/lodepng.cpp

HSLAPixel.o: cs225/HSLAPixel.h cs225/HSLAPixel.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/HSLAPixel.cpp

Animation.o: cs225/Animation.h cs225/Animation.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/Animation.cpp

GraphTests.o: Tests/GraphTests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/catch/catchmain.cpp Tests/GraphTests.cpp

LLEtest.o:  Tests/LLEtest.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cs225/catch/catchmain.cpp Tests/LLEtest.cpp

Graph.o: Graph/Graph.h Graph/Graph.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Graph/Graph.cpp
clean: 
	$(RM) count *.o *~
	