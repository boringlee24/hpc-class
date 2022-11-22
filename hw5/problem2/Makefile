all: naive tile

naive: stencil_naive.cu
	nvcc stencil_naive.cu -o naiveOut
tile: stencil_tile.cu
	nvcc stencil_tile.cu -o tileOut
opt: stencil_tile_opt.cu
	nvcc stencil_tile_opt.cu -o tileoptOut

.PHONY: clean init

run:
	./tileoptOut

clean:
	rm naiveOut	
	rm tileOut
	rm tileoptOut
