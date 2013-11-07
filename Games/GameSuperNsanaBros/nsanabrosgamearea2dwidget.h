#ifndef NSANABROSGAMEAREA2DWIDGET_H
#define NSANABROSGAMEAREA2DWIDGET_H

#include <vector>

#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "nsanabrosstlfwdheader.h"

namespace ribi {

///NsanaBrosGameAreaWidget contains all information
///to display the game area.
struct NsanaBrosGameArea2dWidget
{
  NsanaBrosGameArea2dWidget();
  //const NsanaBrosGameArea2d * GetArea() const;

  //const std::vector<const NsanaBrosSprite*> GetSprites() const;

  //void KeyPress(const int key);
  //void KeyRelease(const int key);
  //void OnTimer();

  private:
  ~NsanaBrosGameArea2dWidget() {}
  friend void boost::checked_delete<>(NsanaBrosGameArea2dWidget *);

  //boost::scoped_ptr<NsanaBrosGameArea2d> m_area;
  //boost::scoped_ptr<NsanaBrosKeys> m_keys;
};

} //~namespace ribi

#endif // NSANABROSGAMEAREA2DWIDGET_H
