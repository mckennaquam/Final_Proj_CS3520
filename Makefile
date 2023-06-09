CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

all: game

game: monster.hpp player.cpp player.hpp room_factory.hpp room.cpp room_factory.cpp room.hpp main.cpp item.hpp monster.cpp
	$(CXX) $(CXXFLAGS) player.cpp room.cpp main.cpp room_factory.cpp monster.cpp -o $@

player_tests.exe: player.cpp player.hpp room.cpp room.hpp item.hpp player_tests.cpp monster.cpp monster.hpp
	$(CXX) $(CXXFLAGS) player.cpp room.cpp player_tests.cpp monster.cpp -o $@

room_factory_tests.exe: player.cpp player.hpp room.cpp room.hpp item.hpp room_factory_tests.cpp monster.cpp monster.hpp room_factory.hpp room_factory.cpp
	$(CXX) $(CXXFLAGS) player.cpp room.cpp room_factory.cpp room_factory_tests.cpp monster.cpp -o $@

room_tests.exe: player.cpp player.hpp room.cpp room.hpp item.hpp room_tests.cpp monster.cpp monster.hpp 
	$(CXX) $(CXXFLAGS) player.cpp room.cpp room_tests.cpp monster.cpp -o $@

monster_tests.exe: player.cpp player.hpp room.cpp room.hpp item.hpp monster_tests.cpp monster.cpp monster.hpp 
	$(CXX) $(CXXFLAGS) player.cpp room.cpp monster_tests.cpp monster.cpp -o $@

main.exe: monster.cpp player.cpp room.cpp room_factory.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean all
clean:
	rm -vf game
