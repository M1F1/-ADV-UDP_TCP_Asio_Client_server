CC= g++
CFLAGS=  -Wall -g -std=c++11 -lboost_system
SRC= $(wildcard *.cpp)
OBJS= $(SRC:.cpp=.o)
MAIN= Test

$(MAIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) 

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)
mem:
	valgrind --tool=memcheck --leak-check=full -v ./$(MAIN)
run:
	./$(MAIN)

.PHONY: clean
.PHONY: mem
.PHONY: run
