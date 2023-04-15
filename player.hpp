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

    public:
        // public methods for the player
        vector<int> check_stats() const;
        vector<string> check_inventory() const;
        int get_strength() const;
        void pick_up_object(unique_ptr<Item> new_item);
        void use_item(string item_name);
        void take_damage(int damage_taken);
        void remove_buff();
        shared_ptr<Base_Room> get_current_room() const;
        void update_location(shared_ptr<Base_Room> new_room);
        bool player_alive() const;
        void update_points(int points);

        // custom constrctor for player
        Player()
        {
            m_maxHealth = 100;
            m_baseStrength = 10;
            m_baseDefense = 0;
            m_health = m_maxHealth;
            m_strength = m_baseStrength;
            m_defense = m_baseDefense;
            m_inventory = vector<Item>();
            m_in_use = nullptr;
            m_points = 0;
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
        unique_ptr<Item> m_in_use;
        shared_ptr<Base_Room> m_current_room;
    };

}

#endif