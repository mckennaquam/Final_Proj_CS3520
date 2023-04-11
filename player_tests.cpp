#include <iostream>

#include "unit_test_framework.h"
#include "exceptions.hpp"
#include "player.hpp"
#include "item.hpp"

using namespace std;

using namespace final_proj;

// Test to ensure check_stats returns a vector of the player's stats in the order of health, 
// strength, and defense
TEST(test_check_stats)
{
    Player player1 = Player();
    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 50);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

// Test to ensure check_stats returns a vector of the player's stats in the order of health, 
// strength, and defense
TEST(test_pick_up_object_health)
{
    final_proj::Player player1();
    vector<final_proj::Item> test_inventory;
    final_proj::Item item1("Potion", "health", 50);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}


TEST_MAIN()