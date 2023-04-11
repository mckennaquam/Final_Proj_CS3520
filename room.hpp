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
        virtual bool answer_riddle(string answer) = 0;
        virtual void hit_monster(int damage) = 0;
        virtual bool monster_alive() const = 0;
        virtual string describe_room() const = 0;
        virtual Item remove_obj() = 0;
        virtual string room_type() const = 0;
        int get_x() const;
        int get_y() const;
        string get_type() const;

        Base_Room(int x, int y, string type)
        {
            m_x = x;
            m_y = y;
            m_type = type;
        }

    protected:
        int m_x;
        int m_y;
        string m_type;
    };

    class Object_Room : public Base_Room
    {
    public:
        bool answer_riddle(string answer) override;
        void hit_monster(int damage) override;
        bool monster_alive() const override;
        string describe_room() const override;
        Item remove_obj() override;

        Object_Room(int x, int y) : Base_Room(x, y, "Treasure")
        {
            m_item = Item();
        }

    protected:
        Item m_item;
    };

    class Riddle_Room : public Base_Room
    {
    public:
        bool answer_riddle(string answer) override;
        void hit_monster(int damage) override;
        bool monster_alive() const override;
        string describe_room() const override;
        Item remove_obj() override;
        string room_type() const;

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
        bool answer_riddle(string answer);
        void hit_monster(int damage);
        bool monster_alive() const;
        string describe_room() const;
        Item remove_obj();
        string room_type() const;

        Combat_Room(int x, int y) : Object_Room(x, y)
        {
            // gotta put the monster stuff here
        }

    private:
        Base_Monster m_enemy;
    };
}

#endif