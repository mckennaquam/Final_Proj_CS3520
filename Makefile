CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

all: game

game: monster.hpp player.cpp player.hpp room_factory.hpp room.cpp room_factory.cpp room.hpp main.cpp item.hpp
	$(CXX) $(CXXFLAGS) player.cpp room.cpp main.cpp room_factory.cpp -o $@

.PHONY: clean all
clean:
	rm -vf game
