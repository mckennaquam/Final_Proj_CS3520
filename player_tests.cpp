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
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_check_inventory)
{

}

// Test to ensure check_stats returns a vector of the player's stats in the order of health, 
// strength, and defense
TEST(test_pick_up_object_health)
{
}

// Test to ensure check_stats returns a vector of the player's stats in the order of health, 
// strength, and defense
TEST(test_pick_up_object_strength)
{
    Player player1 = Player();
    Item strength_potion = Item("Elixir", "Damage", 5);
    string strength_potion_name = "Elixir";
    player1.pick_up_object(strength_potion);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_pick_up_object_strength_weaker) 
{

}

// Test to ensure check_stats returns a vector of the player's stats in the order of health, 
// strength, and defense
TEST(test_pick_up_object_defense)
{
    /*
    Player player1() = Player();
    vector<final_proj::Item> test_inventory;
    final_proj::Item item1("Potion", "health", 50);

    ASSERT_EQUAL(test_inventory, player1.check_stats());
    */
}

TEST(test_pick_up_object_defense_weaker) 
{

}

TEST(test_pick_up_object_treasure) 
{

}

TEST(test_pick_up_item_strength) 
{
    Player player1 = Player();
    Item strength_item = Item("Sword", "weapon", 5);
    unique_ptr<Item> strength_item_pointer = make_unique<Item>(strength_item);

    string strength_item_name = "Sword";

    player1.pick_up_object(move(strength_item_pointer));

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 15);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_defense) 
{
    Player player1 = Player();
    Item defense_item = Item("Sheild", "defense", 5);
    string defense_item_name = "Sheild";

    player1.pick_up_object(defense_item);

    player1.use_item(defense_item_name);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 15);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_health_almost_max_health) 
{
    Player player1 = Player();
    Item health_potion = Item("Elixir", "potion", 20);
    string health_potion_name = "Elixir";

    player1.pick_up_object(health_potion);

    player1.take_damage(10);

    player1.use_item(health_potion_name);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_health_not_near_max_health) 
{
    Player player1 = Player();
    Item health_potion = Item("Elixir", "potion", 20);
    string health_potion_name = "Elixir";

    player1.pick_up_object(health_potion);

    player1.take_damage(80);

    player1.use_item(health_potion_name);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 70);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_health_at_max_health) 
{
    Player player1 = Player();
    Item health_potion = Item("Elixir", "potion", 20);
    string health_potion_name = "Elixir";

    player1.pick_up_object(health_potion);

    player1.use_item(health_potion_name);
    try
    {
        player1.use_item(health_potion_name);
    }
    catch (final_proj::InvalidUserInputException &e)
    {
        ASSERT_EQUAL("Your health is full!", e.what());
  }
}

TEST(test_remove_buff_attack) 
{

}

TEST(test_remove_buff_defense) 
{

}

TEST(test_take_damage) 
{
    Player player1 = Player();
    player1.take_damage(50);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 50);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_update_location) 
{

}





TEST_MAIN()