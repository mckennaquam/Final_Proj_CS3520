#include "room.hpp"
#include "player.hpp"
#include "exceptions.hpp"
#include "monster.hpp"
#include <iostream>

using namespace std;

// A class representing a room

namespace final_proj
{
    // returns an int representing a room's x coordinate
    int Base_Room::get_x() const
    {
        return m_x;
    }

    // returns an int representing a room's y coordinate
    int Base_Room::get_y() const
    {
        return m_y;
    }

    // returns a string representing a room's type
    string Base_Room::get_type() const
    {
        return m_type;
    }

    // returns a bool represeing if a room has been visted or not
    bool Base_Room::room_visited() const
    {
        return m_visited;
    }

    // marks the visted boolean as true
    void Base_Room::visit_room()
    {
        m_visited = true;
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    bool Base_Room::answer_riddle(string &answer)
    {
        answer = nullptr;
        throw InvalidUserInputException("There is no riddle to answer in here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    void Base_Room::hit_monster(int)
    {
        throw InvalidUserInputException("There is no monster to fight here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    bool Base_Room::monster_alive() const
    {
        throw InvalidUserInputException("There is no monster here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    shared_ptr<Item> Base_Room::remove_obj()
    {
        throw InvalidUserInputException("There is no item to pick up here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    int Base_Room::monster_attack_damage() const
    {
        throw InvalidUserInputException("There is no monster here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    string Base_Room::monster_attack_type() const
    {
        throw InvalidUserInputException("There is no monster here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    string Base_Room::monster_name() const
    {
        throw InvalidUserInputException("There is no monster here!\n");
    }

    // Throws an InvalidUserInputException if the command is not supported for that room type
    int Base_Room::monster_points() const
    {
        throw InvalidUserInputException("There is no monster here!\n");
    }

    // returns true if player enters the correct answer to the riddle
    // only works in riddle room
    bool Riddle_Room::answer_riddle(string &answer)
    {
        if (answer == m_answer)
        {
            m_has_been_answered = true;
        } else
        {
            m_has_been_answered = false;
        }
        return m_has_been_answered;
    }

    // returns and marks the taken flag as true of the object contained in the room
    // works in object room and combat room is moster is dead
    // this method doesn't handel if the object is added to the player's inventory, just removed 
    // from the room
    shared_ptr<Item> Object_Room::remove_obj()
    {
        if (m_item == nullptr)
        {
            throw InvalidUserInputException("You have already picked up the item in this room.\n");
        }
        else
        {
            shared_ptr<Item> to_return = m_item;
            m_item = nullptr;
            return to_return;
        }
    }

    // returns a shared_ptr<Item>, the item that we are removing from the room to make it accesible
    // for the player to pick up. Throws an InvalidUserInputException is the player attempts to pick
    // up the object if the monster is not dead, as well as if the player attempts to pick up an
    // item that does not exist
    shared_ptr<Item> Combat_Room::remove_obj()
    {
        if (m_enemy->is_alive())
        {
            throw InvalidUserInputException("You cant pick up the " + m_item->m_name +
                                            " there is a " + m_enemy->get_name() + " here!\n");
        }
        else
        {
            if (m_item == nullptr)
            {
                throw InvalidUserInputException
                ("You have already picked up the item in this room.\n");
            }
            else
            {
                shared_ptr<Item> to_return = m_item;
                m_item = nullptr;
                return to_return;
            }
        }
    }

    // describes rooms. Returns a string of a one of three room descriptions for if the room has
    // not been "completed", in the Object_Room's case being that the item has no been removed. If
    // the item has been removed, generate an alternative description.
    string Object_Room::describe_room() const
    {
        if (m_seed == 0 && m_item != nullptr)
        {
            return 
            "You enter a room filled wall to wall with gilded treasure, "
            "glistening under the light of \na singular beam peaking through a small opening in "
            "the ceiling. You spot a " + m_item->m_name + ".";
        }
        else if (m_seed == 0 && m_item == nullptr)
        {
            return "You enter a room filled a little less with treasure, but still very shiny.";
        }
        else if (m_seed == 1 && m_item != nullptr)
        {
            return "You walk into the room to see a skeleton on the floor clutching a " + 
            m_item->m_name + ". \nYou would feel bad to take it from them... "
            "however they aren’t using it.";
        }
        else if (m_seed == 1 && m_item == nullptr)
        {
            return "The skeleton is still there... they look a little sadder.";
        }
        else if (m_seed == 2 && m_item != nullptr)
        {
            return "You step into a damp, cold, moss-coated cavern. An aged chest sits in the "
            "leftmost corner, \nwhich you snap open due to its decaying lock. Inside is a " + 
            m_item->m_name + "...";
        }
        else if (m_seed == 2 && m_item == nullptr)
        {
            return "The room is still cold and damp, but now has nothing useful.";
        }
        else
        {
            throw UnsupportedBehavoir
            ("tried to make a randomized description - describe object room");
        }
    }

    // describes rooms. Returns a string of a one of three room descriptions for if the room has
    // not been "completed", in the Riddle_Rooms's case being that the riddle has not been answered.
    // If the riddle has been answered, generate an alternative description.
    string Riddle_Room::describe_room() const
    {

        if (m_seed == 0 && !m_has_been_answered)
        {
            return "You step into the room to see a phase scrawled out on a wall... \n\n\"" + 
            m_riddle + "\"\n";
        }
        else if (m_seed == 0 && m_has_been_answered)
        {
            return "The phrase is still there, but you already solved it! Continue on.";
        }
        else if (m_seed == 1 && !m_has_been_answered)
        {
            return "A leprechaun pops out of the corner of this room! Ah! He says a "
            "riddle... \n\n\"" + m_riddle + "\"\n";
        }
        else if (m_seed == 1 && m_has_been_answered)
        {
            return "The leprechaun is now sobbing, purposeless. Better leave him be.";
        }
        else if (m_seed == 2 && !m_has_been_answered)
        {
            return "You step into this room and see a sleeping sphinx, so try your best to be "
            "silent but she \nwakes up. She doesn’t seem to be upset but she asks you this "
            "riddle: \n\n\"" + m_riddle + "\"\n";
        }
        else if (m_seed == 2 && m_has_been_answered)
        {
            return "The sphinx is now fast asleep. You have nothing to do here, so you should "
            "leave as to not wake her.";
        }
        else
        {
            throw UnsupportedBehavoir
            ("tried to make a randomized description - describe riddle room");
        }
    }

    // describes rooms. Returns a string of a one of three room descriptions for if the room has
    // not been "completed", in the Combat_Room's case being that the monster has not been defeated.
    // If the monster has been defeated, generate an alternative description.
    string Combat_Room::describe_room() const
    {
        if (m_enemy->get_name() == "Skeleton" && m_enemy->is_alive())
        {
            return "Oh no a Skeleton who’s moving! He rattles his bones at you... he’s looking for "
            "a fight and he’s got a " + m_item->m_name + "!";
        }
        else if (m_enemy->get_name() == "Skeleton" && !m_enemy->is_alive())
        {
            return "The skeleton in this room is no longer moving. Good, that’s how it should be.";
        }
        else if (m_enemy->get_name() == "Slime" && m_enemy->is_alive())
        {
            return "You enter the room to see a Slime! They hop up and down getting the floor "
            "covered in their \nooze, gross. However, you see inside their gelatinous body they "
            "are carrying a " + m_item->m_name + ".\nIf you slay the slime you will get to keep "
            "the (wet) " + m_item->m_name + ".";
        }
        else if (m_enemy->get_name() == "Slime" && !m_enemy->is_alive())
        {
            return "You enter the room where the Slime once stood.. the floor is... sticky...";
        }
        else if (m_enemy->get_name() == "Lich" && m_enemy->is_alive())
        {
            return "Before you towers a 7ft tall ghostly figure. His arms stretch wide, daring you "
            "to come an \ninch closer. You’ve read about Lichs before, undead kings and queens "
            "who sold their soul \nto live forever and now you’ve come face to face with one. Do "
            "you dare fight it..?";
        }
        else if (m_enemy->get_name() == "Lich" && !m_enemy->is_alive())
        {
            return "All that is left of the Lich that once haunted this room is a red cape left "
            "on the floor. \nIt looks so humble compared to the great evil that used to wear it.";
        }
        else
        {
            throw UnsupportedBehavoir
            ("tried to make a randomized description - describe combat room");
        }
    }

    // implementing combat only rooms

    // deals damage to the monster contained in the room
    // only works in combat room
    void Combat_Room::hit_monster(int damage)
    {
        m_enemy->take_damage(damage);
        cout << "The " + m_enemy->get_name() + "'s health is now: " + 
        to_string(m_enemy->get_health()) << endl;
    }

    // returns an integer describing the amount of damage an enemy will deal
    int Combat_Room::monster_attack_damage() const
    {
        return m_enemy->deal_damage();
    }
    
    // returns a string describing an enemy's attack type
    string Combat_Room::monster_attack_type() const
    {
        return m_enemy->attack_type();
    }

    // returns an integer describing an enemy's point value
    int Combat_Room::monster_points() const
    {
        return m_enemy->point_val();
    }

    // returns a string describing an enemy's name
    string Combat_Room::monster_name() const
    {
        return m_enemy->get_name();
    }

    // returns a bool describing if an enemy is alive
    bool Combat_Room::monster_alive() const
    {
        return m_enemy->is_alive();
    }

}