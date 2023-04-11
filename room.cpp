#include "room.hpp"
#include "player.hpp"
#include "exceptions.hpp"

using namespace std;

// Empty namespace for helper methods
namespace
{

}

namespace final_proj
{
    // basic functions for getting x and y coordinates and room type
    int Base_Room::get_x() const
    {
        return m_x;
    }

    int Base_Room::get_y() const
    {
        return m_y;
    }

    string Base_Room::get_type() const
    {
        return m_type;
    }

    // returns true if player enters the correct answer to the riddle
    // only works in riddle room
    bool Object_Room::answer_riddle(string answer)
    {
        throw InvalidUserInputException("There is no riddle to answer here!");
    }

    bool Riddle_Room::answer_riddle(string answer)
    {
        return answer == m_answer;
    }

    bool Combat_Room::answer_riddle(string answer)
    {
        throw InvalidUserInputException("There is no riddle to answer here!");
    }

    // deals damage to the monster contained in the room
    // only works in combat room
    // (maybe need to rework this, depends on combat impl)
    void Object_Room::hit_monster(int damage)
    {
        throw InvalidUserInputException("There is no monster to fight here!");
    }

    void Riddle_Room::hit_monster(int damage)
    {
        throw InvalidUserInputException("There is no monster to fight here!");
    }

    void Combat_Room::hit_monster(int damage)
    {
        m_enemy.take_damage(damage);
    }

    // returns and marks the taken flag as true of the object contained in the room
    // works in object room and combat room is moster is dead
    // this method doesn't handel if the object is added to the player's inventory, just removed from the room
    Item Object_Room::remove_obj()
    {

        if (m_item.m_taken)
        {
            throw InvalidUserInputException("You have already picked up the object in this room");
        }
        else
        {
            m_item.m_taken = true;
            return m_item;
        }
    }

    Item Riddle_Room::remove_obj()
    {
        throw InvalidUserInputException("There is no object to pick up in this room");
    }

    Item Combat_Room::remove_obj()
    {
        if (m_enemy.is_alive())
        {
            throw InvalidUserInputException("You can't take the " + m_item.m_name +
                                            " in here! The " + m_enemy.get_name() + " is still alive!");
        }
        else
        {
            if (m_item.m_taken)
            {
                throw InvalidUserInputException("You have already picked up the object in this room");
            }
            else
            {
                m_item.m_taken = true;
                return m_item;
            }
        }
    }

}