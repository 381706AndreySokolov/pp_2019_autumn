#include <mpi.h>
#include <iostream>
#include <random>
#include <ctime>
#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>
#include "../../../modules/task_1/sokolov_a_vector_mid_value/vector_mid_value.h"

int MidValueOfVector(const std::vector <int> &vector) {
  int global_mid = 0;
  int size, rank;
  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int interval = vector.size() / size;
  const int last_interval = vector.size() % size;

  if (rank == 0) {
    for (int proc = 1; proc < size; proc++) {
      MPI_Send(&vector[0] + proc * interval, interval, MPI_INT, proc, 0, MPI_COMM_WORLD); 
    }
  }

  std::vector<int>local_vector(interval + last_interval);
  int local_mid = 0;

  if (rank == 0) {
    for (int i = 0; i < interval + last_interval; i++)
      local_mid += local_vector[i];
    local_mid /= (interval + last_interval);
  }
  else {
    MPI_Recv(&local_vector, interval, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    for (int i = 0; i < interval; i++) 
      local_mid += local_vector[i];
    local_mid /= interval;
  }

  MPI_Barrier(MPI_COMM_WORLD);

  if (rank == 0) {
    global_mid += local_mid;
    for (int proc = 1; proc < size; proc++){
      int tmp;
      MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      global_mid += tmp;
    }
  }
  else {
    MPI_Send(&local_mid, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  global_mid /= size;

  return global_mid;
}