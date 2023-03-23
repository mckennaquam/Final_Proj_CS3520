#include <set>
#include <map>
#include <string>

using namespace std;

namespace final_proj
{

    // class to represent the player
    class player
    {
        // public methods for the player
    public:
        // custom constrctor for player
        player(int &health, int &strength, int &defense)
        {
            m_health = health;
            m_strength = strength;
            m_defense = defense;
            m_inventory = set<item, item_rank>();
            m_commands = {
                //{"check inventory", null},
                //{"pickup item", }
                //{"check points"}
                //{"check health"}
                //{"check strength"}
                //{"use item" }
                // combat commands
                //{"defend",}
                //{"attack",}
                //{"parry",}
                //{"retreat",}
            };
        }

        // default constuctor for player
        player() : player(20, 10, 0){};

        // adds an item to player's inventory
        // if a player already has an item of that type, checks to see if new item has better base stat
        void add_to_inventory(const item &new_item);

        // preforms an player action and returns a descrining statment
        // player actions are a private field
        // if action doesnt exist, then return "unknown command"
        string apply_action_noncombat(istringstream &iss); // might need room and monster

        string apply_action_combat(istringstream &iss); // might need room and monster

        // private fields for player
    private:
        int m_health;
        int m_strength;
        int m_defense;
        int m_points;
        set<item, item_rank> m_inventory;
        map<string, player_command> m_commands; // might need room and monster
    };

    // transparaent functor for item
    struct item_rank
    {
        using is_transparent = void;

        bool operator()(const final_proj::item &i1, const final_proj::item &i2) const;
        bool operator()(const final_proj::item &i1, const string &s1) const;
        bool operator()(const string &s1, const final_proj::item &i1) const;
    };

    // struct for item
    struct item
    {
        string m_name;
        string m_type;
        int m_stat;
    };

    class player_command
    {
    public:
        string apply_action(istringstream &iss, player &player);
        bool combat_action();

    private:
        function<string(istringstream &iss, player &player)> m_action; // might need room and monster
        bool m_combat;
    }

}