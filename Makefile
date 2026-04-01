CXX = g++
CXXFLAGS = -std=c++11 -O2 -fno-exceptions -fno-rtti

test: json511.cpp json511.hpp test.cpp
	$(CXX) $(CXXFLAGS) json511.cpp test.cpp -o test

clean:
	rm -f test

.PHONY: clean