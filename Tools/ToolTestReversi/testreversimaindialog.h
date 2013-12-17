#ifndef TESTREVERSIMAINDIALOG_H
#define TESTREVERSIMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include "about.h"
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct TestReversiMainDialog
{
  TestReversiMainDialog();

  ///Start a Reversi game
  void Execute();

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTREVERSIMAINDIALOG_H
