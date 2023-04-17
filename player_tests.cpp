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

TEST(test_check_inventory_and_pick_up_potion)
{
    Player player1 = Player();
    Item health_potion_item = Item("Health rank 5", "potion", 5);
    shared_ptr<Item> health_potion_item_pointer = make_shared<Item>(health_potion_item);
    string health_potion_item_name = "Health rank 5";

    player1.pick_up_object(health_potion_item_pointer);

    vector<string> test_vector;

    test_vector.insert(test_vector.begin(), health_potion_item_name);

    ASSERT_EQUAL(test_vector, player1.check_inventory());
}

TEST(test_pick_up_item_strength) 
{
    Player player1 = Player();
    Item strength_item = Item("Sword", "weapon", 5);
    shared_ptr<Item> strength_item_pointer = make_shared<Item>(strength_item);

    player1.pick_up_object(strength_item_pointer);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 15);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_pick_up_object_strength_weaker) 
{
    Player player1 = Player();
    Item strength_item = Item("Sword", "weapon", 50);
    shared_ptr<Item> strength_item_pointer = make_shared<Item>(strength_item);

    player1.pick_up_object(strength_item_pointer);

    Item strength_item_bad = Item("Bad Sword", "weapon", 5);
    shared_ptr<Item> strength_item_pointer_bad = make_shared<Item>(strength_item_bad);
    string bad_item_name = "Bad Sword";

    try
    {
        player1.pick_up_object(strength_item_pointer_bad);
    }
    catch (InvalidUserInputException &e)
    {
        ASSERT_EQUAL("The " + bad_item_name + " you picked up is weak! You drop it an proceed on.\n", e.what());
    }
}

TEST(test_pick_up_item_defense) 
{
    Player player1 = Player();
    Item defense_item = Item("Sheild", "defense", 5);
    shared_ptr<Item> defense_item_pointer = make_shared<Item>(defense_item);

    player1.pick_up_object(defense_item_pointer);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 5);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_pick_up_object_defense_weaker) 
{
    Player player1 = Player();
    Item defense_item = Item("Sheild", "defense", 50);
    shared_ptr<Item> defense_item_pointer = make_shared<Item>(defense_item);
    string good_item_name = "Sheild";

    player1.pick_up_object(defense_item_pointer);

    Item defense_item_bad = Item("Bad Sheild", "defense", 5);
    shared_ptr<Item> defense_item_pointer_bad = make_shared<Item>(defense_item_bad);
    string bad_item_name = "Bad Sheild";

    try
    {
        player1.pick_up_object(defense_item_pointer_bad);
    }
    catch (InvalidUserInputException &e)
    {
        ASSERT_EQUAL("The " + bad_item_name + " you picked up is weak! You drop it an proceed on.\n", e.what());
    }
}

TEST(test_pick_up_object_treasure_and_update_points_and_get_points) 
{
    Player player1 = Player();
    Item treasure_item = Item("Gold", "treasure", 5);
    shared_ptr<Item> treasure_item_pointer = make_shared<Item>(treasure_item);

    player1.pick_up_object(treasure_item_pointer);

    ASSERT_EQUAL(5, player1.get_points());
}

TEST(test_use_item_health_potion_low_health_and_take_damage) 
{
    Player player1 = Player();
    Item health_potion_item = Item("Health rank 5", "potion", 5);
    shared_ptr<Item> health_potion_item_pointer = make_shared<Item>(health_potion_item);
    string health_potion_item_name = "Health rank 5";
    string health_potion_item_type = "potion";
    int health_potion_item_rank = 5;

    player1.pick_up_object(health_potion_item_pointer);

    player1.take_damage(50);

    player1.use_item(health_potion_item_name, health_potion_item_type, health_potion_item_rank);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 55);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_health_potion_high_health_and_take_damage) 
{
    Player player1 = Player();
    Item health_potion_item = Item("Health rank 5", "potion", 5);
    shared_ptr<Item> health_potion_item_pointer = make_shared<Item>(health_potion_item);
    string health_potion_item_name = "Health rank 5";
    string health_potion_item_type = "potion";
    int health_potion_item_rank = 5;

    player1.pick_up_object(health_potion_item_pointer);

    player1.take_damage(3);

    player1.use_item(health_potion_item_name, health_potion_item_type, health_potion_item_rank);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_health_potion_full_health) 
{
    Player player1 = Player();
    Item health_potion_item = Item("Health rank 5", "potion", 5);
    shared_ptr<Item> health_potion_item_pointer = make_shared<Item>(health_potion_item);
    string health_potion_item_name = "Health rank 5";
    string health_potion_item_type = "potion";
    int health_potion_item_rank = 5;

    player1.pick_up_object(health_potion_item_pointer);

    try
    {
        player1.use_item(health_potion_item_name, health_potion_item_type, health_potion_item_rank);
    }
    catch (InvalidUserInputException &e)
    {
        ASSERT_EQUAL("Your health is full! No need to use this item.\n", e.what());
    }
}

TEST(test_use_item_attack_potion) 
{
    Player player1 = Player();
    Item attack_potion_item = Item("Attack rank 5", "potion", 5);
    shared_ptr<Item> attack_potion_item_pointer = make_shared<Item>(attack_potion_item);
    string attack_potion_item_name = "Attack rank 5";
    string attack_potion_item_type = "potion";
    int attack_potion_item_rank = 5;

    player1.pick_up_object(attack_potion_item_pointer);

    player1.use_item(attack_potion_item_name, attack_potion_item_type, attack_potion_item_rank);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 15);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_defense_potion) 
{
    Player player1 = Player();
    Item defense_potion_item = Item("Defense rank 5", "potion", 5);
    shared_ptr<Item> defense_potion_item_pointer = make_shared<Item>(defense_potion_item);
    string defense_potion_item_name = "Defense rank 5";
    string defense_potion_item_type = "potion";
    int defense_potion_item_rank = 5;

    player1.pick_up_object(defense_potion_item_pointer);

    player1.use_item(defense_potion_item_name, defense_potion_item_type, defense_potion_item_rank);

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 5);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_use_item_empty_inventory) 
{
    Player player1 = Player();
    string attack_potion_item_name = "Attack rank 5";
    string attack_potion_item_type = "potion";
    int attack_potion_item_rank = 5;

    try
    {
        player1.use_item(attack_potion_item_name, attack_potion_item_type, attack_potion_item_rank);
    }
    catch (InvalidUserInputException &e)
    {
        ASSERT_EQUAL("Item " + attack_potion_item_name + " not found", e.what());
    }
}

TEST(test_remove_buff_attack_potion) 
{
    Player player1 = Player();
    Item attack_potion_item = Item("Attack rank 5", "potion", 5);
    shared_ptr<Item> attack_potion_item_pointer = make_shared<Item>(attack_potion_item);
    string attack_potion_item_name = "Attack rank 5";
    string attack_potion_item_type = "potion";
    int attack_potion_item_rank = 5;

    player1.pick_up_object(attack_potion_item_pointer);

    player1.use_item(attack_potion_item_name, attack_potion_item_type, attack_potion_item_rank);

    player1.remove_buff();

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

TEST(test_remove_buff_defense_potion) 
{
    Player player1 = Player();
    Item defense_potion_item = Item("Defense rank 5", "potion", 5);
    shared_ptr<Item> defense_potion_item_pointer = make_shared<Item>(defense_potion_item);
    string defense_potion_item_name = "Defense rank 5";
    string defense_potion_item_type = "potion";
    int defense_potion_item_rank = 5;

    player1.pick_up_object(defense_potion_item_pointer);

    player1.use_item(defense_potion_item_name, defense_potion_item_type, defense_potion_item_rank);

    player1.remove_buff();

    vector<int> test_vector;

    test_vector.insert(test_vector.begin(), 0);
    test_vector.insert(test_vector.begin(), 10);
    test_vector.insert(test_vector.begin(), 100);

    ASSERT_EQUAL(test_vector, player1.check_stats());
}

// Is get strength supposed to return the baseStrength or is it supposed to update? small fix, I just forgor
TEST(test_get_strength) 
{
    Player player1 = Player();
    Item strength_item = Item("Sword", "weapon", 5);
    shared_ptr<Item> strength_item_pointer = make_shared<Item>(strength_item);

    ASSERT_EQUAL(10, player1.get_strength());

    player1.pick_up_object(strength_item_pointer);

    ASSERT_EQUAL(15, player1.get_strength());
}

TEST(test_player_alive_alive) 
{
    Player player1 = Player();

    ASSERT_TRUE(player1.player_alive());
}

TEST(test_player_alive_dead) 
{
    Player player1 = Player();

    player1.take_damage(100);

    ASSERT_FALSE(player1.player_alive());
}


TEST_MAIN()