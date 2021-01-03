CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lopengl32 -lgdi32 -lws2_32

.PHONY: run_client run_server

run_client: client.exe
	client.exe

run_server: server.exe
	server.exe

client.exe: src/client.cpp src/network.cpp src/board_utils.cpp src/window.cpp src/user_interface.cpp src/file_io.cpp
	$(CXX) $(CXXFLAGS) -o client $^ $(LDFLAGS)

server.exe: src/server.cpp src/network.cpp src/board_utils.cpp
	$(CXX) $(CXXFLAGS) -o server $^ $(LDFLAGS)