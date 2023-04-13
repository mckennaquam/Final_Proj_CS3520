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
        bool answer_riddle(string answer);
        void hit_monster(int damage);
        bool monster_alive() const;
        int montser_attack_damage() const;
        string monster_attack_type() const;
        virtual string describe_room() const = 0;
        unique_ptr<Item> remove_obj();
        string room_type() const;
        int get_x() const;
        int get_y() const;
        string get_type() const;

    protected:
        Base_Room(int x, int y, string type)
        {
            m_x = x;
            m_y = y;
            m_type = type;
        }

        int m_x;
        int m_y;
        string m_type;
    };

    class Object_Room : public Base_Room
    {
    public:
        string describe_room() const override;
        unique_ptr<Item> remove_obj();

        Object_Room(int x, int y) : Base_Room(x, y, "Treasure")
        {
            m_item = make_unique<Item>();
        }

    protected:
        unique_ptr<Item> m_item;
    };

    class Riddle_Room : public Base_Room
    {
    public:
        bool answer_riddle(string answer);
        string describe_room() const override;

        Riddle_Room(int x, int y, string riddle, string answer) : Base_Room(x, y, "Riddle")
        {
            m_riddle = riddle;
            m_answer = answer;
        }

    private:
        string m_riddle;
        string m_answer;
    };

    class Combat_Room : public Object_Room
    {
    public:
        void hit_monster(int damage);
        bool monster_alive() const;
        int montser_attack_damage() const;
        string monster_attack_type() const;
        string describe_room() const;
        unique_ptr<Item> remove_obj();

        Combat_Room(int x, int y) : Object_Room(x, y)
        {
            // gotta put the monster stuff here
        }

    private:
        Base_Monster m_enemy;
    };
}

#endif