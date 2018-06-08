cmake_minimum_required(VERSION 2.8.4)

set(EIGEN_INC_DIR ../bibli_eigen)
include_directories(${EIGEN_INC_DIR})

project(Correcteur)

set(SOURCE_FILES correcteur.cpp correcteur_test.cpp)
add_executable(correcteur_test ${SOURCE_FILES})
