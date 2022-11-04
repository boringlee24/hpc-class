/* The Parallel Hello World Program */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
   int rank, size, namelen;
   char processor_name[MPI_MAX_PROCESSOR_NAME];
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Get_processor_name(processor_name, &namelen);
     
   printf("Hello World from process %d from the Node %s. There are a total of %d processes. namelen=%d\n", 
         rank, processor_name, size, namelen);

   MPI_Finalize();
   return 0;
}
