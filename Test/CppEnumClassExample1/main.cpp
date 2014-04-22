enum class Color { red  , orange };
enum class Fruit { apple, orange };

#include <cassert>

int main()
{
  const Color c = Color::orange;
  const Fruit a = Fruit::orange;
  //const Fruit b = Color::orange; //Won't compile: cannot convert 'Color' to 'Fruit' in initialization
  static_assert(static_cast<int>(a) == static_cast<int>(c),
    "Can do static_assert on integer conversions");
}
