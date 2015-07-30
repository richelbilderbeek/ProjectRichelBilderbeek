#include <cassert>

struct Int
{
  int x;
};

int main()
{
  Int * const my_int = new Int;
  my_int->x = 42;

  //Evaluates both operands
  if ( (static_cast<bool>(my_int)) & (my_int->x == 42) )
  {
    //OK
  }
  else
  {
    assert(!"Should not get here");
  }
  Int * const my_null = 0;

  //Only evaluates the left operand
  if ( (static_cast<bool>(my_null) ) & (my_null->x == 0) )
  {
    assert(!"Should not get here");
  }
  else if ( (static_cast<bool>(my_null) ) & (my_null->x != 0) )
  {
    assert(!"Should not get here");
  }
  else
  {
    //OK
  }
}
