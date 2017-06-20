CC=gcc -std=gnu99

all_run: all run
	
all:
	$(CC) -Wall -Wextra -Werror -pedantic -Wno-unused-variable sokoban.c -o sokoban
run:
	./sokoban
clean:
	rm -rf sokoban

