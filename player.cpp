#include "player.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// Empty namespace for helper methods
namespace
{
    bool str_contains(const string &str, const string &search_for)
    {
        // string::npos plays a similar role to the "end" iterator
        // for containers, but its value is *not* one-past-the-end.
        // string::find returns string::npos if the requested string
        // could not be found.
        return str.find(search_for) != string::npos;
    }

    // Returns an iterator pointing to the element in the given container
    // identified by the given Album name.
    // Throws InvalidUserInputException if that element
    // doesn't exist in the container.
    template <typename Container>
    auto find_item(Container &inventory, const string &name)
    {
        final_proj::Item compare = final_proj::Item(name, 0, 0);

        auto iter = find(cbegin(inventory), cend(inventory), compare);

        throw final_proj::InvalidUserInputException("Item " + name + " not found");

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

        transform(cbegin(m_inventory), cend(m_inventory), back_inserter(inventory), [](const auto &element)
                  { return element.m_name; });

        return inventory;
    }

    void Player::pick_up_object(shared_ptr<Item> &new_item)
    {
        // Check if item is type "health". If so, add it to the inventory
        if (new_item->m_type.compare("potion") == 0)
        {
            m_inventory.insert(m_inventory.end(), *new_item);

            cout << "You pick up the potion of " + new_item->m_name + ", to use it type the command \"use " + new_item->m_name + "\"";

            // Check if item is type "strength". If so, set item into use if and only if it is a
            // "stronger" item
        }
        else if (new_item->m_type.compare("weapon") == 0)
        {
            if (new_item->m_stat + m_baseStrength > m_strength)
            {
                m_strength = new_item->m_stat + m_baseStrength;

                // message that says we added it
                cout << "You pick up the " + new_item->m_name + "! Your strength is now " + to_string(m_strength) << endl;
            }
            else
            {
                throw InvalidUserInputException("The " + new_item->m_name + " you picked up is weak! You drop it an proceed on.");
            }

            // Check if item is type "defense". If so, set item into use if and only if it is a
            // "stronger" item
        }
        else if (new_item->m_type.compare("defense") == 0)
        {
            if (new_item->m_stat > m_defense)
            {
                m_defense = new_item->m_stat;
                // message that says we added it
                cout << "You pick up the " + new_item->m_name + "! Your defense is now " + to_string(m_defense) << endl;
            }
            else
            {
                throw InvalidUserInputException("The " + new_item->m_name + " you picked up is weak! You drop it an proceed on.");
            }
        }
        else if (new_item->m_type == "treasure")
        {
            // item is treasure, add to points!
            m_points += new_item->m_stat;
            cout << "You pick up the " + new_item->m_name + "! Your score is now " + to_string(m_points) << endl;
        }
        else
        {
            throw UnsupportedBehavoir("type of item not regonized - player pick up item");
        }
    }

    void Player::use_item(string &item_name)
    {
        auto iter = find_item(m_inventory, item_name);

        if (str_contains(iter->m_name, "attack"))
        {
            m_strength += iter->m_stat;
            m_in_use = make_unique<Item>(iter->m_name, iter->m_type, iter->m_stat);
            m_inventory.erase(iter);
        }
        else if (str_contains(iter->m_name, "defense"))
        {
            m_defense += iter->m_stat;
            m_in_use = make_unique<Item>(iter->m_name, iter->m_type, iter->m_stat);
            m_inventory.erase(iter);
        }
        else if (str_contains(iter->m_name, "health"))
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

                    // If item will not surpass the max health, apply item normally
                }
                else
                {
                    m_health += iter->m_stat;
                    m_inventory.erase(iter);
                }
            }
            else
            {
                throw InvalidUserInputException("Your health is full!");
            }
        }
        else
        {
            throw UnsupportedBehavoir("type of object not regonized - player use item");
        }
    }

    void Player::remove_buff()
    {
        if (m_in_use != nullptr)
        {
            if (str_contains(m_in_use->m_name, "attack"))
            {
                m_strength -= m_in_use->m_stat;
                m_in_use = nullptr;
            }
            else if (str_contains(m_in_use->m_name, "defense"))
            {
                m_defense -= m_in_use->m_stat;
                m_in_use = nullptr;
            }
            else
            {
                throw UnsupportedBehavoir("type of object not recognized - player remove buff");
            }
        }
    }

    void Player::take_damage(int damage_taken)
    {
        m_health -= damage_taken;
    }

    void Player::update_location(shared_ptr<Base_Room> &new_room)
    {
        m_current_room = new_room;
    }

    void Player::update_points(int points)
    {
        m_points += points;
    }

    int Player::get_strength() const
    {
        return m_baseStrength;
    }

    bool Player::player_alive() const
    {
        return m_health > 0;
    }

    shared_ptr<Base_Room> Player::get_current_room() const
    {
        return m_current_room;
    }

    int Player::get_points() const
    {
        return m_points;
    }
}
