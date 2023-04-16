#include "room.hpp"
#include "player.hpp"
#include "exceptions.hpp"
#include "monster.hpp"

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

    // throwing errors if the command is not supported for that room type
    bool Base_Room::answer_riddle(string &answer)
    {
        throw InvalidUserInputException("There is no riddle to answer in here!");
    }

    void Base_Room::hit_monster(int)
    {
        throw InvalidUserInputException("There is no monster to fight here!");
    }

    bool Base_Room::monster_alive() const
    {
        throw InvalidUserInputException("There is no monster here!");
    }

    shared_ptr<Item> Base_Room::remove_obj()
    {
        throw InvalidUserInputException("There is no item to pick up here!");
    }

    int Base_Room::montser_attack_damage() const
    {
        throw InvalidUserInputException("There is no monster here!");
    }

    string Base_Room::monster_attack_type() const
    {
        throw InvalidUserInputException("There is no monster here!");
    }

    string Base_Room::monster_name() const
    {
        throw InvalidUserInputException("There is no monster here!");
    }

    int Base_Room::monster_points() const
    {
        throw InvalidUserInputException("There is no monster here!");
    }

    // returns true if player enters the correct answer to the riddle
    // only works in riddle room
    bool Riddle_Room::answer_riddle(string &answer)
    {
        return answer == m_answer;
    }

    // returns and marks the taken flag as true of the object contained in the room
    // works in object room and combat room is moster is dead
    // this method doesn't handel if the object is added to the player's inventory, just removed from the room
    shared_ptr<Item> Object_Room::remove_obj()
    {
        if (m_item == nullptr)
        {
            throw InvalidUserInputException("You have already picked up the item in this room");
        }
        else
        {
            shared_ptr<Item> to_return = m_item;
            m_item = nullptr;
            return m_item;
        }
    }

    shared_ptr<Item> Combat_Room::remove_obj()
    {
        if (m_enemy->is_alive())
        {
            throw InvalidUserInputException("You cant pick up the " + m_item->m_name + " there is a " + m_enemy->get_name() + " here!");
        }
        else
        {
            Object_Room::remove_obj();
        }
    }

    // describe rooms
    string Object_Room::describe_room() const
    {
        return "to do";
    }

    string Riddle_Room::describe_room() const
    {
        return "to do";
    }

    string Combat_Room::describe_room() const
    {
        return "to do";
    }

    // Implementing combat only rooms

    // deals damage to the monster contained in the room
    // only works in combat room
    // (maybe need to rework this, depends on combat impl)

    void Combat_Room::hit_monster(int damage)
    {
        m_enemy->take_damage(damage);
    }

    int Combat_Room::montser_attack_damage() const
    {
        return m_enemy->deal_damage();
    }
    string Combat_Room::monster_attack_type() const
    {
        return m_enemy->attack_type();
    }

    int Combat_Room::monster_points() const
    {
        return m_enemy->point_val();
    }

    string Combat_Room::monster_name() const
    {
        return m_enemy->get_name();
    }

    bool Combat_Room::monster_alive() const
    {
        return m_enemy->is_alive();
    }

}