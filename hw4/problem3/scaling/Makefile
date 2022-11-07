target: matmul_scaling.cu
	nvcc matmul_scaling.cu -o matmulOut

.PHONY: clean init

run:
	./matmulOut 1 && ./matmulOut 2 && ./matmulOut 4 && ./matmulOut 8 && ./matmulOut 16

clean:
	rm matmulOut 
