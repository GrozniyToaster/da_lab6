
CC = g++
CXX_FLAGS = -Wall -Wextra -O2 -std=c++17 -pedantic
PROJ = solution

all: main.cpp big_integer.hpp big_integer.o big_integer_tools.o 
	$(CC) $(CXX_FLAGS) big_integer.o big_integer_tools.o main.cpp -o $(PROJ)  

big_integer_tools.o: big_integer_tools.hpp big_integer_tools.cpp
	$(CC) $(CXX_FLAGS) -c big_integer_tools.cpp  

big_integer.o: big_integer_tools.hpp big_integer.cpp big_integer.hpp 
	$(CC) $(CXX_FLAGS) -c big_integer.cpp 

clean: 
	rm -f *.o $(NAME)