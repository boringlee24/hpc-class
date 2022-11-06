target: part_a.c
	mpicc part_a.c -o part_aOut

.PHONY: clean

run:
	sbatch part_a_node_2.script
	sbatch part_a_node_4.script

clean:
	rm part_aOut
