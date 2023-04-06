#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "monster.hpp"
#include "item.hpp"
#include <string>

using namespace std;

namespace final_proj
{
    class Base_Room
    {
    public:
        void answer_riddle();
        void hit_monster();
        void enter_room();
        string describe_room();
        pair<int, int> location();

    private:
        int m_x;
        int m_y;
    };

    class Object_Room : public Base_Room
    {
    public:
    private:
        Item m_item;
    };

    class Riddle_Room : public Base_Room
    {
    public:
    private:
        string m_riddle;
        string m_answer;
    };

    class Combat_Room : public Object_Room
    {
    public:
    private:
        Base_Monster m_enemy;
    };
}

#endif