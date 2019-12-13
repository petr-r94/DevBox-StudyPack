#include<stdio.h>
#include<mpi.h>


int main(int argc, char **argv) {
    MPI_Comm com = MPI_COMM_WORLD;
    char host[MPI_MAX_PROCESSOR_NAME];
    int np, rank, len;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(com, &np);
    MPI_Comm_rank(com, &rank);
    MPI_Get_processor_name(host, &len);
    printf("%d of %d on %s\n", rank, np, host);
    MPI_Finalize();
    return 0;
}
