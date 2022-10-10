target: omp_pi.c
	gcc -fopenmp -lm omp_pi.c -o omp_piOut

.PHONY: clean init

run:
	./omp_piOut 

clean:
	rm omp_piOut
