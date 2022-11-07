target: matmul_gpu.cu
	nvcc matmul_gpu.cu -o matmulOut

.PHONY: clean init

run:
	./matmulOut

clean:
	rm matmulOut 
