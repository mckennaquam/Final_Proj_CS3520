#include <iostream>

#include "unit_test_framework.h"
#include "exceptions.hpp"
#include "player.hpp"
#include "item.hpp"
#include "room_factory.hpp"
#include "room.hpp"

using namespace std;

using namespace final_proj;


TEST_MAIN()

TEST(test_room_factory_constructor)
{
    Room_Factory rf = Room_Factory(10, 10);

    shared_ptr<Base_Room> room1 = make_shared<Object_Room>(0, 0);
    shared_ptr<Base_Room> room2 = make_shared<Riddle_Room>(1, 0, "riddle", "riddle_answer");
    shared_ptr<Base_Room> room3 = make_shared<Combat_Room>(2, 0);

    ASSERT_EQUAL(room1, rf.get_room_at(0, 0));
    ASSERT_EQUAL(room2, rf.get_room_at(1, 0));
    ASSERT_EQUAL(room3, rf.get_room_at(2, 0));
}