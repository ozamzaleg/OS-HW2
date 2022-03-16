CC = gcc
OBJS = targil2.o
EXEC = targil2
DEBUG = -g
CFLAGS = -std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : clean $(OBJS)
	$(CC) $(OBJS) -o $@ -lpthread

targil2.o: targil2.c function.c defenition.h function.h 


clean:
	rm -f $(EXEC) $(OBJS)
