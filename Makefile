
build_dir=build

flags=-Wall -g 
libs=-lncurses
source= src/main.c

all: build
	gcc $(source) $(flags) $(libs) -o $(build_dir)/game

build:
	mkdir $(build_dir)

clean:
	rm -rf $(build_dir)
