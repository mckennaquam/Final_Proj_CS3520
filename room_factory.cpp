#include "room_factory.hpp"
#include "exceptions.hpp"

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

    shared_ptr<Base_Room> Room_Factory::construct_room(int x, int y)
    {
        /*
        switch (rand() % 3)
        {
        case 0:
            // make a teasure room
            return make_shared<Object_Room>(x, y);
            break;
        case 1:
            // make a riddle room (if possible)
            // this means that we have run out of riddels in our dict and therefore cant make a new riddle room
            if (m_riddle_iter == cend(m_riddle))
            {
                // do one of the 2 other rooms
                if (0 == rand() % 1)
                {
                    return make_shared<Object_Room>(x, y);
                }
                else
                {
                    return make_shared<Object_Room>(x, y);
                }
            }
            else
            {
                shared_ptr<Base_Room> temp_val = make_shared<Riddle_Room>(x, y, m_riddle_iter->first, m_riddle_iter->second);
                // go to the next riddle in out dict
                m_riddle_iter++;
                return temp_val;
            }
            break;
        case 2:
            // make a monster room
            return make_shared<Combat_Room>(x, y);
            break;
        default:
        throw UnsupportedBehavoir("tried to generate a type that dosen't exist- construct room");
        }
        */
       return make_shared<Object_Room>(x, y);
    }

    // this method retuns a shared pointer to a room at a location in the map
    // and if there isn't one there then it creates one and places it at the location
    shared_ptr<Base_Room> Room_Factory::get_room_at(int x, int y)
    {
        // get the room at that location
        // at handels if we are going off the board, throws exception if we are
        //auto moving_to = at(x, y);

        // if the pointer at the location is a nullptr that location
        // has not been visited and thus we need to make a new room
        //if (moving_to == nullptr)
        //{
        //   // construct_room(x, y);
        //}
        //else
        //{
            // room has been visited before return it
        //    return moving_to;
        //}
        return m_map.at(x);
    }

    // Generates the map for the show map function
    string Room_Factory::show_map(int x, int y) const
    {
        /*
        string map = "";
        map += add_divide(m_width);

        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                // if we are at the player's position then display an C
                if ((i == y) && (j == x))
                {
                    map += "|X";
                }
                // otherwise display the correponding room symbol
                else
                {
                    map += "|";
                    map += at(j, i)->get_type();
                }
            }
            map += "|\n";
            map += add_divide(m_width);
        }
        */
       string map = "todo";

        return map;
    }

    // returns the legend for the map
    string Room_Factory::show_legend() const
    {
        return "Legend:\nX - You are here\nO - Treasure room\nR - Riddle room\nM - Monster room";
    }
    /*
        void Room_Factory::player_start(Player &p)
        {
            shared_ptr<Base_Room> start_room = get_room_at(0, 0);
            p.update_location(start_room);
        }
        */

}