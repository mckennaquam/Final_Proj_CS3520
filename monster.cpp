#include "monster.hpp"

using namespace std;

namespace final_proj
{
    void Base_Monster::take_damage(int damage)
    {
        m_health -= damage;
    }

    bool Base_Monster::is_alive() const
    {
        return m_health > 0;
    }

    string Base_Monster::get_name() const
    {
        return m_name;
    }
}
