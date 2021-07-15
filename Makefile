
build_dir=build

flags=-Wall -g 
libs=-lncurses
source= src/main.c

all:
	gcc $(source) $(flags) $(libs) -o $(build_dir)/game
clean:
	rm -rf $(build_dir)
