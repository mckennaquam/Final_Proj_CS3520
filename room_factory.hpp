#ifndef ROOM_FACTORY_HPP_
#define ROOM_FACTORY_HPP_

#include "room.hpp"
#include <map>
#include <vector>
#include <memory>
#include <iterator>
#include <cstdlib>

using namespace std;

namespace final_proj
{
    class Room_Factory
    {
    public:
        // gets the room at specified cooidinates
        shared_ptr<Base_Room> get_room_at(int x);
        // string show_map(int x, int y) const;
        // string show_legend() const;

        Room_Factory(int height, int width)
        {
            // set the height and width of the game board
            m_height = height;
            m_width = width;

            // initalize the list for riddle rooms
            m_riddle = {
                {"What has hands but cannot clap?", "clock"},
                {"What's bought by the yard and worn by the foot?", "carpet"},
                {"What has a neck but no head?", "bottle"},
                {"What occurs one in a minuet, twice in a moment and never in 1,000 years?", "m"},
                {"What has 13 hearts but no other organs?", "cards"},
                {"What do you bury when it's alive and dig up when it's dead?", "plant"},
                {"How do you keep your pants up when you're preforming? it's amazing!", "belt"},
                {"What is 3/7 chicken, 2/3 cat, and 2/4 goat?", "chicago"},
                {"What goes all around the world but stays in a corner?", "stamp"}};
            m_riddle_iter = cbegin(m_riddle);

            // inialize the map
            m_map = vector<shared_ptr<Base_Room>>();
            for (int i = 0; i < width; i++)
            {
                m_map.push_back(construct_room(i));
            }

            // set the first room
            m_map.at(0) = make_shared<Object_Room>(0, 0);
        }

    private:
        int m_width;
        int m_height;
        vector<shared_ptr<Base_Room>> m_map;
        map<string, string> m_riddle;
        map<string, string>::const_iterator m_riddle_iter;

        shared_ptr<Base_Room> construct_room(int x);
    };
}

#endif