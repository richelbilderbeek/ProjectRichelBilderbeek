#include "lizard.h"

int main()
{
  const Lizard male(Gender::male);
  assert(male.GetGender() == Gender::male);
  const Lizard female(Gender::female);
  assert(female.GetGender() == Gender::female);
}
