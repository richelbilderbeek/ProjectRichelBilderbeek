#ifndef REVERSIMAINDIALOG_H
#define REVERSIMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace reversi {

struct MainDialog
{
  MainDialog();

  ///Start a Reversi game
  void Execute(const int size);

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIMAINDIALOG_H
