enum class Color { red  , orange };
enum class Fruit { apple, orange };

int main()
{
  const Color c = Color::orange;
  const Fruit a = Fruit::orange;
  //const Fruit b = Color::orange; //Won't compile: cannot convert 'Color' to 'Fruit' in initialization
}
