build:
	gcc -o bin/${file}.out ${file}.c

run: build
	./bin/${file}