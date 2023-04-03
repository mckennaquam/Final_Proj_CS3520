#include <set>
#include <map>
#include <string>

using namespace std;

namespace final_proj
{

    // class to represent the player
    class Player
    {
        // public methods for the player
        vector<int> check_stats();
        set<Item, Item_Rank> check_inventory();
        void use_item();

    public:
        // custom constrctor for player
        player(int &health, int &strength, int &defense)
        {
            m_health = health;
            m_strength = strength;
            m_defense = defense;
            m_inventory = set<Item, Item_Rank>();
        }

        // private fields for player
    private:
        int m_health;
        int m_strength;
        int m_defense;
        int m_points;
        set<Item, Item_Rank> m_inventory;
        shared_ptr<Base_Room> m_current_room;
    };

    // transparaent functor for item
    struct Item_Rank
    {
        using is_transparent = void;

        bool operator()(const final_proj::Item &i1, const final_proj::Item &i2) const;
        bool operator()(const final_proj::Item &i1, const string &s1) const;
        bool operator()(const string &s1, const final_proj::Item &i1) const;
    };

    // struct for item
    struct Item
    {
        string m_name;
        string m_type;
        int m_stat;
    };

}