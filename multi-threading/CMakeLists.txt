cmake_minimum_required(VERSION 3.9)
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

set(EIGEN_INC_DIR bibli_eigen)
include_directories(${EIGEN_INC_DIR})

project(multi_threading)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES	../Correction/Correction/kalman-cpp/correcteur.cpp 
					main.cpp 
					multiThreading.cpp
					../tcp_client/ClientTCP.cpp 
					../tcp_client/ClientUDP.cpp 
					../tcp_client/FT_Client.cpp 
					../tcp_client/NetworkServices.cpp 
					../tcp_client/Robot_Client.cpp)
add_executable(main ${SOURCE_FILES})
