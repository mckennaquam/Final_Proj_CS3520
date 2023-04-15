#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "monster.hpp"
#include "item.hpp"
#include <string>
#include <memory>

using namespace std;

namespace final_proj
{
    class Base_Room
    {
    public:
        virtual bool answer_riddle(string answer);
        virtual void hit_monster(int damage);
        virtual bool monster_alive() const;
        virtual int montser_attack_damage() const;
        virtual string monster_attack_type() const;
        virtual string monster_name() const;
        virtual int monster_points() const;
        virtual string describe_room() const = 0;
        virtual unique_ptr<Item> remove_obj();
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
        unique_ptr<Item> remove_obj() override;

        Object_Room(int x, int y) : Base_Room(x, y, "Treasure")
        {
            m_item = make_unique<Item>();
        }

    protected:
        // constructor for derrived classes to use base room constructor for name
        Object_Room(int x, int y, string name) : Base_Room(x, y, name)
        {
            m_item = make_unique<Item>();
        }

        unique_ptr<Item> m_item;
    };

    class Riddle_Room : public Base_Room
    {
    public:
        bool answer_riddle(string answer) override;
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
        void hit_monster(int damage) override;
        bool monster_alive() const override;
        int montser_attack_damage() const override;
        string monster_attack_type() const override;
        string monster_name() const override;
        int monster_points() const override;
        string describe_room() const override;
        unique_ptr<Item> remove_obj() override;

        Combat_Room(int x, int y) : Object_Room(x, y, "Combat")
        {
            // gotta put the monster stuff here
        }

    private:
        unique_ptr<Base_Monster> m_enemy;
    };
}

#endif