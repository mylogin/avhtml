CXX 		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++11 -Iinclude/
EXECUTABLE 	:= html5test

all: $(EXECUTABLE)

$(EXECUTABLE): html5.o test.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

html5.o: src/html5.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

test.o: test/test.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	-rm -f *.o $(EXECUTABLE)
