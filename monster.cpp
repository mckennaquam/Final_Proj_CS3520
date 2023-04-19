#include "monster.hpp"
#include "iostream"

using namespace std;

// A class representing a monster

namespace final_proj
{
    // subtracts a given damage from a monster's health
    void Base_Monster::take_damage(int const damage)
    {
        m_health -= damage;
    }

    // returns an integer describing the health of a monster. If the health is less than 0, returns
    // 0 as the monster's health. Otherwise, returns the monster's health.
    int Base_Monster::get_health() const
    {
        int health;
        if (m_health >= 0)
        {
            health = m_health;
        }
        else
        {
            health = 0;
        }
        return health;
    }

    // returns a bool describing if the monster's health is above 0, indicating if it is "alive"
    bool Base_Monster::is_alive() const
    {
        return m_health > 0;
    }

    // returns a string describing the monster's name
    string Base_Monster::get_name() const
    {
        return m_name;
    }

    // returns an integer describing the monster's point value
    int Base_Monster::point_val() const
    {
        return m_points;
    }

    // returns an Item describing the item a monster is holding
    Item Base_Monster::get_item() const
    {
        return m_equipped;
    }

    // returns an integer describing the amount of damage a Skeleton mob will deal. This amount of 
    // damage is equivalent to half of the Skeleton's base strength, plus a randomized value of
    // the Skeleton's total strength
    int Skeleton::deal_damage() const
    {
        return m_strength / 2 + (rand() % m_strength);
    }

    // returns a string describing a Skeleton's attack type, which is randomized with favor towards
    // pierce
    string Skeleton::attack_type() const
    {
        int attack = rand() % 100;
        if (attack <= 25)
        {
            return "bludgeon";
        }
        else if (attack > 25 && attack <= 50)
        {
            return "slash";
        }
        else
        {
            return "pierce";
        }
    }

    // returns an integer describing the amount of damage a Slime mob will deal. This amount of 
    // damage is equivalent to a randomized integer of the Slime's base strength
    int Slime::deal_damage() const
    {
        return rand() % m_strength + 1;
    }

    // returns a string describing a Slime's attack type, which is randomized with favor towards
    // bludgeon
    string Slime::attack_type() const
    {
        int attack = rand() % 100;

        if (attack <= 25)
        {
            return "pierce";
        }
        else if (attack > 25 && attack <= 50)
        {
            return "slash";
        }
        else
        {
            return "bludgeon";
        }
    }

    // returns an integer describing the amount of damage a Lich mob will deal. This amount of 
    // damage is equivalent to half of the Lich's base strength, plus a randomized value of
    // the Lich's total strength
    int Lich::deal_damage() const
    {
        return m_strength / 2 + (rand() % m_strength);
    }

    // returns a string describing a Lich's attack type, which is completely randomized
    string Lich::attack_type() const
    {
        int attack = rand() % 3;
        if (attack == 0)
        {
            return "pierce";
        }
        else if (attack == 1)
        {
            return "slash";
        }
        else if (attack == 2)
        {
            return "bludgeon";
        }
        else
        {
            return "error";
        }
    }
}
