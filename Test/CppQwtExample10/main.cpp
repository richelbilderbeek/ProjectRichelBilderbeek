#include <cassert>
#include <cmath>
#include <string>
#include <string>
#include <sstream>

#include <QApplication>
#include <QDesktopWidget>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_column_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_text.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QwtPlotMultiBarChart * const bar_plot = new QwtPlotMultiBarChart;

  for (int i=0; i!=2; ++i)
  {
    QwtColumnSymbol * symbol{new QwtColumnSymbol(QwtColumnSymbol::Box)};
    QPalette bar_color{i == 0 ? Qt::red : Qt::blue};
    symbol->setPalette(bar_color);
    bar_plot->setSymbol(i,symbol);
  }
  QList<QwtText> titles;
  titles.push_back(QwtText("A"));
  titles.push_back(QwtText("B"));
  bar_plot->setBarTitles(titles);


  QVector<QVector<double>> data;
  for (int i=0; i!=11; ++i)
  {
    const double a{static_cast<double>(i) / 10.0};
    const double b{1.0-a};
    QVector<double> this_bar = {a,b};
    data.push_back(this_bar);
  }
  bar_plot->setSamples(data);

  bar_plot->setStyle(QwtPlotMultiBarChart::Stacked);


  //plot is used to display the bar_plot on screen
  QwtPlot * const plot = new QwtPlot(QwtText("Increase of A"));
  bar_plot->attach(plot);
  plot->setAxisScale(QwtPlot::xBottom,0.0,10.0,1);
  plot->setAxisScale(QwtPlot::yLeft,0.0,1.0,0.1);
  plot->setAxisTitle(QwtPlot::xBottom,"Sample");
  plot->setAxisTitle(QwtPlot::yLeft,"Fractions");

  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  //Put plot in screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    plot->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    plot->move(screen.center() - plot->geometry().center());
  }

  plot->show();
  return a.exec();
}


