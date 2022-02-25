COMPILER = clang

build:
	$(COMPILER) src/main.c -o out/minesweeper

build-debug:
	$(COMPILER) -DDEBUG src/main.c -o out/minesweeper

check:
	$(COMPILER) -v

run:
	out/minesweeper

clean:
	rm out/minesweeper
