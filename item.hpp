#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "exceptions.hpp"
#include <string>
#include <cstdlib>

//to delete
#include <iostream>

using namespace std;

namespace
{
    string generate_name_weapon()
    {
        int name = rand() % 5;

        if (name == 0)
        {
            return "Sword";
        }
        else if (name == 1)
        {
            return "Dagger";
        }
        else if (name == 2)
        {
            return "Bow";
        }
        else if (name == 3)
        {
            return "Battle Ax";
        }
        else if (name == 4)
        {
            return "Flail";
        }
        else
        {
            return "error";
        }
    }

    string generate_name_defense()
    {
        int name = rand() % 5;
        if (name == 0)
        {
            return "Shield";
        }
        else if (name == 1)
        {
            return "Helmet";
        }
        else if (name == 2)
        {
            return "Breastplate";
        }
        else if (name == 3)
        {
            return "Greaves";
        }
        else if (name == 4)
        {
            return "Chainmail";
        }
        else
        {
            return "error";
        }
    }

    string generate_name_treasure()
    {
        int name = rand() % 5;
        if (name == 0)
        {
            return "Gold";
        }
        else if (name == 1)
        {
            return "Jewels";
        }
        else if (name == 2)
        {
            return "a Sense of Satisfaction";
        }
        else if (name == 3)
        {
            return "Faberge egg";
        }
        else if (name == 4)
        {
            return "Doubloons";
        }
        else
        {
            return "error";
        }
    }
}

namespace final_proj
{
    struct Item
    {
        string m_name;
        string m_type;
        int m_stat;

        Item(string name, string type, int stat)
        {
            m_name = name;
            m_type = type;
            m_stat = stat;
        }

        Item()
        {
            int type = rand() % 101;
            if (type <= 10)
            {
                m_type = "weapon";
                m_name = generate_name_weapon();
                m_stat = (rand() % 20) + 1;
            }
            else if (type > 10 && type <= 20)
            {
                m_type = "defense";
                m_name = generate_name_defense();
                m_stat = (rand() % 20) + 1;
            }
            else if (type > 20 && type <= 40)
            {
                m_type = "potion";
                m_stat = (rand() % 10) + 1;

                int name = rand() % 3;
                if (name == 0)
                {
                    m_name = "Health rank " + to_string(m_stat);
                }
                else if (name == 1)
                {
                    m_name = "Attack rank " + to_string(m_stat);
                }
                else if (name == 2)
                {
                    m_name = "Defense rank " + to_string(m_stat);
                }
                else
                {
                    m_name = "error";
                }
            }
            else
            {
                m_type = "treasure";
                m_name = generate_name_treasure();
                m_stat = (rand() % 50) + 1;
            }
        }

        bool operator==(const Item &rhs) const
        {
            return m_name == rhs.m_name;
        }
    };

}

#endif