file=main



building: 
	 gcc -o build/handler.out -c src/handler/handler.c
	 gcc -o build/${file}.out -c src/${file}.c
	 gcc build/handler.out build/${file}.out -o build/main

run: building
	./build/main