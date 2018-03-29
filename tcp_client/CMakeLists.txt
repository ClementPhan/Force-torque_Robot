project(client_tcp)
add_executable(client_tcp
               main.cpp
               FT_Client.cpp
			   ClientNetwork.cpp
			   NetworkServices.cpp)

