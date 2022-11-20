all: naive tile

naive: stencil_naive.cu
	nvcc stencil_naive.cu -o naiveOut
tile: stencil_tile.cu
	nvcc stencil_tile.cu -o tileOut

.PHONY: clean init

run:
	./tileOut

clean:
	rm naiveOut	
	rm tileOut
