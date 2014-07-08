#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include <boost/make_shared.hpp>

#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_color_map.h>


#include "plane.h"
#include "qwttestplaneplot.h"
#include "qwttestplanezoomer.h"
#include "qwttestplanedata.h"
#pragma GCC diagnostic pop

ribi::QwtTestPlanePlot::QwtTestPlanePlot(
  const boost::shared_ptr<Plane>& plane,
  const std::function<Coordinat3D(const double, const double)>& f,
  QWidget *parent
) : QwtPlot(parent),
    m_spectrogram(new QwtPlotSpectrogram)
{
  //'0' Enables multithreaded rendering, use '1' for singethreaded
  //Note that the program crashes when using multithreading/'0'
  m_spectrogram->setRenderThreadCount(1);
  m_spectrogram->setCachePolicy(QwtPlotRasterItem::PaintCache);

  m_spectrogram->setDisplayMode(QwtPlotSpectrogram::ContourMode,true);
  m_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode,true);
  m_spectrogram->setDefaultContourPen(QPen(Qt::black, 0));

  {
    this->SetData(
      plane,
      f,
      -1.0,1.0,
      -1.0,1.0
    );
  }

  m_spectrogram->attach(this);

  enableAxis(QwtPlot::yRight );

  plotLayout()->setAlignCanvasToScales(true);

  //replot();

  // LeftButton for the zooming
  // MidButton for the panning
  // RightButton: zoom out by 1
  // Ctrl+RighButton: zoom out to full size
  {
    QwtTestPlaneZoomer * const zoomer = new QwtTestPlaneZoomer(canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);
    const QColor c(Qt::white);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
  }

  QwtPlotPanner *panner = new QwtPlotPanner(canvas());
  panner->setAxisEnabled(QwtPlot::yRight, false);
  panner->setMouseButton(Qt::MidButton);

  // Avoid jumping when labels with more/less digits
  // appear/disappear when scrolling vertically

  const QFontMetrics fm(axisWidget(QwtPlot::yLeft)->font());
  QwtScaleDraw *sd = axisScaleDraw(QwtPlot::yLeft);
  sd->setMinimumExtent( fm.width("100.00") );


}

QwtLinearColorMap * ribi::QwtTestPlanePlot::CreateColorMap() noexcept
{
  QwtLinearColorMap * const color_map = new QwtLinearColorMap(Qt::red,Qt::magenta);
  color_map->addColorStop(0.0001,Qt::yellow);
  color_map->addColorStop(0.0010,Qt::green);
  color_map->addColorStop(0.0100,Qt::cyan);
  color_map->addColorStop(0.1000,Qt::blue);
  return color_map;
}

void ribi::QwtTestPlanePlot::SetData(
  const boost::shared_ptr<Plane>& plane,
  const std::function<Coordinat3D(const double, const double)>& f,
  const double minx, const double maxx,
  const double miny, const double maxy
  )
{
  //m_spectrogram will delete data
  QwtTestPlaneData * const data = new QwtTestPlaneData(
    plane,
    f,
    minx,maxx,
    miny,maxy
  );
  assert(data);
  m_spectrogram->setData(data);

  {
    QList<double> contour_levels = { 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001 };
    m_spectrogram->setContourLevels(contour_levels );
  }


  assert(m_spectrogram->data());
  const QwtInterval zInterval(0.0,1.0);
  // A color bar on the right axis
  QwtScaleWidget * const rightAxis = axisWidget(QwtPlot::yRight );
  rightAxis->setColorBarEnabled(true);

  rightAxis->setColorMap(zInterval,CreateColorMap());
  m_spectrogram->setColorMap(CreateColorMap());

  setAxisScale(QwtPlot::yRight,0.0,1.0); //Yes or no in plane
  rightAxis->repaint();

  replot();

}
