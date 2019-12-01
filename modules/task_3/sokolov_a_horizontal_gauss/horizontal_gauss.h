// Copyright 2019 Sokolov Andrey
#ifndef MODULES_TASK_3_SOKOLOV_A_HORIZONTAL_GAUSS_HORIZONTAL_GAUSS_H_
#define MODULES_TASK_3_SOKOLOV_A_HORIZONTAL_GAUSS_HORIZONTAL_GAUSS_H_

constexpr unsigned char gaussFilter[3][3] {{1, 2, 1},
                                           {2, 4, 2},
                                           {1, 2, 1}};

constexpr unsigned char sumMask {16};

std::vector<unsigned char> getRandomImage(size_t sizeN, size_t sizeM);

unsigned char changePixel(std::vector<unsigned char> _source, int x, int y, int rows, int cols);

std::vector<unsigned char> filterImageParallel(std::vector<unsigned char> source, int rows, int cols);
std::vector<unsigned char> filterImageSequential(std::vector<unsigned char> source, int rows, int cols);



#endif  // MODULES_TASK_3_SOKOLOV_A_HORIZONTAL_GAUSS_HORIZONTAL_GAUSS_H_
