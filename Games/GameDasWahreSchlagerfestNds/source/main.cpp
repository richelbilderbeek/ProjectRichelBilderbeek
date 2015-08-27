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
    //Screen is 256x196 (w x h), thus 8x6 blocks of 32x32
    ribi::dws::NdsGameDialog d;
    ribi::dws::Widget w(&d,8,6);
    //w.SetDisplay(&d);
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
