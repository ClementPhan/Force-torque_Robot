cmake_minimum_required(VERSION 2.8.4)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

set(EIGEN_INC_DIR /Users/sawah/Documents/ponts/GMM/2eme_semestre/projet_departement/Force-torque_Robot/Correction/Correction/kalman-cpp/bibli_eigen)
include_directories(${EIGEN_INC_DIR})

project(Correcteur)

set(SOURCE_FILES correcteur.cpp correcteur_test.cpp)
add_executable(correcteur_test ${SOURCE_FILES})
