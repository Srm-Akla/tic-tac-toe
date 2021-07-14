
build_dir=build

flags=-Wall -lncurses -o
source= src/main.c

all:
	gcc $(source) $(flags) $(build_dir)/game
clean:
	rm -rf $(build_dir)
