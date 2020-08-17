
# Generic Makefile
#

# executable name
EXE= a.out

# srcs
SRCS= main.cpp GameObject.cpp GameRunner.cpp Ship.cpp PlayerShip.cpp EnemyShip.cpp EnemyDestroyer.cpp EnemyCruiser.cpp Projectile.cpp PlayerMissle.cpp EnemyMissle.cpp
# /some/path /some/other/path
SRCPATH= ./ ./src

# compiler
CC = g++

# compiler flags
CFLAGS = -Wall -g -O0

OBJS= $(SRCS:.cpp=.o)
VPATH=$(SRCPATH)

.PHONY: depend clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) -lncurses

#build .o's from .c's,
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) *.o *.gch *~ $(EXE)
