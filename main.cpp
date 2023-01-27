
#include <iostream>
#include <vector>
#include <limits.h>
#include <omp.h>
#include "mpi.h"

#include "utils.hpp"

#define THREADS 4
#define DATA_SIZE 48
#define POPULATION_SIZE 100
#define ITERATIONS 10000
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.05

int main(int argc, char *argv[])
{
    int numprocs, rank;
    MPI_Status status; /* return status for recieve*/
    std::vector<std::vector<int>> distance_table(48, std::vector<int>(48, -1));

    int i, j, itr;

    // MPI Start
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Rank 0: Reading data from data.txt\n");
       // distance_table = read_table(distance_table);
        printf("Rank 0: Finished Reading\n");
        printf("Rank 0: Sharing with the rest of the processes\n");

        for (i = 1; i < numprocs; i++)
        {
            for (j = 0; j < DATA_SIZE; j++)
            {
                MPI_Send(&distance_table[j][0], DATA_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        for (j = 0; j < DATA_SIZE; j++)
        {
            MPI_Recv(&distance_table[j][0], DATA_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("Rank %d: recevied the data\n", rank);
    }

    std::vector<std::vector<int>> population(POPULATION_SIZE, std::vector<int>(48));

    printf("Rank %d: Initializing Population", rank);
    omp_set_dynamic(0);           // Disabling dynamic teams to garentee the required number of threads to be created
    omp_set_num_threads(THREADS); // Setting number of threads
    #pragma omp parallel shared(population) private(i, j)
    {
    #pragma omp for schedule(static)
        for (i = 0; i < POPULATION_SIZE; i++)
        {
            for (j = 0; j < 48; j++)
            {
                population[i][j] = j + 1;
            }
            //shuffle(population[i], 48);
        }
    }
    printf("Rank %d: Population Initialized Successfully\n", rank);

    for (itr = 0; itr < ITERATIONS; itr++)
    {
    }

    MPI_Finalize();
}