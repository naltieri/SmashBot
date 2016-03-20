CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11
#LDFLAGS=-g -Wall -std=gnu++11 -lUtil

SOURCES=smashbot.cpp
GOALS=Goals/*.cpp
STRATS=Strategies/*.cpp
TACTICS=Tactics/*.cpp
CHAINS=Chains/*.cpp
UTIL=Util/*.cpp

EXECUTABLE=smashbot

#all: $(OBJ)
all: goals.sylvan strats.sylvan tactics.sylvan chains.sylvan util.sylvan main
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) *.o

main:
	$(CC) $(CFLAGS) $(SOURCES)

goals.sylvan:
	$(CC) $(CFLAGS) $(GOALS)

strats.sylvan:
	$(CC) $(CFLAGS) $(STRATS)

tactics.sylvan:
	$(CC) $(CFLAGS) $(TACTICS)

chains.sylvan:
	$(CC) $(CFLAGS) $(CHAINS)

util.sylvan:
	$(CC) $(CFLAGS) $(UTIL)

clean:
	rm -f *.o */*.o *.d */*.d smashbot
