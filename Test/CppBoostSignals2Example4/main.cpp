#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

void EmptySlot() {}

int main()
{
  boost::signals2::signal<void()> signal;

  //A signal is connected to no slots
  assert(signal.num_slots() == 0);
  signal.connect(EmptySlot);

  //Adding a slot increases num_slots
  assert(signal.num_slots() == 1);
  signal.connect(EmptySlot);

  //Adding the same slot again increases num_slots
  assert(signal.num_slots() == 2);

  //Disconnect that slot removes both connections
  signal.disconnect(EmptySlot);
  assert(signal.num_slots() == 0);
}
