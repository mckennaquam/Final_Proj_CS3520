#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "item.hpp"

using namespace std;

namespace final_proj
{
    class Player;

    class Base_Monster
    {
    public:
        void take_damage(int damage);
        int deal_damage() const;
        bool is_alive() const;
        string get_name() const;

    private:
        string name;
        int m_health;
        int m_stength;
        int m_points;
        Item equipped;
    };
}

#endif