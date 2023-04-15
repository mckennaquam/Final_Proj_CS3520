#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

using namespace std;

namespace
{
    string generate_name_weapon()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "Sword";
        case 1:
            return "Dagger";
        case 2:
            return "Bow";
        case 3:
            return "Battle Axe";
        case 4:
            return "Flail";
        }
    }

    string generate_name_defense()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "Shield";
        case 1:
            return "Helmet";
        case 2:
            return "Breastplate";
        case 3:
            return "Greaves";
        case 4:
            return "Chainmail";
        }
    }

    string generate_name_treasure()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "Gold";
        case 1:
            return "Jewels";
        case 2:
            return "Faberge egg";
        case 3:
            return "Doubloons";
        case 4:
            return "a Sense of Satisfaction";
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
            if (type >= 10)
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
                switch (name)
                {
                case 0:
                    m_name = "health rank " + to_string(m_stat);
                case 1:
                    m_name = "attack rank " + to_string(m_stat);
                case 2:
                    m_name = "defense rank " + to_string(m_stat);
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