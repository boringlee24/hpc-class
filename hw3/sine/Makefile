all: double_sine single_sine

double_sine: double_sine.c
	gcc double_sine.c -o doubleSine -lm
single_sine: single_sine.c
	gcc single_sine.c -o singleSine -lm 
.PHONY: clean init

run:
	./doubleSine && ./singleSine

clean:
	rm doubleSine && rm singleSine
