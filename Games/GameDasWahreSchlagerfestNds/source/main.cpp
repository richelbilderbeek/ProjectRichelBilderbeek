#include <cassert>
#include <stdexcept>

#include "ndsgamedialog.h"
#include "daswahreschlagerfestwidget.h"
int main(/* int argc, char* argv[0] */)
{
  #ifndef NDEBUG
  NO DEBUG MODE IN NDS
  #endif
  assert(1==2);


  try
  {
    ribi::dws::Widget w;
    ribi::dws::NdsGameDialog d;
    w.SetDisplay(&d);
    w.Execute();
  }
  catch (std::logic_error& e)
  {
    //Helper().Cout(e.what());
  }
  catch (std::runtime_error& e)
  {
    //Helper().Cout(e.what());
  }
}
