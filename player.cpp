#include "player.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// A class representing a Player

// Empty namespace for helper methods
namespace
{
    // Returns a bool, indicating whether or not a string contains a sought after string
    bool str_contains(const string &str, const string &search_for)
    {
        return str.find(search_for) != string::npos;
    }

    // Returns an iterator pointing to the element in the given container
    // identified by the given item name, type, and stat.
    // Throws InvalidUserInputException if that element
    // doesn't exist in the container.
    template <typename Container>
    auto find_item(Container &inventory, const string &name, string &type, int &stat)
    {
        final_proj::Item compare = final_proj::Item(name, type, stat);

        auto iter = find(cbegin(inventory), cend(inventory), compare);

        if (iter == cend(inventory))
        {
            throw final_proj::InvalidUserInputException("Item " + name + " not found");
        }

        return iter;
    }
}

namespace final_proj
{

    // Return a vector of the current stats of the player, ie. their health, strength, and defense
    vector<int> Player::check_stats() const
    {
        vector<int> stat_vector;

        stat_vector.insert(stat_vector.begin(), m_defense);
        stat_vector.insert(stat_vector.begin(), m_strength);
        stat_vector.insert(stat_vector.begin(), m_health);

        return stat_vector;
    }

    // Return a set of a player's inventory
    vector<string> Player::check_inventory() const
    {
        vector<string> inventory;

        transform(cbegin(m_inventory), cend(m_inventory), back_inserter(inventory), 
        [](const auto &element)
                  { return element.m_name; });

        return inventory;
    }

    // Performs an alloted action depending on the type of a given item
    void Player::pick_up_object(shared_ptr<Item> &new_item)
    {
        // Check if item is type "health". If so, add it to the inventory
        if (new_item->m_type.compare("potion") == 0)
        {
            m_inventory.insert(m_inventory.end(), *new_item);

            cout << "You pick up the potion of " + new_item->m_name + ", to use it type the "
            "command \"use " + new_item->m_name + "\"\n" << endl;

        }
        // Check if item is type "strength". If so, set item into use if and only if it is a
        // "stronger" item
        // Throws an InvalidUserInputException if the given item is weaker than a player's prior 
        // strength
        else if (new_item->m_type.compare("weapon") == 0)
        {
            if (new_item->m_stat + m_baseStrength > m_strength)
            {
                m_strength = new_item->m_stat + m_baseStrength;

                cout << "You pick up the " + new_item->m_name + "! Your strength is now " + 
                to_string(m_strength)  + ".\n"<< endl;
            }
            else
            {
                throw InvalidUserInputException("The " + new_item->m_name + " you picked up is "
                "weak! You drop it an proceed on.\n");
            }
        }
        // Check if item is type "defense". If so, set item into use if and only if it is a
        // "stronger" item
        // Throws an InvalidUserInputException if the given item is weaker than a player's prior 
        // defense
        else if (new_item->m_type.compare("defense") == 0)
        {
            if (new_item->m_stat > m_defense)
            {
                m_defense = new_item->m_stat;
                // message that says we added it
                cout << "You pick up the " + new_item->m_name + "! Your defense is now " + 
                to_string(m_defense)  + ".\n"<< endl;
            }
            else
            {
                throw InvalidUserInputException("The " + new_item->m_name + " you picked up is "
                "weak! You drop it an proceed on.\n");
            }
        }
        // Checks if the item is type "treasure". If so, adds the alloted point value to the
        // player's total points
        else if (new_item->m_type == "treasure")
        {
            m_points += new_item->m_stat;
            cout << "You pick up the " + new_item->m_name + "! Your score is now " + 
            to_string(m_points) + ".\n" << endl;
        }
        else
        {
            throw UnsupportedBehavoir("type of item not regonized - player pick up item");
        }
    }

    // "Uses" an item, performance is dependent on the type of the object
    void Player::use_item(string &item_name, string &item_type, int &item_stat)
    {
        auto iter = find_item(m_inventory, item_name, item_type, item_stat);

        // If type "Attack", adds the stat of the item to a player's attack
        if (str_contains(iter->m_name, "Attack"))
        {
            m_strength += iter->m_stat;
            m_in_use = make_unique<Item>(iter->m_name, iter->m_type, iter->m_stat);
            m_inventory.erase(iter);
            m_is_item_in_use = true;
            cout << "You used your " + item_name + "! Your attack is now " + 
            to_string(m_strength) + "." << endl;
            cout << "If you enter a combat room, and then exit, your buff will be lost! Be "
            "careful...\n" << endl;
        }
        // If type "Defense", adds the stat of the item to a player's attack
        else if (str_contains(iter->m_name, "Defense"))
        {
            m_defense += iter->m_stat;
            m_in_use = make_unique<Item>(iter->m_name, iter->m_type, iter->m_stat);
            m_inventory.erase(iter);
            m_is_item_in_use = true;
            cout << "You used your " + item_name + "! Your defense is now " + to_string(m_defense) + 
            "." << endl;
            cout << "If you enter a combat room, and then exit, your buff will be lost! Be "
            "careful...\n" << endl;
        }
        // If type "Health", adds the stat of the item to a player's attack
        else if (str_contains(iter->m_name, "Health"))
        {
            // Ensure the player's health is below their max health
            if (m_health < m_maxHealth)
            {
                // Ensure the item will not set the player's health above their max health. If so,
                // set the player's health to their max health
                if (iter->m_stat + m_health > m_maxHealth)
                {
                    m_health = m_maxHealth;
                    m_inventory.erase(iter);
                    cout << "You used your " + item_name + "! Your health is now " + 
                    to_string(m_health) + ".\n" << endl;

                }
                // If item will not surpass the max health, apply item normally
                else
                {
                    m_health += iter->m_stat;
                    m_inventory.erase(iter);
                    cout << "You used your " + item_name + "! Your health is now " + 
                    to_string(m_health) + ".\n" << endl;
                }
            }
            // Throws an InvalidUserInputException if the player is using a health-increasing item 
            // and if their health is full
            else
            {
                throw InvalidUserInputException("Your health is full! No need to use this item.\n");
            }
        }
        else
        {
            throw UnsupportedBehavoir("type of object not regonized - player use item");
        }
    }

    // Removes a buff added on from using an item from the player's stats
    // Fetches the item in use, if not null, utilizes those values to reset the player's stats
    void Player::remove_buff()
    {
        if (m_in_use != nullptr)
        {
            if (str_contains(m_in_use->m_name, "Attack"))
            {
                m_strength -= m_in_use->m_stat;
                m_in_use = nullptr;
                m_is_item_in_use = false;
            }
            else if (str_contains(m_in_use->m_name, "Defense"))
            {
                m_defense -= m_in_use->m_stat;
                m_in_use = nullptr;
                m_is_item_in_use = false;
            }
            else
            {
                throw UnsupportedBehavoir("type of object not recognized - player remove buff");
            }
        }
    }

    // Apply damage to a player. Subtracts a given damage from the player's health
    void Player::take_damage(int damage_taken)
    {
        m_health -= damage_taken;
        cout << "Your health is now: " + to_string(m_health) + ""<< endl;
    }

    // Updates the player's location of the current room to a given new room
    void Player::update_location(shared_ptr<Base_Room> &new_room)
    {
        m_current_room = new_room;
    }

    // Updates the player's points to be equivalent to their prior point value + a given point value
    void Player::update_points(int points)
    {
        m_points += points;
    }

    // Returns an int of the player's current strength
    int Player::get_strength() const
    {
        return m_strength;
    }

    // Returns a bool indicating whether or not the player is alive, which is if their health is
    // above 0
    bool Player::player_alive() const
    {
        return m_health > 0;
    }

    // Returns a shared_ptr<Base_Room> that is the current room the player is in
    shared_ptr<Base_Room> Player::get_current_room() const
    {
        return m_current_room;
    }

    // Returns an int of the player's current point value
    int Player::get_points() const
    {
        return m_points;
    }

    // Returns a bool indicating the value refering to whether or not the player has an item in use
    bool Player::is_item_in_use() const
    {
        return m_is_item_in_use;
    }
}
