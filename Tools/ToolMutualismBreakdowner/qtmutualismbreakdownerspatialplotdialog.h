#ifndef QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H
#define QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H

#include <vector>

#include "seagrasssystem.h"
#include "parameters.h"
#include "qthideandshowdialog.h"
#include "spatialsimulation.h"
struct QwtPlotCurve;
struct QtMutualismBreakdownerParametersWidget;
struct QtMutualismBreakdownerSpatialWidget;
struct SpatialSimulation;

namespace Ui {
  class QtMutualismBreakdownerSpatialPlotDialog;
}

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
  //using System = SeagrassSystem;
  using Simulation = SpatialSimulation;
  //using Grid = std::vector<std::vector<System>>;

  Ui::QtMutualismBreakdownerSpatialPlotDialog *ui;
  QtMutualismBreakdownerParametersWidget * const m_parameters_widget;
  QtMutualismBreakdownerSpatialWidget * const m_seagrass_widget;
  QtMutualismBreakdownerSpatialWidget * const m_sulfide_widget;
  QTimer * const m_timer;
  //Grid m_grid;
  std::unique_ptr<Simulation> m_simulation;
  void DisplayGrid();
};

#endif // QTMUTUALISMBREAKDOWNERSPATIALPLOTDIALOG_H
