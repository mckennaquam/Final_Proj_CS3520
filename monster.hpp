#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "item.hpp"

using namespace std;

// A class representing a monster

namespace final_proj
{

    // A class representing a Base_Monster
    class Base_Monster
    {
        // public methods for the Base_Monster
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

        // protected fields for the Base_Monster
    protected:
        string m_name;
        int m_health;
        int m_strength;
        int m_defense;
        int m_points;
        Item m_equipped;
    };

    // A class representing a Skeleton, derived from Base_Monster
    class Skeleton : public Base_Monster
    {
        // public methods for the Skeleton, derived from Base_Monster
    public:
        int deal_damage() const override;
        string attack_type() const override;

        // Custom constructor for Skeleton, defining it's name, stats, point value, and 
        // equiped item.
        Skeleton()
        {
            m_name = "Skeleton";
            m_health = 25;
            m_strength = 10;
            m_defense = 0;
            m_points = 30;
            m_equipped = Item();

            // Equips the item if they are non-potion items
            if (m_equipped.m_type == "attack")
            {
                m_strength += m_equipped.m_stat;
            }
            else if (m_equipped.m_type == "defense")
            {
                m_defense += m_equipped.m_stat;
            }
        }
    };

    // A class representing a Slime, derived from Base_Monster
    class Slime : public Base_Monster
    {
        // public methods for the Slime, derived from Base_Monster
    public:
        int deal_damage() const override;
        string attack_type() const override;

        // Custom constructor for Slime, defining it's name, stats, point value, and 
        // equiped item. Slimes are the weakest mob, and do not equip their item.
        Slime()
        {
            m_name = "Slime";
            m_health = 20;
            m_strength = 4;
            m_defense = 0;
            m_points = 20;
            m_equipped = Item();
        }
    };

    // A class representing a Lich, derived from Base_Monster
    class Lich : public Base_Monster
    {
        // public methods for the Lich, derived from Base_Monster
    public:
        int deal_damage() const override;
        string attack_type() const override;

        // Custom constructor for Lich, defining it's name, stats, point value, and 
        // equiped item.        
        Lich()
        {
            m_name = "Lich";
            m_health = 50;
            m_strength = 20;
            m_defense = 0;
            m_points = 55;
            // Lich are automatically equipped with a large point value item
            m_equipped = Item("Crown", "treasure", (rand() % 51) + 50);
        }
    };
}

#endif