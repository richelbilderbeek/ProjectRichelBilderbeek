#include <iostream>

struct Animal
{
  //Base classes must have a virtual destructor
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

  //Now use the same Animal pointer for different animals
  Animal * animal{new Cat};
  animal->MakeSound();
  delete animal;
  animal = new Dog;
  animal->MakeSound();
  delete animal;
}

/* Screen output:

Meow
Bark
Press <RETURN> to close this window...

*/
