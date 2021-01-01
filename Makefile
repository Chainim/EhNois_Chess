FLAGS = -std=c++17
LINKER_FLAGS = -lopengl32 -lgdi32 -lws2_32

.PHONY: run_client run_server

run_client: client.exe
	client.exe

run_server: server.exe
	server.exe

client.exe: src/client.cpp src/network.cpp src/board_utils.cpp src/window.cpp src/user_interface.cpp
	g++ $(FLAGS) -o client src/client.cpp src/network.cpp src/board_utils.cpp src/window.cpp src/user_interface.cpp $(LINKER_FLAGS)

server.exe: src/server.cpp src/network.cpp src/board_utils.cpp
	g++ $(FLAGS) -o server src/server.cpp src/network.cpp src/board_utils.cpp $(LINKER_FLAGS)