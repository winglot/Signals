CXX = g++
CXXFLAGS = -std=c++11 -I../include -L../build
LIBA = -lVarSlot_static

simple:
	$(CXX) simple.cpp $(CXXFLAGS) $(LIBA) -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f simple

.PHONY: clean cleanall
