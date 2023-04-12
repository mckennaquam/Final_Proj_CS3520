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
    void list_commands(istringstream &, Player &, Room_Factory &);
    void go(istringstream &, Player &, Room_Factory &);
    void fight(istringstream &, Player &, Room_Factory &);
    void use(istringstream &, Player &, Room_Factory &);
    void describe_room(istringstream &, Player &, Room_Factory &);
    void pick_up(istringstream &, Player &, Room_Factory &);
    void check_inventory(istringstream &, Player &, Room_Factory &);
    void check_stats(istringstream &, Player &, Room_Factory &);
    void show_map(istringstream &, Player &, Room_Factory &);
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
        {"list commands", list_commands},
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
    void list_commands(istringstream is &, Player &, Room_Factory &)
    {
    }
    void go(istringstream &, Player &, Room_Factory &) {}
    void fight(istringstream &, Player &, Room_Factory &) {}
    void use(istringstream &, Player &, Room_Factory &) {}
    void describe_room(istringstream &, Player &, Room_Factory &) {}
    void pick_up(istringstream &, Player &, Room_Factory &) {}
    void check_inventory(istringstream &, Player &, Room_Factory &) {}
    void check_stats(istringstream &, Player &, Room_Factory &) {}
    void show_map(istringstream &, Player &, Room_Factory &) {}
}