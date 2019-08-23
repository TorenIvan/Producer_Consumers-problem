OBJS	= main.o
SOURCE	= main.c
HEADER	= 
OUT	= main
CC	= gcc
FLAGS	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) 


main.o: main.c
	$(CC) $(FLAGS) main.c 

clean:
	rm -f $(OBJS) $(OUT)
