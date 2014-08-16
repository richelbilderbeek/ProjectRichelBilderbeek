#ifndef QTTESTPLANEINVESTIGATEACCURACYDIALOG_H
#define QTTESTPLANEINVESTIGATEACCURACYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestPlaneInvestigateAccuracyQwtDialog;
}

namespace ribi {

struct Plane;
struct QwtTestPlanePlot;

class QtTestPlaneInvestigateAccuracyQwtDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPlaneInvestigateAccuracyQwtDialog(QWidget *parent = 0);
  QtTestPlaneInvestigateAccuracyQwtDialog(const QtTestPlaneInvestigateAccuracyQwtDialog&) = delete;
  QtTestPlaneInvestigateAccuracyQwtDialog& operator=(const QtTestPlaneInvestigateAccuracyQwtDialog&) = delete;
  ~QtTestPlaneInvestigateAccuracyQwtDialog();

private slots:
  void OnAnyChange();

private:

  Ui::QtTestPlaneInvestigateAccuracyQwtDialog *ui;
  boost::shared_ptr<QwtTestPlanePlot> m_plot_x;
  boost::shared_ptr<QwtTestPlanePlot> m_plot_y;
  boost::shared_ptr<QwtTestPlanePlot> m_plot_z;

  boost::shared_ptr<Plane> CreatePlane() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTPLANEINVESTIGATEACCURACYDIALOG_H
