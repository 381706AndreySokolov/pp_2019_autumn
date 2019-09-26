#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/sokolov_a_vector_mid_value/vector_mid_value.h"

TEST(Mid_Value_Vector_MPI, Test_Common_Numbers) {
  std::vector <int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    EXPECT_EQ(MidValueOfVector(vector), 4);
  }
}

TEST(Mid_Value_Vector_MPI, Test_Equal_Numbers) {
  std::vector <int> vector = { 3, 3, 3, 3, 3, 3, 3, 3 };
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    EXPECT_EQ(MidValueOfVector(vector), 3);
  }
}

TEST(Mid_Value_Vector_MPI, Test_Empty_Numbers) {
  std::vector <int> vector = { };
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    EXPECT_EQ(MidValueOfVector(vector), 0);
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