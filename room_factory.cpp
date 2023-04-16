#include "room_factory.hpp"
#include "exceptions.hpp"

// delete this
#include <iostream>

using namespace std;

namespace
{
    string add_divide(int width)
    {
        string divide;
        for (int i = 0; i < width; i++)
        {
            divide = "+-";
        }
        divide += "+\n";
        return divide;
    }

    string room_type(shared_ptr<final_proj::Base_Room> room)
    {
        if (room == nullptr)
        {
            return " ";
        }
        else if (room->get_type() == "Riddle")
        {
            return "R";
        }
        else if (room->get_type() == "Object")
        {
            return "T";
        }
        else if (room->get_type() == "Combat")
        {
            return "M";
        }
        else
        {
            return "?";
        }
    }

}

namespace final_proj
{

    shared_ptr<Base_Room> Room_Factory::construct_room(int x)
    {
        int room_type = rand() % 3;

        if (room_type == 0)
        {
            return make_shared<Object_Room>(x, 0);
        }
        else if (room_type == 1)
        {
            return make_shared<Combat_Room>(x, 0);
        }
        else if (room_type == 2)
        {
            if (m_riddle_iter == cend(m_riddle))
            {
                int new_type = rand() % 2;
                if (new_type == 0)
                {
                    return make_shared<Object_Room>(x, 0);
                }
                else if (new_type == 1)
                {
                    return make_shared<Combat_Room>(x, 0);
                }
                else
                {
                    throw UnsupportedBehavoir("tried to generate a room that doesn't exsist - construct room no riddle");
                }
            }
            else
            {
                shared_ptr<Base_Room> to_return = make_shared<Riddle_Room>(x, 0, m_riddle_iter->first, m_riddle_iter->second);
                m_riddle_iter++;
                return to_return;
            }
        }
        else
        {
            throw UnsupportedBehavoir("tried to generate a room that doesn't exsist - construct room");
        }
    }

    shared_ptr<Base_Room> Room_Factory::get_room_at(int x)
    {
        if (x < 0 || x >= m_width)
        {
            throw InvalidUserInputException("player is trying to go off the board");
        }
        else
        {
            return m_map.at(x);
        }
    }

}