#include <iostream>

struct Animal
{
  virtual ~Animal() {}
  virtual void MakeSound() const = 0;
  virtual void Walk() const = 0;
};

struct Cow : public Animal
{
  void MakeSound() const final { std::cout << "moo\n"; } //MakeSound is final
  virtual void Walk() const { std::cout << "walk\n"; }
};

struct NonCow : public Cow
{
  //void MakeSound() const { std::cout << "MOO\n"; } //will not compile: Cow::MakeSound is final
  void Walk() const { std::cout << "non walk\n"; }
};

int main()
{
  Cow cow;
  cow.MakeSound();
  cow.Walk();

  NonCow noncow;
  noncow.MakeSound();
  noncow.Walk();
}
