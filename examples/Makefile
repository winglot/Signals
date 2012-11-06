CXX = g++
CXXFLAGS = -std=c++11 -I../

simple: ./simple.cpp
	$(CXX) simple.cpp $(CXXFLAGS) -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f simple

.PHONY: clean cleanall
