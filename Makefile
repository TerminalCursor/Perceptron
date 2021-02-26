.PHONY: clean

build: main.c
	gcc -O3 -o $@ $<

clean:
	rm -f build
