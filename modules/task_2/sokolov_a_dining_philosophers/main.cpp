// Copyright 2019 Sokolov Andrey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <array>
#include "../../../modules/task_2/sokolov_a_dining_philosophers/dining_philosophers.h"

TEST(Dining_Philosophers_MPI, Sum_Mode_with_4_elements) {
  int mode{ -1 };
  int size{ 3 };
  int rank{ 0 };
  int comm_size{ 0 };
  int gold_result{ 0 };
  int local_result{ 0 };
  int global_result{ 0 };

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();
    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc + (proc + 1) + (proc + 2);
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  }
  else {
    std::array<int, 3U> mas{ { rank, rank + 1, rank + 2 } };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);

  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    ASSERT_EQ(global_result, gold_result);
  }
}

TEST(Dining_Philosophers_MPI, Default_Mode_with_5_elements) {
  int mode{ 0 };
  int size{ 5 };
  int rank{ 0 };
  int comm_size{ 0 };
  int gold_result{ 0 };
  int local_result{ 0 };
  int global_result{ 0 };

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();

    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc + 4;
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  }
  else {
    std::array<int, 5U> mas{ { rank, rank + 1, rank + 2, rank + 3, rank + 4 } };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    ASSERT_EQ(global_result, gold_result);
  }
}


TEST(Dining_Philosophers_MPI, Sum_Mode_with_3_elements) {
  int mode          {-1};
  int size          {3};
  int rank          {0};
  int comm_size     {0};
  int gold_result   {0};
  int local_result  {0};
  int global_result {0};

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();
    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc + (proc + 1) + (proc + 2);
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  } else {
    std::array<int, 3U> mas{ { rank, rank + 1, rank + 2 } };
    
    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
    
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    ASSERT_EQ(global_result, gold_result);
  }
}

TEST(Dining_Philosophers_MPI, Sum_Mode_with_10_elements) {
  int mode          {-1};
  int size          {10};
  int rank          {0};
  int comm_size     {0};
  int gold_result   {0};
  int local_result  {0};
  int global_result {0};

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();

    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc + (proc + 1) + (proc + 2) + (proc + 3) + (proc + 4) +\
                     (proc + 5) + (proc + 6) + (proc + 7) + (proc + 8) + (proc + 9);
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  } else {
    std::array<int, 10U> mas{ { rank, rank + 1, rank + 2, rank + 3, rank + 4,
                                rank + 5, rank + 6, rank + 7, rank + 8, rank + 9 } };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    ASSERT_EQ(global_result, gold_result);
  }
}

TEST(Dining_Philosophers_MPI, Multiplication_Mode_with_3_elements) {
  int mode          {-2};
  int size          {3};
  int rank          {0};
  int comm_size     {0};
  int gold_result   {0};
  int local_result  {1};
  int global_result {0};

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();

    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc * (proc + 1) * (proc + 2);
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  } else {
    std::array<int, 3U> mas{ { rank, rank + 1, rank + 2 } };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    global_result--;
    ASSERT_EQ(global_result, gold_result);
  }
}

TEST(Dining_Philosophers_MPI, Multiplication_Mode_with_10_elements) {
  int mode          {-2};
  int size          {10};
  int rank          {0};
  int comm_size     {0};
  int gold_result   {0};
  int local_result  {1};
  int global_result {0};

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();

    for (int proc = 1; proc < comm_size; proc++) {
      gold_result += proc * (proc + 1) * (proc + 2) * (proc + 3) * (proc + 4) * \
                     (proc + 5) * (proc + 6) * (proc + 7) * (proc + 8)  * (proc + 9);
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  } else {
    std::array<int, 10U> mas{ { rank, rank + 1, rank + 2, rank + 3, rank + 4,
                                rank + 5, rank + 6, rank + 7, rank + 8, rank + 9 } };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    global_result--;
    ASSERT_EQ(global_result, gold_result);
  }
}

TEST(Dining_Philosophers_MPI, Multiplication_Mode_with_40_elements) {
  int mode{ -2 };
  int size{ 40 };
  int rank{ 0 };
  int comm_size{ 0 };
  int gold_result{ 0 };
  int local_result{ 1 };
  int global_result{ 0 };

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  if (rank == 0) {
    double time1 = MPI_Wtime();
    startTable(comm_size, size);
    double time2 = MPI_Wtime();

    for (int proc = 1; proc < comm_size; proc++) {
      int local_gold_result = 1;
      for (int i = 0; i < 40; ++i) {
        local_gold_result *= proc + i;
      }
      global_result += local_gold_result;
    }
    std::cout << "Time " << time2 - time1 << std::endl;
  }
  else {
    std::array<int, 40U> mas{ { rank, rank + 1, rank + 2, rank + 3, rank + 4,
                                rank + 5, rank + 6, rank + 7, rank + 8, rank + 9,
                                rank + 10, rank + 11, rank + 12, rank + 13, rank + 14,
                                rank + 15, rank + 16, rank + 17, rank + 18, rank + 19,
                                rank + 20, rank + 21, rank + 22, rank + 23, rank + 24,
                                rank + 25, rank + 26, rank + 27, rank + 28, rank + 29,
                                rank + 30, rank + 31, rank + 32, rank + 33, rank + 34,
                                rank + 35, rank + 36, rank + 37, rank + 38, rank + 39} };

    startPilosopher(&local_result, rank, mas.data(), comm_size, mode, size);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    global_result--;
    ASSERT_EQ(global_result, gold_result);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
