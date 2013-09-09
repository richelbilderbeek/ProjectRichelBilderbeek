#include <iostream>

struct Animal
{
  virtual ~Animal() {}
  virtual void MakeSound() const = 0;
};

struct Cat : public Animal
{
  void MakeSound() const { std::cout << "Meow" << std::endl; }
};

struct Dog : public Animal
{
  void MakeSound() const { std::cout << "Bark" << std::endl; }
};

int main()
{
  const Cat c;
  c.MakeSound();

  const Dog d;
  d.MakeSound();
}

/* Screen output:

Meow
Bark
Press <RETURN> to close this window...

*/
