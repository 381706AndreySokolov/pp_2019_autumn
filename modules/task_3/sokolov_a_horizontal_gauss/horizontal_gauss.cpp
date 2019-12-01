// Copyright 2019 Sokolov Andrey
#include <mpi.h>
#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <list>
#include "../../../modules/task_3/sokolov_a_horizontal_gauss/horizontal_gauss.h"

std::vector<unsigned char> getRandomImage(size_t _cols, size_t _rows) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<unsigned char> image(_cols * _rows);
  for (int i = 0; i < _cols; i++)
    for (int j = 0; j < _rows; j++)
      image[i*_rows+j] = static_cast<unsigned char>(gen() % 256);

  return image;
}

unsigned char changePixel(std::vector<unsigned char> source, int x, int y, int rows, int cols) {
  int sum = 0;
  for (int j = -1; j <= 1; ++j) {
    for (int k = -1; k <= 1; ++k) {
      int x_idx = x + j;
      int y_idx = y + k;

      if (x_idx < 0 || x_idx > rows - 1) {
        x_idx = x;
      }
      if (y_idx < 0 || y_idx > cols - 1) {
        y_idx = y;
      }
      if (x_idx*cols + y_idx >= cols * rows) {
        x_idx = x;
        y_idx = y;
      }
      sum += static_cast<int>(source[x_idx*cols + y_idx] * (gaussFilter[j + 1][k + 1]));
    }
  }
  return sum / sumMask;
}

std::vector<unsigned char> filterImageSequential(std::vector<unsigned char> source, int rows, int cols) {
  std::vector<unsigned char> result(cols * rows);
  for (int i = 0; i < cols; ++i)
    for (int j = 0; j < rows; ++j)
      result[i * cols + j] = changePixel(source, i, j, rows, cols);
  return result;
}

std::vector<unsigned char> filterImageParallel(std::vector<unsigned char> source, int rows, int cols) {
  int comm_size, rank;
  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::vector<unsigned char> globalResult(cols * rows);

  if (rows < comm_size) {
    return filterImageSequential(source, rows, cols);
  }

  std::cout << "{" << rank << "}" << "ERROR" << std::endl;
  
  const int interval      = rows / comm_size; // how many lines will send to processes != 0  5 / 2 = 2 // 5 / 3 = 1
  const int last_interval = rows % comm_size; // residue to 0'th process                     5 % 2 = 1 // 5 % 3 = 2 

  std::vector<std::vector<unsigned char>> recvResult(comm_size - 1);

  if (rank == 0) {
    for (int i = 0; i < comm_size - 1; ++i) {
      recvResult[i].resize(interval * cols, 0);
    }
  }

  std::vector<unsigned char> localImage(interval * cols + 2 * cols);
  std::vector<unsigned char> localResult(interval * cols);

  if (rank == 0) {
    std::cout << "Source:" << std::endl;
    for (int i = 0; i < source.size(); ++i)
    {
      std::cout << (unsigned int)source[i] << " ";
    }
    std::cout << std::endl;

    // sending image rows to others process
    for (int proc = 1; proc < comm_size; proc++) {
      int startAdress = (proc * interval * cols) + (last_interval - 1) * cols;
      int countSend;

      if (proc != (comm_size - 1)) {
        countSend = interval * cols + 2 * cols;
      }
      else {
        countSend = interval * cols + cols;
      }
      MPI_Send(&source[0] + startAdress, countSend, MPI_UNSIGNED_CHAR, proc, 0, MPI_COMM_WORLD);
    }

  } else if (rank != 0){  // receive subvectors
    if (rank != comm_size - 1)
      MPI_Recv(&localImage[0], (interval + 2) * cols + 2, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    else {
      localImage.resize(interval * cols + cols);
      MPI_Recv(&localImage[0], (interval + 1) * cols, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }
    std::cout << "{" << rank << "}" << "Local Image" << std::endl;
    for (int i = 0; i < localImage.size(); ++i) {
      std::cout << (unsigned int)localImage[i] << " ";
    }
    std::cout << std::endl;
  }

  std::vector<unsigned char> localResultImage(interval * cols);

  if (rank == comm_size - 1) {
    for (int i = 1; i < interval + 1; ++i)
      for (int j = 0; j < cols; ++j)
        localResult[(i - 1) * cols + j] = changePixel(localImage, i, j, interval + 1, cols);
  }
  else if (rank != 0) {
    for (int i = 1; i < interval + 1; ++i)
      for (int j = 0; j < cols; ++j)
        localResult[(i - 1) * cols + j] = changePixel(localImage, i, j, interval + 2, cols);
  } else {
    for (int i = 0; i < interval + last_interval; ++i)
      for (int j = 0; j < cols; ++j)
        globalResult[i * cols + j] = changePixel(source, i, j, cols, rows);
  }

  std::cout << "{" << rank << "}" << "Local result" << std::endl;
  std::cout << "Size: " << localResult.size() << std::endl;
  for (int i = 0; i < localResult.size(); ++i) {
    std::cout << (unsigned int)localResult[i] << " ";
  }
  std::cout << std::endl;

  if (rank != 0) {
    MPI_Send(&localResult[0], interval * cols, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
  } else if (rank == 0) {
    //for (int i = 0; i < (interval + last_interval) * cols; ++i)
    //  globalResult[i] = localResult[i];
    for (int proc = 1; proc < comm_size; ++proc)
      //MPI_Recv(&recvResult[proc - 1], interval * cols, MPI_UNSIGNED_CHAR, proc, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(&globalResult[0] + ((interval + last_interval) * cols) + ((proc - 1) * interval * cols), interval * cols, MPI_UNSIGNED_CHAR, proc, 0, MPI_COMM_WORLD, &status);
    //for (int i = 0; i < comm_size - 1; ++i) {
    //  globalResult.insert(globalResult.begin() + (((interval + last_interval) * cols) + (i * interval * cols)), recvResult[i].begin(), recvResult[i].end());
    //}
  }


  return globalResult;
}
