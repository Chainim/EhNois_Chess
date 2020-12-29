FLAGS = -std=c++17
LINKER_FLAGS = -lopengl32 -lws2_32

.PHONY: run_client run_server

run_client: client.exe
	client.exe

run_server: server.exe
	server.exe

client.exe: src/client.cpp src/network.cpp
	g++ $(FLAGS) -o client src/client.cpp src/network.cpp $(LINKER_FLAGS)

server.exe: src/server.cpp src/network.cpp
	g++ $(FLAGS) -o server src/server.cpp src/network.cpp $(LINKER_FLAGS)