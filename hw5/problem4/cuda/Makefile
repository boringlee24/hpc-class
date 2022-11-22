target: GPUvecAdd.cu
	nvcc GPUvecAdd.cu -o cudaOut

.PHONY: clean init

run:
	./cudaOut

clean:
	rm cudaOut
