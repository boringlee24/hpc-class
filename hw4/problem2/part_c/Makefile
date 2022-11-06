all: bin20 bin100

bin20: bin20_node2.c
	mpicc bin20_node2.c -o bin20Out
bin100: bin100_node2.c
	mpicc bin100_node2.c -o bin100Out

.PHONY: clean

run:
	sbatch bin20.script
	sbatch bin100.script

clean:
	rm bin20Out 
	rm bin100Out
