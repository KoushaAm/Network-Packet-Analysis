CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LIBS = -lpcap

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

sniffer: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f src/*.o sniffer
