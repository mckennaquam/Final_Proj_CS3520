#include <iostream>

#include "unit_test_framework.h"
#include "exceptions.hpp"
#include "player.hpp"
#include "item.hpp"
#include "room_factory.hpp"
#include "room.hpp"

using namespace std;

using namespace final_proj;

// tests for the room_factory

TEST_MAIN()

// tests that the room_factory constructor properly creates a game with the preassigned three rooms
TEST(test_room_factory_constructor)
{
    Room_Factory rf = Room_Factory(10, 10);

    shared_ptr<Base_Room> room1 = make_shared<Object_Room>(0, 0);
    shared_ptr<Base_Room> room2 = make_shared<Riddle_Room>(1, 0, "riddle", "riddle_answer");
    shared_ptr<Base_Room> room3 = make_shared<Combat_Room>(2, 0);

    ASSERT_EQUAL(room1->get_type(), rf.get_room_at(0, 0)->get_type());
    ASSERT_EQUAL(room2->get_type(), rf.get_room_at(1, 0)->get_type());
    ASSERT_EQUAL(room3->get_type(), rf.get_room_at(2, 0)->get_type());
}

// tests that show_map will display the proper map
TEST(test_room_factory_show_map)
{
    Room_Factory rf = Room_Factory(2, 2);

    string correctMap = 
    "+-+-+\n" 
    "|T| |\n"
    "+-+-+\n"
    "| | |\n"
    "+-+-+";

    ASSERT_EQUAL(correctMap, rf.show_map(2, 2));
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that show_legend will return a string displaying the legend
TEST(test_room_factory_show_legend)
{
    Room_Factory rf = Room_Factory(2, 2);

    string correctLegend = "Legend:\nX - You are here\nT - Treasure room\nR - Riddle room\nC - "
    "Combat room\n";

    ASSERT_EQUAL(correctLegend, rf.show_legend());
}


