cmake_minimum_required(VERSION 2.8.4)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

set(EIGEN_INC_DIR /Users/sawah/Documents/ponts/GMM/2eme_semestre/projet_departement/Force-torque_Robot/multi-threading/bibli_eigen)
include_directories(${EIGEN_INC_DIR})

project(multi_threading)
set(CMAKE_CXX_FLAGS -std=c++11)

set(SOURCE_FILES kalman.cpp initKalman.cpp envoi.cpp acquisition.cpp main.cpp)
add_executable(main ${SOURCE_FILES})
