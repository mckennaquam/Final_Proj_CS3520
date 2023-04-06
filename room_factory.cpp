#include "room_factory.hpp"
#include "exceptions.hpp"

using namespace std;

namespace
{

}

namespace final_proj
{
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
            switch (rand() % 3)
            {
            case 0:
            // make a teasure room
            case 1:
            // make a riddle room (if possible)
            case 2:
                // make a monster room
            }
        }
        else
        {
            // room has been visited before return it
            return moving_to;
        }
    }

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
}