#ifndef QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H
#define QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H

#include <vector>

#include "mutualismbreakdownerseagrasssystem.h"
#include "mutualismbreakdownerparameters.h"
#include "qthideandshowdialog.h"
#include "mutualismbreakdownerspatialsimulation.h"
struct QwtPlotCurve;

namespace Ui {
  class QtMutualismBreakdownerSpatialPlotDialog;
}

namespace ribi {
namespace mb {

struct SpatialSimulation;
struct QtMutualismBreakdownerParametersWidget;
struct QtMutualismBreakdownerSpatialWidget;

class QtMutualismBreakdownerSpatialPlotDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:


  explicit QtMutualismBreakdownerSpatialPlotDialog(QWidget *parent = 0);
  ~QtMutualismBreakdownerSpatialPlotDialog();
  Parameters GetParameters() const;
  void SetParameters(const Parameters& parameters);

private slots:

  void StartRun();
  void NextTimestep();

private:
  using Simulation = SpatialSimulation;

  Ui::QtMutualismBreakdownerSpatialPlotDialog *ui;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;
  QtMutualismBreakdownerSpatialWidget * const m_seagrass_widget;
  QtMutualismBreakdownerSpatialWidget * const m_sulfide_widget;
  QTimer * const m_timer;
  std::unique_ptr<Simulation> m_simulation;
  void DisplayGrid();
};

} //~namespace mb
} //~namespace ribi

#endif // QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H
