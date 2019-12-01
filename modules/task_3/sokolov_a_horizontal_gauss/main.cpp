// Copyright 2019 Sokolov Andrey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <array>
#include "../../../modules/task_3/sokolov_a_horizontal_gauss/horizontal_gauss.h"

//TEST(Horizontal_Gauss_MPI, Test_Image_9_9) {
//  int rank;
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//  constexpr int cols{ 9 };
//  constexpr int rows{ 9 };
//
//  std::vector<unsigned char> src;
//  std::vector<unsigned char> resPar;
//  std::vector<unsigned char> resSeq;
//
//  if (rank == 0) {
//    src = getRandomImage(cols, rows);
//  }
//
//  resPar = filterImageParallel(src, cols, rows);
//
//  //std::cout << "{" << rank << "}" << "Done" << std::endl;
//
//  if(rank == 0) {
//    resSeq = filterImageSequential(src, cols, rows);
//    for (int i = 0; i < cols * rows; ++i) {
//      std::cout << (unsigned int)resPar[i] << " ";
//    }
//    std::cout << std::endl;
//    for (int i = 0; i < cols* rows; ++i) {
//      std::cout << (unsigned int)resSeq[i] << " ";
//    }
//    ASSERT_EQ(resPar, resSeq);
//  }
//  //std::cout << "{" << rank << "}" << "Finish" << std::endl;
//}

//TEST(Horizontal_Gauss_MPI, Test_Image_27_27) {
//  int rank;
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//  constexpr int cols{ 27 };
//  constexpr int rows{ 27 };
//
//  std::vector<unsigned char> src;
//  std::vector<unsigned char> resPar;
//  std::vector<unsigned char> resSeq;
//
//  if (rank == 0) {
//    src = getRandomImage(cols, rows);
//  }
//
//  resPar = filterImageParallel(src, cols, rows);
//
//  std::cout << "{" << rank << "}" << "Done" << std::endl;
//
//  if (rank == 0) {
//    resSeq = filterImageSequential(src, cols, rows);
//    for (int i = 0; i < cols * rows; ++i) {
//      std::cout << (unsigned int)resPar[i] << " ";
//    }
//    std::cout << std::endl;
//    for (int i = 0; i < cols* rows; ++i) {
//      std::cout << (unsigned int)resSeq[i] << " ";
//    }
//    ASSERT_EQ(resPar, resSeq);
//  }
//  //std::cout << "{" << rank << "}" << "Finish" << std::endl;
//}

TEST(Horizontal_Gauss_MPI, Test_Image_5_10) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  constexpr int cols{ 5 };
  constexpr int rows{ 10 };

  std::vector<unsigned char> src;
  std::vector<unsigned char> resPar;
  std::vector<unsigned char> resSeq;

  if (rank == 0) {
    src = getRandomImage(cols, rows);
  }

  resPar = filterImageParallel(src, cols, rows);

  //std::cout << "{" << rank << "}" << "Done" << std::endl;

  if (rank == 0) {
    resSeq = filterImageSequential(src, cols, rows);
    for (int i = 0; i < cols * rows; ++i) {
      std::cout << (unsigned int)resPar[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < cols* rows; ++i) {
      std::cout << (unsigned int)resSeq[i] << " ";
    }
    ASSERT_EQ(resPar, resSeq);
  }
  //std::cout << "{" << rank << "}" << "Finish" << std::endl;
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
