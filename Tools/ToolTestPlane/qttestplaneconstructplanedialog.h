#ifndef QTTESTPLANEMAINDIALOG_H
#define QTTESTPLANEMAINDIALOG_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/geometry.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPlaneConstructPlaneDialog;
}

namespace ribi {

class QtTestPlaneConstructPlaneDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPlaneConstructPlaneDialog(QWidget *parent = 0);
  QtTestPlaneConstructPlaneDialog(const QtTestPlaneConstructPlaneDialog&) = delete;
  QtTestPlaneConstructPlaneDialog& operator=(const QtTestPlaneConstructPlaneDialog&) = delete;
  ~QtTestPlaneConstructPlaneDialog() noexcept;
    
private slots:
  void OnAnyChange();

private:
  Ui::QtTestPlaneConstructPlaneDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

//std::ostream& operator<<(std::ostream& os, const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept;

} //~namespace ribi


#endif // QTTESTPLANEMAINDIALOG_H
