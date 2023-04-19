#include "player.hpp"
#include "room.hpp"
#include "monster.hpp"
#include "room_factory.hpp"
#include "exceptions.hpp"

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <map>
#include <functional>
#include <string>

using namespace std;

using namespace final_proj;

// the main function of our project. Acts as the controller and controlls all the interactions 
// between our model

namespace
{
    void remove_extra(istringstream &iss)
    {
        string removing_extra;
        getline(iss, removing_extra);
    }

}

namespace
{
    // all possible commands get defined here
    void go(istringstream &iss, Player &p, Room_Factory &rf);
    void fight(istringstream &iss, Player &p, Room_Factory &);
    void answer_riddle(istringstream &iss, Player &p, Room_Factory &);
    void use(istringstream &iss, Player &p, Room_Factory &);
    void describe_room(istringstream &, const Player &p, Room_Factory &);
    void pick_up(istringstream &, Player &p, Room_Factory &);
    void check_inventory(istringstream &, const Player &p, Room_Factory &);
    void check_stats(istringstream &, const Player &p, Room_Factory &);
    void show_map(istringstream &, const Player &p, const Room_Factory &rf);
    void show_commands(istringstream &, Player &, Room_Factory &);
}

// map of functions here
const map<
    string, std::function<void(istringstream &, final_proj::Player &, final_proj::Room_Factory &)>>
    command_funcs = {
        // takes the player into the next room in the direction speficied
        {"go", go},
        // fights the moster if there is an alive monster in the room
        // handles fighting and retreating within the fight command
        {"fight", fight},
        // shows the player a list of the commands avaliable
        {"show_commands", show_commands},
        // uses the spefified item
        {"use", use},
        // a short descrption of the room you are in
        {"describe_room", describe_room},
        // picks up the item that is in the room is there is one
        {"pick_up", pick_up},
        // list the player's current inventory (and points)
        {"check_inventory", check_inventory},
        // list the player's current stats
        {"check_stats", check_stats},
        // shows a simple map of the gameboard
        {"show_map", show_map},
        // lets the player attempt to answer a riddle
        {"answer_riddle", answer_riddle}};

int main()
{
    srand(time(0));

    string input;

    Room_Factory rf = Room_Factory(5, 20);

    Player p = Player();

    cout << "Welcome weary traveler! Your journey through this trecherous dungeon begins now.\n"
            "To view the scope of your abilities, type \"show_commands\"\n"
         << endl;

    // tutorial
    while (std::getline(cin, input))
    {
        // Skip over blank lines (provided for you). You do not need to handle
        // leading whitespace, and we will not test your code on that.
        if (input.empty())
        {
            continue;
        }

        istringstream iss = istringstream(input);
        string command;
        iss >> command;

        if (command == "show_commands")
        {
            auto func = command_funcs.find(command);
            func->second(iss, p, rf);

            remove_extra(iss);

            cout << "Amazing! Now that you know the ropes, your journey can begin.\n"
                 << endl;
            shared_ptr<Base_Room> start_room = rf.get_room_at(0, 0);
            p.update_location(start_room);
            string prompt = "\nWhat do you do?\n";
            cout << p.get_current_room()->describe_room() + prompt << endl;
            break;
        }
        else
        {
            cout << "It would be wise to review your commands! \n"
                 << endl;
        }
    }
    //  Read lines from cin as long as the state of the stream is good.
    //  the main game portion.
    while (std::getline(cin, input) && p.player_alive())
    {
        // Skip over blank lines (provided for you). You do not need to handle
        // leading whitespace, and we will not test your code on that.
        if (input.empty())
        {
            continue;
        }

        // Create an istringstream from the line that we read in.
        // Read the first word as the command to run.
        // If the command is "quit", exit the program with zero status.
        istringstream iss = istringstream(input);
        string command;
        iss >> command;

        if (command == "quit")
        {
            break;
        }

        // Look up the command function in the map of commands.
        // If that command doesn't exist, print "Unrecognized command"
        // to cout followed by a newline.

        // If it does exist, call the command function, passing in
        // the library, scene builder, and scene objects you created.
        // If InvalidUserInputException is thrown, print out the message
        // returned by the "what()" member function on the exception.

        if (command_funcs.find(command) == cend(command_funcs))
        {
            cout << "Unrecognized command, type \"show_commands\" to view the list of acceptable "
            "commands!\n"
                 << endl;
        }
        else
        {
            try
            {
                auto func = command_funcs.find(command);
                func->second(iss, p, rf);
            }
            catch (InvalidUserInputException &e)
            {
                cout << e.what() << endl;
            }
        }
        remove_extra(iss);
    }

    if (p.player_alive())
    {
        cout << "Thanks for playing! Your final score was: " + to_string(p.get_points()) + "!" 
        << endl;
    }
    else
    {
        cout << "The" + p.get_current_room()->monster_name() + " stikes you down! You are forced "
        "to leave the dungeon in disgrace." << endl;
        cout << "Your final score was " + to_string(p.get_points()) + "! Thanks for playing!" 
        << endl;
    }

    return 0;
}

namespace
{
    // go command implementation
    void go(istringstream &iss, Player &p, Room_Factory &rf)
    {

        string direction;
        iss >> direction;

        int player_x = p.get_current_room()->get_x();
        int player_y = p.get_current_room()->get_y();
        string old_room_type = p.get_current_room()->get_type();

        shared_ptr<Base_Room> new_room;

        if (direction == "north")
        {
            new_room = rf.get_room_at(player_x, player_y - 1);
        }
        else if (direction == "east")
        {
            new_room = rf.get_room_at(player_x + 1, player_y);
        }
        else if (direction == "south")
        {
            new_room = rf.get_room_at(player_x, player_y + 1);
        }
        else if (direction == "west")
        {
            new_room = rf.get_room_at(player_x - 1, player_y);
        }
        else
        {
            throw InvalidUserInputException("You must use cardinal direction (north, east, south, "
            "west) for movement.\n");
        }

        if (old_room_type == "Combat")
        {
            if (p.is_item_in_use())
            {
                p.remove_buff();
                vector<int> stats = p.check_stats();
                cout << "You feel the effects of the potion wearing off... your strength is now " + 
                to_string(stats.at(1)) + " and your defense is now " + to_string(stats.at(2)) + 
                ".\n" << endl;
            }
        }

        p.update_location(new_room);
        p.get_current_room()->visit_room();
        string prompt = "\nWhat do you do?\n";
        cout << "You enter the " + direction + " room.\n" + p.get_current_room()->describe_room() + 
        prompt << endl;
    }

    // fight commands implementation
    void fight(istringstream &iss, Player &p, Room_Factory &)
    {
        shared_ptr<Base_Room> current_room = p.get_current_room();
        // checking to make sure this is a combat room
        // and if it is a monster room then make sure the player
        // hasnt already beat the monster
        if (!current_room->monster_alive())
        {
            throw InvalidUserInputException("You can't fight a monster you already killed!");
        }

        string preliminary_message = "You have started combat with the " + 
        current_room->monster_name() + "! ";
        string blank = "";

        string tutorial = blank + "For each turn you can do 1 of 3 things:\n" +
                          "1) Retreat out of combat with \"retreat\" \n2) Use an item with \"use "
                          "[item name]\" \n" +
                          "3) Engage in combat with \"bludgeon\" or \"slash\" or \"pierce\" \n" +
                          "\nWhen you engage in combat, you use one of the three attack types and "
                          "the monster will chose an attack type as well.\n\n"
                          "\"bludgeon\" beats \"slash\", \"slash\" beats \"pierce\", and "
                          "\"pierce\" beats \"bludgeon\"\n\n"
                          "Depending on if you or the monster successfully hit the other, damage "
                          "will then be assigned.";

        cout << tutorial << endl;

        string combat_input;

        cout << "What do you do?\n"
             << endl;

        while (std::getline(cin, combat_input) && p.player_alive() && current_room->monster_alive())
        {

            istringstream iss_combat = istringstream(combat_input);
            string combat_command;
            iss_combat >> combat_command;

            if (combat_command == "help")
            {
                cout << tutorial << endl;
            }
            else if (combat_command == "retreat")
            {
                cout << "You back away from the fight!\n"
                     << endl;
                break;
            }
            else if (combat_command == "use")
            {
                try
                {
                    string name;
                    string rank;
                    int stat;
                    string type;
                    iss >> name;
                    iss >> rank;
                    iss >> stat;
                    iss >> type;
                    name += (" " + rank + " " + to_string(stat) + " " + type);

                    p.use_item(name, type, stat);
                }
                catch (InvalidUserInputException &e)
                {
                    throw InvalidUserInputException("You can't use this item!"); 
                }
            }
            // defines how combat will function
            else if (combat_command == "bludgeon" || combat_command == "pierce" || 
            combat_command == "slash")
            {
                int monster_damage = current_room->monster_attack_damage();
                string monster_type = current_room->monster_attack_type();

                if (combat_command == "bludgeon")
                {
                    if (monster_type == "slash")
                    {
                        cout << "You hit the " + current_room->monster_name() + " and deal " + 
                        to_string(p.get_strength()) + " points of damage!" << endl;
                        current_room->hit_monster(p.get_strength());
                    }
                    else if (monster_type == "pierce")
                    {
                        cout << "The " + current_room->monster_name() + " dealt " + 
                        to_string(monster_damage) + " points of damage! Ouch!" << endl;
                        p.take_damage(monster_damage);
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " both miss!" 
                        << endl;
                    }
                }
                else if (combat_command == "pierce")
                {
                    if (monster_type == "bludgeon")
                    {
                        cout << "You hit the " + current_room->monster_name() + " and deal " + 
                        to_string(p.get_strength()) + " points of damage!" << endl;
                        current_room->hit_monster(p.get_strength());
                    }
                    else if (monster_type == "slash")
                    {
                        cout << "The " + current_room->monster_name() + " dealt " + 
                        to_string(monster_damage) + " points of damage! Ouch!" << endl;
                        p.take_damage(monster_damage);
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " both miss!" 
                        << endl;
                    }
                }
                else
                {
                    if (monster_type == "pierce")
                    {
                        cout << "You hit the " + current_room->monster_name() + " and deal " + 
                        to_string(p.get_strength()) + " points of damage!" << endl;
                        current_room->hit_monster(p.get_strength());
                    }
                    else if (monster_type == "bludgeon")
                    {
                        cout << "The " + current_room->monster_name() + " dealt " + 
                        to_string(monster_damage) + " points of damage! Ouch!" << endl;
                        p.take_damage(monster_damage);
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " both miss!" 
                        << endl;
                    }
                }
            }
            else
            {
                cout << "Action not recognized! Try again or ask for \"help\"" << endl;
            }

            remove_extra(iss);

            if (!current_room->monster_alive())
            {
                p.update_points(current_room->monster_points());
                cout << "\nYou slay the " + current_room->monster_name() + "! and earn " + 
                to_string(current_room->monster_points()) + " points. Heck yeah." << endl;
                cout << "The item the " + current_room->monster_name() + " was holding drops to "
                "the floor.\n"
                     << endl;
                break;
            }
            else
            {
                cout << "What's your next move?\n"
                     << endl;
            }
        }
    }

    // use command implementation
    void use(istringstream &iss, Player &p, Room_Factory &)
    {
        string name;
        string rank;
        int stat;
        string type;
        iss >> name;
        iss >> rank;
        iss >> stat;
        iss >> type;
        name += (" " + rank + " " + to_string(stat) + " " + type);

        p.use_item(name, type, stat);
    }

    // describe_room command implementation
    void describe_room(istringstream &, const Player &p, Room_Factory &)
    {
        cout << p.get_current_room()->describe_room() + "\n"
             << endl;
    }

    // pick_up command implementation
    void pick_up(istringstream &, Player &p, Room_Factory &)
    {
        shared_ptr<Item> new_item = p.get_current_room()->remove_obj();
        p.pick_up_object(new_item);
    }

    // check_inventory command implementation
    void check_inventory(istringstream &, const Player &p, Room_Factory &)
    {
        cout << "Inventory contains: " << endl;
        vector<string> inventory = p.check_inventory();
        if (inventory.empty())
        {
            cout << "Nothing! Collect more items.\n"
                 << endl;
        }
        else
        {
            copy(cbegin(inventory), cend(inventory), std::ostream_iterator<string>(cout, "\n"));
            cout << "\n"
                 << endl;
        }
    }

    // check_stats command implementation
    void check_stats(istringstream &, const Player &p, Room_Factory &)
    {
        vector<int> stats = p.check_stats();
        cout << "Health: " + to_string(stats.at(0)) << endl;
        cout << "Strength: " + to_string(stats.at(1)) << endl;
        cout << "Defense: " + to_string(stats.at(2)) + "\n"
             << endl;
    }

    // show_map command implementation
    void show_map(istringstream &, const Player &p, const Room_Factory &rf)
    {

        // get the players current position for the map
        int x = p.get_current_room()->get_x();
        int y = p.get_current_room()->get_y();

        // display map and key
        cout << rf.show_map(x, y) << endl;
        cout << rf.show_legend() << endl;
    }

    // show_commands command implementation
    void show_commands(istringstream &, Player &, Room_Factory &)
    {
        // pushes command names into a printable list
        cout << "\n";
        vector<string> command_name;
        transform(cbegin(command_funcs), cend(command_funcs), back_inserter(command_name), 
        [](auto &iter)
                  { return iter.first; });

        // erases commands that will appear differently in the show_commands list
        command_name.erase(find(begin(command_name), end(command_name), "answer_riddle"));
        command_name.erase(find(begin(command_name), end(command_name), "use"));
        command_name.erase(find(begin(command_name), end(command_name), "go"));
        copy(cbegin(command_name), cend(command_name), std::ostream_iterator<string>(cout, "\n"));
        cout << "answer_riddle [answer]" << endl;
        cout << "use [name]" << endl;
        cout << "go [north][south][east][west]" << endl;
        cout << "quit\n"
             << endl;
    }

    // answer_riddle command implementation
    void answer_riddle(istringstream &iss, Player &p, Room_Factory &)
    {
        string answer;
        iss >> answer;

        if (p.get_current_room()->answer_riddle(answer))
        {
            p.update_points(25);
            cout << "You got it! Your score now is " + to_string(p.get_points()) + "\n"
                 << endl;
        }
        else
        {
            cout << "Hmmm that's not it...\n"
                 << endl;
        }
    }
}
