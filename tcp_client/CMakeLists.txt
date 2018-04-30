project(client_tcp)
add_executable(client_tcp
               main.cpp
               FT_Client.cpp
			   Robot_Client.cpp
			   ClientTCP.cpp
			   ClientUDP.cpp
			   NetworkServices.cpp)

