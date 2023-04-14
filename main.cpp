#include "player.hpp"
#include "room.hpp"
#include "monster.hpp"
#include "room_factory.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <functional>

using namespace std;

using namespace final_proj;

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
    void go(istringstream &, Player &, Room_Factory &);
    void fight(istringstream &, Player &, Room_Factory &);
    void use(istringstream &, Player &, Room_Factory &);
    void describe_room(istringstream &, Player &, Room_Factory &);
    void pick_up(istringstream &, Player &, Room_Factory &);
    void check_inventory(istringstream &, Player &, Room_Factory &);
    void check_stats(istringstream &, Player &, Room_Factory &);
    void show_map(istringstream &, Player &, Room_Factory &rf);
    void show_commands(istringstream &, Player &, Room_Factory &);
}

// map of functions here
const map<string, function<void(istringstream &, Player &, Room_Factory &)>>
    command_funcs = {
        // takes the player into the next room in the direction speficied
        {"go", go},
        // fights the moster if there is an alive monster in the room
        // handles fighting and retreating within the fight command
        {"fight", fight},
        // shows the player a list of the commands avaliable
        {"show commands", show_commands},
        // uses the spefified item
        {"use", use},
        // a short descrption of the room you are in
        {"describe room", describe_room},
        // picks up the item that is in the room is there is one
        {"pick up", pick_up},
        // list the player's current inventory (and points)
        {"check inventory", check_inventory},
        // list the player's current stats
        {"check stats", check_stats},
        // shows a simple map of the gameboard
        {"show map", show_map}};

int main()
{
    string input;
    // Read lines from cin as long as the state of the stream is good.
    // This while loop condition is provided for you.
    while (std::getline(cin, input))
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
            return 0;
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
            cout << "Unrecognized command" << endl;
        }
        else
        {
            // try
            //{
            //     auto func = command_funcs.find(command);
            // func->second();
            //}
            // catch (InvalidUserInputException &e)
            //{
            //    cout << e.what() << endl;
            //}
        }
        remove_extra(iss);
    }
}

namespace
{
    // define the commands declreaded above here
    void go(istringstream &iss, Player &, Room_Factory &) {}

    void fight(istringstream &iss, Player &p, Room_Factory &)
    {
        shared_ptr<Base_Room> current_room = p.get_current_room();
        // checking to make sure this is a combat room
        // if it isnt an illegal user input error will be thrown and exit the method
        // otherwise the method will contiue and no damage will be dont to the monster
        current_room->hit_monster(0);

        string tutorial = "You have started combat with " + current_room->monster_name() + "for each turn you can do 1 of 3 things \n" +
                          "1) retreat out of combat with \"retreat\" \n 2) use an item with \"use [item name]\" \n" +
                          "3) engage in combat with \"bludgeon\" or \"slash\" or \"pierce\" \n" +
                          "When you engae in combat you use one of the three attack types and the monster will chose an attack type as well \n"
                          "Bludgeon beats slash, slash beats pierce, and pierce beats bludgeon \n"
                          "depending on if you or the monster successfully hit the other damage will then be assigned";

        cout << tutorial << endl;

        while (p.player_alive() && current_room->monster_alive())
        {
            cout << "What's your next move?" << endl;
            string input;
            iss >> input; // use health poyion

            if (input == "help")
            {

                cout << tutorial << endl;
            }
            else if (input == "retreat")
            {
                cout << "you run away from the fight!" << endl;
                break;
            }
            else if (input == "use")
            {
                string name;
                string rank;
                int num;
                iss >> name;
                iss >> rank;
                iss >> num;

                p.use_item_combat(name, num);
            }
            else if (input == "bludgeon" || input == "pierce" || input == "slash")
            {
                int monster_damage = current_room->montser_attack_damage();
                string monster_type = current_room->monster_attack_type();

                if (input == "bludgeon")
                {
                    if (monster_type == "slash")
                    {
                        current_room->hit_monster(p.get_strength());
                        cout << "You hit the" + current_room->monster_name() + " for " + to_string(p.get_strength()) +
                                    " points of damage!"
                             << endl;
                    }
                    else if (monster_type == "pierce")
                    {
                        p.take_damage(monster_damage);
                        cout << "The " + current_room->monster_name() + "dealt " + to_string(monster_damage) + " points of damage! Ouch!" << endl;
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " miss!" << endl;
                    }
                }
                else if (input == "pierce")
                {
                    if (monster_type == "bludgeon")
                    {
                        current_room->hit_monster(p.get_strength());
                        cout << "You hit the " + current_room->monster_name() + " for " + to_string(p.get_strength()) + " points of damage!" << endl;
                    }
                    else if (monster_type == "slash")
                    {
                        p.take_damage(monster_damage);
                        cout << "The " + current_room->monster_name() + " dealt " + to_string(monster_damage) + " points of damage! Ouch!" << endl;
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " miss!" << endl;
                    }
                }
                else
                {
                    if (monster_type == "pierce")
                    {
                        current_room->hit_monster(p.get_strength());
                        cout << "You hit the " + current_room->monster_name() + " for " + to_string(p.get_strength()) + " points of damage!" << endl;
                    }
                    else if (monster_type == "bludgeon")
                    {
                        p.take_damage(monster_damage);
                        cout << "The " + current_room->monster_name() + " dealt " + to_string(monster_damage) + " points of damage! Ouch!" << endl;
                    }
                    else
                    {
                        cout << "You and the " + current_room->monster_name() + " miss!" << endl;
                    }
                }
            }
            else
            {
                cout << "Action not recognized! Try again or ask for \"help\"" << endl;
            }

            remove_extra(iss);
        }
    }

    void use(istringstream &iss, Player &p, Room_Factory &)
    {
        string name;
        string rank;
        string stat;
        iss >> name;
        iss >> rank;
        iss >> stat;
        name += (rank + stat);
    }

    void describe_room(istringstream &, Player &p, Room_Factory &)
    {
        p.get_current_room()->describe_room();
    }

    void pick_up(istringstream &, Player &, Room_Factory &)
    {
    }

    void check_inventory(istringstream &, Player &, Room_Factory &)
    {
    }

    void check_stats(istringstream &, Player &p, Room_Factory &)
    {
        vector<int> stats = p.check_stats();
        cout << "health: " + to_string(stats.at(0)) << endl;
        cout << "strength: " + to_string(stats.at(1)) << endl;
        cout << "defense: " + to_string(stats.at(2)) << endl;
    }

    void show_map(istringstream &, Player &p, Room_Factory &rf)
    {
        // get the players current position for the map
        int x = p.get_current_room()->get_x();
        int y = p.get_current_room()->get_y();

        // display map and key
        cout << rf.show_map(x, y) << endl;
        cout << rf.show_legend() << endl;
    }

    void show_commands(istringstream &, Player &, Room_Factory &)
    {
        vector<string> command_name;
        transform(cbegin(command_funcs), cend(command_funcs), back_inserter(command_name), [](auto &iter)
                  { return iter.first; });
        copy(cbegin(command_name), cend(command_name), std::ostream_iterator<string>(cout, "\n"));
    }
}