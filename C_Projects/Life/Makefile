Shell := /bin/sh 
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lm
EXEC = life
OBJS = universe.o life.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS) -lncurses
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< 
	
clean:
	rm -f life *.o universe 

format:
	clang-format -i -style=file *.[ch]
