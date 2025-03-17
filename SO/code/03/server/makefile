CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pthread
TARGET = server
SOURCES = server.cc

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
