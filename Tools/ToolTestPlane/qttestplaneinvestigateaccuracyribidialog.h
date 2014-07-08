#ifndef QTTESTPLANEINVESTIGATEACCURAYRIBIDIALOG_H
#define QTTESTPLANEINVESTIGATEACCURAYRIBIDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPlaneInvestigateAccuracyRibiDialog;
}

namespace ribi {

struct QtSurfacePlotWidget;
struct Plane;

class QtTestPlaneInvestigateAccuracyRibiDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestPlaneInvestigateAccuracyRibiDialog(QWidget *parent = 0);
  QtTestPlaneInvestigateAccuracyRibiDialog(const QtTestPlaneInvestigateAccuracyRibiDialog&) = delete;
  QtTestPlaneInvestigateAccuracyRibiDialog& operator=(const QtTestPlaneInvestigateAccuracyRibiDialog&) = delete;
  ~QtTestPlaneInvestigateAccuracyRibiDialog() noexcept;
    
private slots:
  void keyPressEvent(QKeyEvent *event);
  void OnAnyChange();
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtTestPlaneInvestigateAccuracyRibiDialog *ui;

  const boost::shared_ptr<QtSurfacePlotWidget> m_widget_x;
  const boost::shared_ptr<QtSurfacePlotWidget> m_widget_y;
  const boost::shared_ptr<QtSurfacePlotWidget> m_widget_z;

  boost::shared_ptr<Plane> CreatePlane() const noexcept;

  /*
  ///Rescale calculates a value between old_min and old_max its relative place and transforms
  ///this relative position to a new_min and new_max
  ///For example: for the old range [1,5], the value 2 is at 25% of this range. Transforming this
  ///to the new range range [0,100] results in a 25
  static double Rescale(
    const double value,
    const double oldMin,
    const double oldMax,
    const double newMin,
    const double newMax);
  */
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTPLANEINVESTIGATEACCURAYRIBIDIALOG_H
