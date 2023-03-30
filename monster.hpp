using namespace std;

namespace final_proj
{
    class Base_Monster
    {
    public:
        void take_damage();
        void deal_damage();
        bool is_alive();

    private:
        string name;
        int m_health;
        int m_stength;
        int m_points;
        Item equipped;
    };
}