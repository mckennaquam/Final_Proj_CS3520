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
    Room_Factory new_board = Room_Factory(10, 10);

    new_board.get_room_at(0, 0);
}