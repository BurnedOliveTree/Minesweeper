COMPILER = javac
INTERPRETER = java

build:
	$(COMPILER) -d out src/Main.java

check:
	$(INTERPRETER) -version

run:
	$(INTERPRETER) -classpath out Main

clean:
	rm out/Main.class
