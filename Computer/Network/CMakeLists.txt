cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(client_tcp)
add_executable(client_tcp
               main.cpp
               FT_Client.cpp
			   Robot_Client.cpp
			   Network_Core/ClientTCP.cpp
			   Network_Core/ClientUDP.cpp
			   Network_Core/NetworkServices.cpp)

