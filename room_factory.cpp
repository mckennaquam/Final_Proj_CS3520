#include "room_factory.hpp"
#include "exceptions.hpp"

using namespace std;

// A class representing a room_factory

// Empty namespace for helper methods
namespace
{
    // returns a string of "+-" as long as a provided width
    string add_divide(int width)
    {
        string divide;
        for (int a = 0; a < width; a++)
        {
            divide += "+-";
        }
        divide += "+\n";
        return divide;
    }

    // returns a string depending on the room type of a provided room
    string room_type(shared_ptr<final_proj::Base_Room> room)
    {
        if (!room->room_visited())
        {
            return " ";
        }
        else if (room->get_type() == "Riddle")
        {
            return "R";
        }
        else if (room->get_type() == "Treasure")
        {
            return "T";
        }
        else if (room->get_type() == "Combat")
        {
            return "C";
        }
        else
        {
            // unfednied behavior
            return "?";
        }
    }
}

namespace final_proj
{

    // Returns a shared_ptr<Base_Room> of one of three constructed Rooms, created at a given
    // x and y position
    shared_ptr<Base_Room> Room_Factory::construct_room(int x, int y)
    {
        int room_type = rand() % 100;

        if (room_type <= 40)
        {
            return make_shared<Object_Room>(x, y);
        }
        else if (room_type > 40 && room_type <= 80)
        {
            return make_shared<Combat_Room>(x, y);
        }
        else if (room_type > 80)
        {
            if (m_riddle_iter == cend(m_riddle))
            {
                int new_type = rand() % 2;
                if (new_type == 0)
                {
                    return make_shared<Object_Room>(x, y);
                }
                else if (new_type == 1)
                {
                    return make_shared<Combat_Room>(x, y);
                }
                else
                {
                    throw UnsupportedBehavoir
                    ("tried to generate a room that doesn't exsist - construct room no riddle");
                }
            }
            else
            {
                shared_ptr<Base_Room> to_return = make_shared<Riddle_Room>(x, y, 
                m_riddle_iter->first, m_riddle_iter->second);
                m_riddle_iter++;
                return to_return;
            }
        }
        else
        {
            throw UnsupportedBehavoir
            ("tried to generate a room that doesn't exsist - construct room");
        }
    }

    // Returns a shared_ptr<Base_Room> at a given x and y position
    // Throws an InvalidUserException if the given x and y position are out of bounds
    shared_ptr<Base_Room> Room_Factory::get_room_at(int x, int y) const
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        {
            // player is trying to go off the board
            throw InvalidUserInputException
            ("You can't go that way! Perhaps you should review your map.\n");
        }
        else
        {
            return m_map.at((m_width * y) + x);
        }
    }

    // returns a string detailing a map of the dungeon. Dependent on a provided x and y coordinate,
    // generates an "X" at the player's location on the map
    string Room_Factory::show_map(int x, int y) const
    {
        string map;
        map += add_divide(m_width);

        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                if (i == y && j == x)
                {
                    map += "|X";
                }
                else
                {
                    map += "|" + room_type(get_room_at(j, i));
                }
            }
            map += "|\n";
            map += add_divide(m_width);
        }

        return map;
    }

    // returns a string decribing the legend for the map
    string Room_Factory::show_legend() const
    {
        return "Legend:\nX - You are here\nT - Treasure room\nR - Riddle room\nC - Combat room\n";
    }

}