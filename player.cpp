#include "player.hpp"
#include "exceptions.hpp"
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
        auto iter = inventory.find(name);

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
    vector<int> Player::check_stats()
    {
        vector<int> stat_vector;

        stat_vector.insert(stat_vector.begin(), m_defense);
        stat_vector.insert(stat_vector.begin(), m_strength);
        stat_vector.insert(stat_vector.begin(), m_health);

        return stat_vector;
    }

    /*
        // Return a set of a player's inventory
        set<Item > Player::check_inventory() {
            set<Item, Item_Rank> inventory;

            transform(cbegin(m_inventory), cend(m_inventory), back_inserter(inventory), [](const auto
            &element) { return element.second; });

            return inventory;
        }
    */
    void Player::pick_up_object(unique_ptr<Item> new_item)
    {
        // Check if item is type "health". If so, add it to the inventory
        if (new_item->m_type.compare("potion") == 0)
        {
            m_inventory.insert(m_inventory.end(), *new_item);

            // Check if item is type "strength". If so, set item into use if and only if it is a
            // "stronger" item
        }
        else if (new_item->m_type.compare("strength") == 0)
        {
            if (new_item->m_stat + m_baseStrength > m_strength)
            {
                m_strength = new_item->m_stat + m_baseStrength;
                // message that says we added it
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
            }
            else
            {
                throw InvalidUserInputException("The " + new_item->m_name + " you picked up is weak! You drop it an proceed on.");
            }
        }
        else
        {
            // item is treasure, add to points!
            m_points += new_item->m_stat;
        }
    }

    void Player::use_item(Item selected_item)
    {
        auto iter = find_item(m_inventory, selected_item.m_name);

        if (str_contains(selected_item.m_name, "attack"))
        {
            m_strength += selected_item.m_stat;
            m_in_use = make_unique<Item>(selected_item.m_name, selected_item.m_type, selected_item.m_stat);
        }
        else if (str_contains(selected_item.m_name, "defense"))
        {
            m_defense += selected_item.m_stat;
            m_in_use = make_unique<Item>(selected_item.m_name, selected_item.m_type, selected_item.m_stat);
        }
        else
        {
            // Ensure the player's health is below their max health
            if (m_health < m_maxHealth)
            {

                // Ensure the item will not set the player's health above their max health. If so,
                // set the player's health to their max health
                if (selected_item.m_stat + m_health > m_maxHealth)
                {
                    m_health = m_maxHealth;
                    m_inventory.erase(iter);

                    // If item will not surpass the max health, apply item normally
                }
                else
                {
                    m_health += selected_item.m_stat;
                    m_inventory.erase(iter);
                }
            }
            else
            {
                throw InvalidUserInputException("Your health is full!");
            }
        }
    }

    void Player::remove_buff()
    {
        if (m_in_use != nullptr)
        {
            if (m_in_use->m_name, "attack")
            {
                m_strength -= m_in_use->m_stat;
                m_in_use = nullptr;
            }
            else
            {
                m_defense -= m_in_use->m_stat;
                m_in_use = nullptr;
            }
        }
    }

    void Player::take_damage(int damage_taken)
    {
        m_health -= damage_taken;
    }
}
