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
all: goals.d strats.d tactics.d chains.d util.d main
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) *.o

main:
	$(CC) $(CFLAGS) $(SOURCES)

goals.d:
	$(CC) $(CFLAGS) $(GOALS)

strats.d:
	$(CC) $(CFLAGS) $(STRATS)

tactics.d:
	$(CC) $(CFLAGS) $(TACTICS)

chains.d:
	$(CC) $(CFLAGS) $(CHAINS)

util.d:
	$(CC) $(CFLAGS) $(UTIL)

clean:
	rm -f *.o */*.o *.d */*.d smashbot
