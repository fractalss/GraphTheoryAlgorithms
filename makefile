CXX=g++
CXXFLAGS= -Wall -g -std=c++11
RM=rm -f
SRCS=hw2.cpp Simulator.cpp DijkstrasPath.cpp Graph.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

all: hw2
hw2: $(OBJS)
	$(CXX) $(CXXFLAGS) -o hw2 $(OBJS)

clean:
	$(RM) hw2 $(OBJS)
