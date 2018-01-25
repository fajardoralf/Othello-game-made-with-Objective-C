CC=gcc
DEPS = othello.h
CFLAGS = -Wall -std=c11
OBJS = othello.o board.o gamelogic.o

all: othellomake

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CLAGS)

othellomake: $(OBJS)
	gcc -o othellomake $(OBJS) $(CFLAGS)


clean:
	rm -f othellomake *.othellomake

remake: clean othellomake

