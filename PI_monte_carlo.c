#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
  // Initialize MPI
  MPI_Init(NULL, NULL);

  // Get the total number of processes currently running
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the current process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Initialize the random number generator
  srand(time(NULL));

  // Define the number of points to generate for each process
  int num_points = 10000000;

  // Count the number of points generated within the circle
  int count = 0;
  for (int i = 0; i < num_points; i++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;
    double distance = x*x + y*y;
    if (distance <= 1) count++;
  }

  // Reduce results and get the total number of points within the circle
  int global_count;
  MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Calculate and print the final result
  if (world_rank == 0) {
    double pi = (double)global_count / (num_points * world_size) * 4;
    printf("Le nombre PI est approximativement égal à %.50f\n", pi);
  }

  // Terminate MPI
  MPI_Finalize();
}


