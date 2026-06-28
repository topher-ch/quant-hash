.PHONY: build main tests both clean

clean:
	rm -rf build

build:
	cmake -S . -B build
	cmake --build build

main: build
	./build/main

tests: build
	./build/tests

both: build
	./build/main
	./build/tests