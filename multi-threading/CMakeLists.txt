cmake_minimum_required(VERSION 2.8.4)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

set(EIGEN_INC_DIR /Users/sawah/Documents/ponts/GMM/2eme_semestre/projet_departement/Kalman/kalman-cpp/bibli_eigen)
include_directories(${EIGEN_INC_DIR})

project(kalman)

set(SOURCE_FILES kalman.cpp main.cpp)
add_executable(main ${SOURCE_FILES})
