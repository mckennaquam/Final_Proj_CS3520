#include <iostream>

#include "unit_test_framework.h"
#include "exceptions.hpp"
#include "player.hpp"
#include "item.hpp"

using namespace std;

using namespace final_proj;

// tests for the room class

// tests that get x will return the x value
TEST(test_base_room_get_x)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");
    Combat_Room cR = Combat_Room(x, y);

    ASSERT_EQUAL(x, oR.get_x());
    ASSERT_EQUAL(x, rR.get_x());
    ASSERT_EQUAL(x, cR.get_x());
}

// tests that get y will return the y value
TEST(test_base_room_get_y)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");
    Combat_Room cR = Combat_Room(x, y);

    ASSERT_EQUAL(y, oR.get_y());
    ASSERT_EQUAL(y, rR.get_y());
    ASSERT_EQUAL(y, cR.get_y());
}

// tests that get type will return the type value
TEST(test_base_room_get_type)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");
    Combat_Room cR = Combat_Room(x, y);

    ASSERT_EQUAL("Treasure", oR.get_type());
    ASSERT_EQUAL("Riddle", rR.get_type());
    ASSERT_EQUAL("Combat", cR.get_type());
}

// tests that room_visited will return true if the room has been visited, and false if not
// tests that visit room will change the room to being visited
TEST(test_base_room_room_visited_and_visit_room)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    oR.visit_room();

    ASSERT_TRUE(oR.room_visited());
    ASSERT_FALSE(rR.room_visited());
}

// tests that an exception is thrown when a player attempts to answer a riddle in a object and 
// combat room
TEST(test_object_and_combat_answer_riddle)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Combat_Room cR = Combat_Room(x, y);

    string answer = "answer";

    try
    {
        oR.answer_riddle(answer);
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no riddle to answer in here!\n", e.what());
    }

    try
    {
        cR.answer_riddle(answer);
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no riddle to answer in here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when hit_monster is used on an object and 
// riddle room
TEST(test_object_and_riddle_hit_monster)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.hit_monster(50);
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster to fight here!\n", e.what());
    }

    try
    {
        rR.hit_monster(50);
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster to fight here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when monster_alive is used on an object and 
// riddle room
TEST(test_object_and_riddle_monster_alive)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.monster_alive();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }

    try
    {
        rR.monster_alive();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when remove_obj is used on a riddle room
TEST(test_riddle_remove_obj)
{
    int x = 5;
    int y = 6;

    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        rR.remove_obj();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no item to pick up here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when monster_attack_damage is used on an object and 
// riddle room
TEST(test_object_and_riddle_monster_attack_damage)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.monster_attack_damage();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }

    try
    {
        rR.monster_attack_damage();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when monster_attack_type is used on an object and 
// riddle room
TEST(test_object_and_riddle_monster_attack_type)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.monster_attack_type();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }

    try
    {
        rR.monster_attack_type();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when monster_name is used on an object and 
// riddle room
TEST(test_object_and_riddle_monster_name)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.monster_name();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }

    try
    {
        rR.monster_name();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that an exception is thrown when monster_points is used on an object and 
// riddle room
TEST(test_object_and_riddle_monster_points)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);
    Riddle_Room rR = Riddle_Room(x, y, "riddle", "riddle answer");

    try
    {
        oR.monster_points();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }

    try
    {
        rR.monster_points();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("There is no monster here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// test that answer_riddle will return true when the riddle is answer correctly, and false otherwise
TEST(test_riddle_answer_riddle)
{
    int x = 5;
    int y = 6;

    string answerTrue = "riddle answer";

    string answerFalse = "wrong answer";

    Riddle_Room rR = Riddle_Room(x, y, "riddle", answerTrue);

    ASSERT_TRUE(rR.answer_riddle(answerTrue));
    ASSERT_FALSE(rR.answer_riddle(answerFalse));
}

// tests that remove_obj will return the removed object in an object room
TEST(test_object_remove_obj_good)
{
    int x = 5;
    int y = 6;

    Item r_item = Item("Sword", "weapon", 50);
    shared_ptr<Item> r_itemPtr= make_shared<Item>(r_item);
    Object_Room oR = Object_Room(x, y, r_item);

    ASSERT_EQUAL(r_itemPtr->m_name, oR.remove_obj()->m_name);
}

// tests that remove_obj will not return the removed object in an object room if the item is null
TEST(test_object_remove_obj_bad)
{
    int x = 5;
    int y = 6;

    Object_Room oR = Object_Room(x, y);

    try
    {
        oR.remove_obj();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("You have already picked up the item in this room.\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that remove_obj will return the removed object in a combat room if the monster is dead
TEST(test_combat_remove_obj_good)
{
    int x = 5;
    int y = 6;

    Item r_item = Item("Sword", "weapon", 50);
    shared_ptr<Item> r_itemPtr= make_shared<Item>(r_item);
    Combat_Room cR = Combat_Room(x, y, r_item);

    cR.hit_monster(100);

    ASSERT_EQUAL(r_itemPtr->m_name, cR.remove_obj()->m_name);
}

// tests that remove_obj will not return the removed object in a combat room if the monster 
// is not dead
TEST(test_combat_remove_obj_bad)
{
    int x = 5;
    int y = 6;

    Item r_item = Item("Sword", "weapon", 50);
    shared_ptr<Item> r_itemPtr= make_shared<Item>(r_item);
    Combat_Room cR = Combat_Room(x, y, r_item);

    try
    {
        cR.remove_obj();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("You cant pick up the sword"
                     " there is a Skeleton here!\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that remove_obj will not return the removed object in an combat room if the item is null
TEST(test_combat_remove_obj_bad2)
{
    int x = 5;
    int y = 6;

    Combat_Room cR = Combat_Room(x, y);

    cR.hit_monster(100);

    cR.remove_obj();

    try
    {
        cR.remove_obj();
    }
    catch(InvalidUserInputException& e)
    {
        ASSERT_EQUAL("You have already picked up the item in this room.\n", e.what());
    }
    // FORMATTING ERROR, COULD NOT DECIHPER HOW TO FIX! TEST IS CORRECT
}

// tests that hit_monster will deal damage to the monster of a combat room
// tests that monster_alive will return true when the monster is alive and false when not
TEST(test_combat_hit_monster_and_monster_alive)
{
    int x = 5;
    int y = 6;

    Combat_Room cR = Combat_Room(x, y);

    ASSERT_TRUE(cR.monster_alive());

    cR.hit_monster(100);

    ASSERT_FALSE(cR.monster_alive());
}


TEST_MAIN()