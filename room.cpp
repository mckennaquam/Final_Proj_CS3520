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
        if (answer == m_answer) {
            m_has_been_answered = true;
        } 
        return m_has_been_answered;
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
            return to_return;
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
            if (m_item == nullptr)
        {
            throw InvalidUserInputException("You have already picked up the item in this room");
        }
        else
        {
            shared_ptr<Item> to_return = m_item;
            m_item = nullptr;
            return to_return;
        }
        }
    }

    // describe rooms
    string Object_Room::describe_room() const
    {
        if (m_seed == 0 && m_item != nullptr) {
            return "You enter a room filled wall to wall with gilded treasure, glistening under the light of a singular beam peaking through a small opening in the ceiling.";
        
        } else if (m_seed == 0 && m_item == nullptr) 
        {
            return "You enter a room filled a little less with treasure, but still very shiny";
        
        } else if (m_seed == 1 && m_item != nullptr)
        {
            return "You walk into the room to see a skeleton on the floor clutching a " + m_item->m_name + ". You would feel bad to take it from them... however they aren’t using it.";

        } else if (m_seed == 1 && m_item == nullptr)
        {
            return "The skeleton is still there... they look a little sadder.";

        } else if (m_seed == 2 && m_item != nullptr)
        {
            return "You step into a damp, cold, moss-coated cavern. An aged chest sits in the leftmost corner, which you seem able to open because of its decaying lock.";

        } else if (m_seed == 2 && m_item == nullptr)
        {
            return "The room is still cold and damp, but now has nothing useful.";

        } else 
        {
            throw UnsupportedBehavoir("tried to make a randomized description - describe object room");
        }
    }

    string Riddle_Room::describe_room() const
    {

        if (m_seed == 0 && !m_has_been_answered) {
            return "You step into the room to see a phase scrawled out on a wall... \"" + m_riddle + "\"";
        
        } else if (m_seed == 0 && m_has_been_answered) 
        {
            return "The phrase is still there, but you already solved it! Continue on.";
        
        } else if (m_seed == 1 && !m_has_been_answered)
        {
            return "A leprechaun pops our of the corner of this room! Ah! He says a riddle... \"" + m_riddle + "\"";

        } else if (m_seed == 1 && m_has_been_answered)
        {
            return "The leprechaun is now sobbing, purposeless. Better leave him be.";

        } else if (m_seed == 2 && !m_has_been_answered)
        {
            return "You step into this room and see a sleeping sphinx, so try your best to be silent but she wakes up. She doesn’t seem to be upset but she asks you this riddle: \"" + m_riddle + "\"";

        } else if (m_seed == 2 && m_has_been_answered)
        {
            return "The sphinx is now fast asleep. You have nothing to do here, so you should leave as to not wake her.";

        } else 
        {
            throw UnsupportedBehavoir("tried to make a randomized description - describe riddle room");
        }
    }

    string Combat_Room::describe_room() const
    {
        if (m_enemy->get_name() == "Skeleton" && m_enemy->is_alive())
        {
            return "Oh no a skeleton who’s moving! He rattles his bones at you... he’s looking for a fight and he’s got a " + m_item->m_name + "!";

        } else if (m_enemy->get_name() == "Skeleton" && !m_enemy->is_alive())
        {
            return "The skeleton in this room is no longer moving. Good, that’s how it should be.";

        } else if (m_enemy->get_name() == "Slime" && m_enemy->is_alive())
        {
            return "You enter the room to see a slime! They hop up and down getting the floor covered in their ooze, gross. However, you see inside their gelatinous body they are carrying a " + m_item->m_name + ". If you slay the slime you will get to keep the (wet) " + m_item->m_name + ".";

        } else if (m_enemy->get_name() == "Slime" && !m_enemy->is_alive())
        {
            return "You enter the room where the slime once stood.. the floor is... sticky...";

        } else if (m_enemy->get_name() == "Lich" && m_enemy->is_alive())
        {
            return "Before you towers a 7ft tall ghostly figure. His arms stretch wide, daring you to come an inch closer. You’ve read about lichs before, undead kings and queens who sold their soul to live forever and now you’ve come face to face with one. Do you dare fight it?";

        } else if (m_enemy->get_name() == "Lich" && !m_enemy->is_alive())
        {
            return "All that is left of the Lich that once haunted this room is a red cape left on the floor. It looks so humble compared to the great evil that used to wear it.";

        } else
        {
            throw UnsupportedBehavoir("tried to make a randomized description - describe combat room");

        }
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