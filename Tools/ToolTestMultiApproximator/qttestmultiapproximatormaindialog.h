#ifndef QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H
#define QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "multiapproximator.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestMultiApproximatorMainDialog;
}

namespace ribi {

class QtToolTestMultiApproximatorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestMultiApproximatorMainDialog(QWidget *parent = 0) noexcept;
  QtToolTestMultiApproximatorMainDialog(const QtToolTestMultiApproximatorMainDialog&) = delete;
  QtToolTestMultiApproximatorMainDialog& operator=(const QtToolTestMultiApproximatorMainDialog&) = delete;
  ~QtToolTestMultiApproximatorMainDialog() noexcept;
  
private slots:
  void on_button_clicked() noexcept;

private:
  Ui::QtToolTestMultiApproximatorMainDialog *ui;
  typedef double Key;
  typedef double Value;
  typedef std::map<Key,Value> Container;
  typedef std::multimap<Key,Value> MultiContainer;
  typedef MultiApproximator<Key,Value,MultiContainer> MultiApproximator_t;
  typedef Approximator<Key,Value,Container> Approximator_t;
  MultiApproximator_t m_multi_approximator;

  ///The curve of the approximation of the (non-Multi)Approximator
  QwtPlotCurve * const m_curve_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_approximation; //DONT!

  ///The curve of the approximation of the MultiApproximator
  QwtPlotCurve * const m_curve_multi_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_multi_approximation; //DONT!

  ///The curve of the raw values of the MultiApproximator
  QwtPlotCurve * const m_curve_multi_values;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_multi_values; //DONT!

  ///The curve of the raw values of the (non-Multi)Approximator
  QwtPlotCurve * const m_curve_values;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_values; //DONT!

  ///Contains the plot of the MultiApproximator
  const boost::shared_ptr<QwtPlot> m_multi_plot;

  ///Contains the plot of the (non-Multi)Approximator
  const boost::shared_ptr<QwtPlot> m_plot;

  void Plot() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H
