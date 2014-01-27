#ifndef MAZIAKMAINDIALOG_H
#define MAZIAKMAINDIALOG_H

#include <set>
#include <vector>

#include "maziakfwd.h"
#include "maziakkey.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

struct MainDialog
{
  void OnTimerPressKey(const Key key);

  void OnKeyPress(const Key key);
  void OnKeyRelease(const Key key);

  private:
  std::set<Key> m_keys;
};

} //namespace maziak
} //namespace ribi


#endif // MAZIAKMAINDIALOG_H
