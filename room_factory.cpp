#include "room_factory.hpp"
#include "exceptions.hpp"

using namespace std;

namespace
{

}

namespace final_proj
{
    auto Room_Factory::at(int x, int y)
    {
        if (x < 0 || x >= m_width || y < 0 || y <= m_height)
        {
            // player is off the board
            throw InvalidUserInputException("posistion " + to_string(x) + ", " + to_string(y) + " is off the board");
        }
        else
        {
            // return the room at that position
            return m_map.at((y * m_width) + x);
        }
    }

    void Room_Factory::construct_room(int x, int y)
    {
        switch (rand() % 3)
        {
        case 0:
            // make a teasure room
            m_map.at((y * m_width) + x) = make_shared<Object_Room>(x, y);
        case 1:
            // make a riddle room (if possible)
            // this means that we have run out of riddels in our dict and therefore cant make a new riddle room
            if (m_riddle_iter == cend(m_riddle))
            {
                // do one of the 2 other rooms
                if (0 == rand() % 1)
                {
                    m_map.at((y * m_width) + x) = make_shared<Object_Room>(x, y);
                }
                else
                {
                    m_map.at((y * m_width) + x) = make_shared<Object_Room>(x, y);
                }
            }
            else
            {
                m_map.at((y * m_width) + x) = make_shared<Riddle_Room>(x, y, m_riddle_iter->first, m_riddle_iter->second);
                // go to the next riddle in out dict
                m_riddle_iter++;
            }
        case 2:
            // make a monster room
            m_map.at((y * m_width) + x) = make_shared<Combat_Room>(x, y);
        }
    }

    // this method retuns a shared pointer to a room at a location in the map
    // and if there isn't one there then it creates one and places it at the location
    shared_ptr<Base_Room> Room_Factory::get_room_at(int x, int y)
    {
        // get the room at that location
        // at handels if we are going off the board, throws exception if we are
        auto moving_to = at(x, y);

        // if the pointer at the location is a nullptr that location
        // has not been visited and thus we need to make a new room
        if (moving_to == nullptr)
        {
            construct_room(x, y);
        }
        else
        {
            // room has been visited before return it
            return moving_to;
        }
    }

}