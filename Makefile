
build_dir=build

flags=-lncurses -o
source= src/main.c

all:
	gcc $(source) $(flags) $(build_dir)/game
	./build/game

clean:
	rm -rf $(build_dir)
