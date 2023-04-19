#include <iostream>

#include "unit_test_framework.h"
#include "exceptions.hpp"
#include "player.hpp"
#include "item.hpp"

using namespace std;

using namespace final_proj;

// tests for the monster class

// tests that take damage will subtract the given damage from a mob's health
// tests that get health will return a mob's updated health
TEST(test_take_damage_and_get_health)
{
    Skeleton mob1 = Skeleton();

    mob1.take_damage(5);

    ASSERT_EQUAL(20, mob1.get_health());
}

// tests that get health will return 0 when a mob's health drops into negative values
TEST(test_get_health_less_than_0)
{
    Skeleton mob1 = Skeleton();

    mob1.take_damage(50);

    ASSERT_EQUAL(0, mob1.get_health());
}

// tests that is alive will return true when a mob is alive and false when a mob is dead
TEST(test_is_alive)
{
    Skeleton mob1 = Skeleton();

    ASSERT_TRUE(mob1.is_alive());

    mob1.take_damage(50);

    ASSERT_FALSE(mob1.is_alive());
}

// tests that get name will return a string of the mob's name
TEST(test_get_name)
{
    Skeleton mob1 = Skeleton();
    string name = "Skeleton";

    mob1.take_damage(50);

    ASSERT_EQUAL(name, mob1.get_name());
}

// tests that point val will return the mob's point value
TEST(test_point_val)
{
    Skeleton mob1 = Skeleton();
    string name = "Skeleton";

    ASSERT_EQUAL(30, mob1.point_val());
}

TEST_MAIN()