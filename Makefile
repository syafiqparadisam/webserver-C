file=main

build:
	gcc -o bin/${file}.out src/${file}.c

run: build
	./bin/${file}.out