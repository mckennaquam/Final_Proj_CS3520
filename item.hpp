#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

using namespace std;

namespace
{
    string generate_name_damage()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "sword";
        case 1:
            return "dagger";
        case 2:
            return "bow";
        case 3:
            return "battle axe";
        case 4:
            return "flail";
        }
    }

    string generate_name_defense()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "shield";
        case 1:
            return "helmet";
        case 2:
            return "breastplate";
        case 3:
            return "greaves";
        case 4:
            return "chainmail";
        }
    }

    string generate_name_treasure()
    {
        int name = rand() % 5;
        switch (name)
        {
        case 0:
            return "gold";
        case 1:
            return "jewels";
        case 2:
            return "faberge egg";
        case 3:
            return "doubloons";
        case 4:
            return "a sense of satisfaction";
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

        Item()
        {
            int type = rand() % 101;
            if (type >= 10)
            {
                m_type = "damage";
                m_name = generate_name_damage();
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
                    m_name = "health";
                case 1:
                    m_name = "attack";
                case 2:
                    m_name = "defense";
                }
            }
            else
            {
                m_type = "treasure";
                m_name = generate_name_treasure();
                m_stat = (rand() % 50) + 1;
            }
        }
    };

}

#endif