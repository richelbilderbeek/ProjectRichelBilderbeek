#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>

#include <qwt_interval.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_item.h>

#include <qwt_compat.h>

#pragma GCC diagnostic pop

int main( int argc, char **argv )
{
  //using HistogramItem = QwtPlotItem;
  using HistogramItem = QwtPlotHistogram;
  //using QwtIntervalData = QwtSeriesData<QwtIntervalSample>;

  QApplication a(argc, argv);
  QwtPlot plot;
  plot.setCanvasBackground(QColor(Qt::white));
  plot.setTitle("Histogram");
  QwtPlotGrid *grid = new QwtPlotGrid;
  grid->enableXMin(true);
  grid->enableYMin(true);

  grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
  grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
  grid->attach(&plot);
  HistogramItem *histogram = new HistogramItem;
  //histogram->setColor(Qt::darkCyan);
  const int numValues = 20;
  //QwtArray<QwtDoubleInterval> intervals(numValues);
  QwtArray<QwtIntervalSample> intervals(numValues);
  QwtArray<double> values(numValues);
  double pos = 0.0;
  for ( int i = 0; i < (int)intervals.size(); i++ )
  {
    //const int width = 5 + rand() % 15;
    const int value = rand() % 100;
    //intervals[i] = QwtDoubleInterval(pos, pos + double(width));
    intervals[i] = QwtIntervalSample(value, pos, pos + double(width));
    //values[i] = value;
    pos += width;
  }

  //histogram->setData(QwtIntervalData(intervals, values));
  histogram->setSamples(intervals);
  //histogram->setSamples(QwtIntervalData(intervals, values));
  //QwtIntervalData d;
  //histogram->setData(d);
  histogram->attach(&plot);
  plot.setAxisScale(QwtPlot::yLeft, 0.0, 100.0);
  plot.setAxisScale(QwtPlot::xBottom, 0.0, pos);
  plot.replot();
  plot.resize(600,400);
  plot.show();
  return a.exec();
}
