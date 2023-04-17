#include "monster.hpp"
#include "iostream"

using namespace std;

namespace final_proj
{
    void Base_Monster::take_damage(int damage)
    {
        m_health -= damage;
    }

    int Base_Monster::get_health() const
    {
        int health;
        if (m_health >= 0)
        {
            health = m_health;
        } else
        {
            health = 0;
        }
        return health;
    }

    bool Base_Monster::is_alive() const
    {
        return m_health > 0;
    }

    string Base_Monster::get_name() const
    {
        return m_name;
    }

    int Base_Monster::point_val() const
    {
        return m_points;
    }

    Item Base_Monster::get_item() const
    {
        return m_equipped;
    }

    int Skeleton::deal_damage() const
    {
        return m_stength / 2 + (rand() % m_stength);
    }

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

    string Skeleton::describe_enemy() const
    {
        int descriptions = rand() % 3;
        switch (descriptions)
        {
        case 0:
            return "The skeleton rattles their bones, stumbling fowards. His glowing green";
            //"eyes dimly light the room as they steadily approach you.";
            break;
        case 1:
            return "to do";
            break;
        case 2:
            return "to do";
            break;
        default:
            return "to do";
        }
    }

    int Slime::deal_damage() const
    {
        //to do stength
        return rand() % m_stength + 1;
    }

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

    string Slime::describe_enemy() const
    {
        int descriptions = rand() % 3;
        switch (descriptions)
        {
        case 0:
            return "to do";
            break;
        case 1:
            return "to do";
            break;
        case 2:
            return "to do";
            break;
        default:
            return "to do";
        }
    }

    int Lich::deal_damage() const
    {
        return m_stength / 2 + (rand() % m_stength);
    }

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

    string Lich::describe_enemy() const
    {
        int descriptions = rand() % 3;
        switch (descriptions)
        {
        case 0:
            return "to do";
        case 1:
            return "to do";
        case 2:
            return "to do";
        }
    }
}
