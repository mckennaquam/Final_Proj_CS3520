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
        void take_damage(int damage_taken);

    public:
        // custom constrctor for player
        Player()
        {
            m_maxHealth = 100;
            m_baseStrength = 50;
            m_baseDefense = 0;
            m_health = m_maxHealth;
            m_strength = m_baseStrength;
            m_defense = m_baseDefense;
            m_inventory = vector<Item>();
        }

        // private fields for player
    private:
        int m_maxHealth;
        int m_baseStrength;
        int m_baseDefense;
        int m_health;
        int m_strength;
        int m_defense;
        int m_points;
        vector<Item> m_inventory;
        shared_ptr<Base_Room> m_current_room;
    };

}

#endif