all: part_a part_b

part_a: part_a.c
	mpicc part_a.c -o part_aOut
part_b: part_b.c
	mpicc part_b.c -o part_bOut 
.PHONY: clean init

run:
	./part_aOut && ./part_bOut

clean:
	rm part_aOut && rm part_bOut
