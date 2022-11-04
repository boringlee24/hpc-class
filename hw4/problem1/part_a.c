#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
int world_rank;
int world_size;
int partner_rank;
int curr_num;
int name_length;
char processor_name[MPI_MAX_PROCESSOR_NAME];

MPI_Init(NULL, NULL);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Get_processor_name(processor_name, &name_length);

if (world_size < 32) {
	fprintf(stderr, "World size must be >= 32\n");
  	MPI_Abort(MPI_COMM_WORLD, 1);
   }

if (world_rank == 0) {
	partner_rank = world_rank + 1;
	curr_num = 1;
	printf("process rank %d (node %s) prints %d\n", world_rank, processor_name, curr_num);
	curr_num += 1;
	MPI_Send(&curr_num, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);	
}
else if (world_rank == world_size - 1)
{
	partner_rank = world_rank - 1;
	// first listen
	MPI_Recv(&curr_num, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("process rank %d (node %s) prints %d\n", world_rank, processor_name, curr_num);
	curr_num += 1;
}
else {
	partner_rank = world_rank - 1;
	// first listen
	MPI_Recv(&curr_num, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("process rank %d (node %s) prints %d\n", world_rank, processor_name, curr_num);
	partner_rank = world_rank + 1;
	curr_num += 1;
	MPI_Send(&curr_num, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);	
}

MPI_Finalize();

}
