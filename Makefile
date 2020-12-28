FLAGS = -std=c++17
LINKER_FLAGS = -lopengl32 -lws2_32

.PHONY: client.exe server.exe

client.exe: src/client.cpp src/network.cpp
	g++ $(FLAGS) -o client src/client.cpp src/network.cpp $(LINKER_FLAGS)

server.exe: src/server.cpp
	g++ $(FLAGS) -o server src/server.cpp src/network.cpp $(LINKER_FLAGS)