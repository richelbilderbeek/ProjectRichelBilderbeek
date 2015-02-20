#include <cassert>

struct Strategy
{
    virtual int DoIt(const int x) const = 0;
};

struct TripleStrategy : public Strategy
{
    int DoIt(const int x) const { return x * 3; }
};

struct QuadStrategy : public Strategy
{
    int DoIt(const int x) const { return x * 4; }
};

struct MultiplyByStrategy : public Strategy
{
    MultiplyByStrategy(const int my_multiplier) : m_multiplier(my_multiplier) {}

    int DoIt(const int x) const { return x * m_multiplier; }

private:
    const int m_multiplier;
};

int main()
{
    const Strategy * my_strategy = new TripleStrategy;
    assert(my_strategy->DoIt(42) == 3 * 42);

    my_strategy = new MultiplyByStrategy(314);
    assert(my_strategy->DoIt(1) == 314 * 1);
    assert(my_strategy->DoIt(2) == 314 * 2);
    assert(my_strategy->DoIt(3) == 314 * 3);
    assert(my_strategy->DoIt(4) == 314 * 4);
    assert(my_strategy->DoIt(5) == 314 * 5);
    assert(my_strategy->DoIt(6) == 314 * 6);

    my_strategy = new TripleStrategy;
    assert(my_strategy->DoIt(3) == 3 * 3);

    my_strategy = new MultiplyByStrategy(42);
    assert(my_strategy->DoIt(3) == 42 * 3);

}
