all: cuda openmp

cuda: histo.cu
	nvcc histo.cu -o histoOut
openmp: omp_histo.c
	gcc -fopenmp omp_histo.c -o omp_histoOut

.PHONY: clean init

run:
	./histoOut
	./omp_histoOut

clean:
	rm histoOut
	rm omp_histoOut
