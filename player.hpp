#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <set>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "room.hpp"
#include "item.hpp"

using namespace std;

namespace final_proj
{

    // class to represent the player
    class Player
    {
        // public methods for the player
        vector<int> check_stats();
        vector<Item> check_inventory();
        void pick_up_object(Item new_item);
        void use_item(Item selected_item);

    public:
        // custom constrctor for player
        Player(int &health, int &strength, int &defense)
        {
            m_health = m_maxHealth;
            m_strength = strength;
            m_defense = defense;
            m_maxHealth = 100;
            m_inventory = vector<Item>();
        }

        // private fields for player
    private:
        int m_health;
        int m_strength;
        int m_defense;
        int m_maxHealth;
        int m_points;
        vector<Item> m_inventory;
        shared_ptr<Base_Room> m_current_room;
    };

}

#endif