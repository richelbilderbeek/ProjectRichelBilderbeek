#ifndef QTTESTPLANEMAINDIALOG_H
#define QTTESTPLANEMAINDIALOG_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPlaneConstructPlaneDialog;
}

namespace ribi {

struct Plane;

class QtTestPlaneConstructPlaneDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPlaneConstructPlaneDialog(QWidget *parent = 0);
  QtTestPlaneConstructPlaneDialog(const QtTestPlaneConstructPlaneDialog&) = delete;
  QtTestPlaneConstructPlaneDialog& operator=(const QtTestPlaneConstructPlaneDialog&) = delete;
  ~QtTestPlaneConstructPlaneDialog() noexcept;
    
private slots:
  void OnAnyChange() noexcept;

private:
  Ui::QtTestPlaneConstructPlaneDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi


#endif // QTTESTPLANEMAINDIALOG_H
