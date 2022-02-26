COMPILER = clang++

build:
	$(COMPILER) src/main.cpp -o out/minesweeper

build-debug:
	$(COMPILER) -DDEBUG src/main.cpp -o out/minesweeper

check:
	$(COMPILER) -v

run:
	out/minesweeper $(ARGS)

clean:
	rm out/minesweeper
