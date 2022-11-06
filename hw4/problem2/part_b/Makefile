target: part_b.c
	mpicc part_b.c -o part_bOut

.PHONY: clean

run:
	sbatch part_b_node_2.script
	sbatch part_b_node_4.script

clean:
	rm part_bOut
