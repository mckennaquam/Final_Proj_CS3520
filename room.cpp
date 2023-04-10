#include "room.hpp"
#include "player.hpp"

using namespace std;

// Empty namespace for helper methods
namespace
{

}

namespace final_proj
{

    int Base_Room::get_x() const
    {
        return m_x;
    }

    int Base_Room::get_y() const
    {
        return m_y;
    }

    void Object_Room::answer_riddle(string answer)
    {
    }

    void Object_Room::hit_monster(int damage)
    {
    }

    bool Object_Room::monster_alive()
    {
    }

    Item Object_Room::remove_obj()
    {
    }

    string Object_Room::describe_room()
    {
    }

    void Riddle_Room::answer_riddle(string answer)
    {
    }

    void Riddle_Room::hit_monster(int damage)
    {
    }

    bool Riddle_Room::monster_alive()
    {
    }

    Item Riddle_Room::remove_obj()
    {
    }

    string Riddle_Room::describe_room()
    {
    }

    void Combat_Room::answer_riddle(string answer)
    {
    }

    void Combat_Room::hit_monster(int damage)
    {
    }

    bool Combat_Room::monster_alive()
    {
    }

    Item Combat_Room::remove_obj()
    {
    }

    string Combat_Room::describe_room()
    {
    }

}