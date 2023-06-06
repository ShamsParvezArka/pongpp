CXX = g++
CFLAGS = -std=c++2a -Wall -Wextra -Wshadow -Wswitch-default -Wconversion -Wunreachable-code  
CLIBS = -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm

output: main.cpp
	$(CXX) -o pongpp main.cpp lib/pongpp.cpp $(CFLAGS) $(CLIBS)

clean:
	rm pongpp 
