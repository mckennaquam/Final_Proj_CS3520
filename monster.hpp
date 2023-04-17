#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "item.hpp"

using namespace std;

namespace final_proj
{

    class Base_Monster
    {
    public:
        void take_damage(int const damage);
        virtual int deal_damage() const = 0;
        virtual string attack_type() const = 0;
        bool is_alive() const;
        int get_health() const;
        string get_name() const;
        int point_val() const;
        Item get_item() const;

        // empty destuctor for this class and its dervied classes
        virtual ~Base_Monster() {}

    protected:
        string m_name;
        int m_health;
        int m_stength;
        int m_defense;
        int m_points;
        Item m_equipped;
    };

    class Skeleton : public Base_Monster
    {
    public:
        int deal_damage() const override;
        string attack_type() const override;

        Skeleton()
        {
            m_name = "Skeleton";
            m_health = 25;
            m_stength = 10;
            m_defense = 0;
            m_points = 30;
            m_equipped = Item();

            if (m_equipped.m_type == "attack")
            {
                m_stength += m_equipped.m_stat;
            }
            else if (m_equipped.m_type == "defense")
            {
                m_defense += m_equipped.m_stat;
            }
        }
    };

    class Slime : public Base_Monster
    {
    public:
        int deal_damage() const override;
        string attack_type() const override;

        Slime()
        {
            m_name = "Slime";
            m_health = 20;
            m_stength = 4;
            m_defense = 0;
            m_points = 20;
            m_equipped = Item();
        }
    };

    class Lich : public Base_Monster
    {
    public:
        int deal_damage() const override;
        string attack_type() const override;

        Lich()
        {
            m_name = "Lich";
            m_health = 50;
            m_stength = 20;
            m_defense = 0;
            m_points = 55;
            m_equipped = Item("treasure", "crown", (rand() % 51) + 50);
        }
    };
}

#endif