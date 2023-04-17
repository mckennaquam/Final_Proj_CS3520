#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "monster.hpp"
#include "item.hpp"
#include <string>
#include <memory>

using namespace std;

// A class representing a room

namespace final_proj
{
    class Base_Room
    {
        // public methods for the Base_Room
    public:
        virtual bool answer_riddle(string &answer);
        virtual void hit_monster(int damage);
        virtual bool monster_alive() const;
        virtual int montser_attack_damage() const;
        virtual string monster_attack_type() const;
        virtual string monster_name() const;
        virtual int monster_points() const;
        virtual string describe_room() const = 0;
        virtual shared_ptr<Item> remove_obj();
        int get_x() const;
        int get_y() const;
        string get_type() const;
        bool room_visited() const;
        void visit_room();

        // empty destuctor for this class and it's derived classes
        virtual ~Base_Room() {}

        // protcted fields for Base_Room
    protected:
        Base_Room(int x, int y, string type)
        {
            m_x = x;
            m_y = y;
            m_type = type;
            m_seed = rand() % 3;
            // 0, 0 position starts as visited
            m_visited = (m_x == 0 && m_y == 0);
        }

        int m_x;
        int m_y;
        string m_type;
        int m_seed;
        bool m_visited;
    };

    class Object_Room : public Base_Room
    {
    public:
        string describe_room() const override;
        shared_ptr<Item> remove_obj() override;

        Object_Room(int x, int y) : Base_Room(x, y, "Treasure")
        {
            m_item = make_shared<Item>();
        }

        Object_Room(int x, int y, Item &item) : Base_Room(x, y, "Treasure")
        {
            m_item = make_shared<Item>(item);
        }

    protected:
        // constructor for derrived classes to use base room constructor for name
        // and do custom item
        Object_Room(int x, int y, string name) : Base_Room(x, y, name)
        {
            // m_item = make_shared<Item>(item);
        }

        shared_ptr<Item> m_item;
    };

    class Riddle_Room : public Base_Room
    {
    public:
        bool answer_riddle(string &answer) override;
        string describe_room() const override;

        Riddle_Room(int x, int y, string riddle, string answer) : Base_Room(x, y, "Riddle")
        {
            m_riddle = riddle;
            m_answer = answer;
            m_has_been_answered = false;
        }

    private:
        string m_riddle;
        string m_answer;
        bool m_has_been_answered;
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
        shared_ptr<Item> remove_obj() override;

        Combat_Room(int x, int y) : Object_Room(x, y, "Combat")
        {
            // gotta put the monster stuff here
            int random = rand() % 100;

            if (random <= 10)
            {
                m_enemy = make_unique<Lich>();
            }
            else if (random > 10 && random <= 55)
            {
                m_enemy = make_unique<Skeleton>();
            }
            else if (random > 55 && random <= 100)
            {
                m_enemy = make_unique<Slime>();
            }
            else
            {
                throw UnsupportedBehavoir("tried make a randomized enemy - combat room constructor");
            }

            m_item = make_shared<Item>(m_enemy->get_item());
        }

    private:
        unique_ptr<Base_Monster> m_enemy;
    };
}

#endif