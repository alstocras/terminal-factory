compiler = g++
binary = build/tf

sourceFiles = $(wildcard *.cpp)

all: $(binary)

$(binary): $(sourceFiles)
	mkdir -p build
	$(compiler) $(sourceFiles) -lncurses -o $(binary)

systeminstall: 
	sudo cp $(binary) /usr/bin

userinstall:
	cp $(binary) ~/.local/bin

useruninstall:
	rm ~/.local/bin/tf

systemuninstall:
	sudo rm /usr/bin/tf

