#ifndef ROOM_FACTORY_HPP_
#define ROOM_FACTORY_HPP_

#include "room.hpp"
#include <map>
#include <vector>

using namespace std;

namespace final_proj
{
    class Room_Factory
    {
    public:
        Room_Factory(int height, int width)
        {
            // set the height and width of the game board
            m_height = height;
            m_width = width;

            // inialize the map and set all of it's value to the null ptr
            m_map = vector<shared_ptr<Base_Room>>(height * width, nullptr);

            // initalize the list for riddle rooms
            m_riddle = {
                {"What has hands but cannot clap?", "clock"},
                {"What's bought by the yard and worn by the foot?", "carpet"}};
            m_riddle_iter = cbegin(m_riddle);
        }

        // gets the room at specified cooidinates
        shared_ptr<Base_Room> get_room_at(int x, int y);
        string show_map();

    private:
        int m_width;
        int m_height;
        vector<shared_ptr<Base_Room>> m_map;
        map<string, string> m_riddle;
        map<string, string>::const_iterator m_riddle_iter;

        auto at(int x, int y);
        void construct_room(int x, int y);
    };
}

#endif