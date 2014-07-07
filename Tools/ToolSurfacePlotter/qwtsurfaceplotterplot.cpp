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

#include "fparser.hh"

#include "qwtsurfaceplotterplot.h"
#include "qwtsurfaceplotterzoomer.h"
#include "qwtsurfaceplotterdata.h"
#include "qwtsurfaceplottercolormap.h"
#pragma GCC diagnostic pop

ribi::QwtSurfacePlotterPlot::QwtSurfacePlotterPlot(QWidget *parent)
  : QwtPlot(parent),
    m_color_map(),
    m_data(),
    m_spectrogram(new QwtPlotSpectrogram),
    m_zoomer()
{
  m_spectrogram->setRenderThreadCount(0); // use system specific thread count
  m_spectrogram->setCachePolicy(QwtPlotRasterItem::PaintCache );

  {
    this->SetData(
      "cos(x*y*100)",
      -1.0,1.0,
      -1.0,1.0,
      -1.0,1.0
    );
  }

  m_spectrogram->attach(this);

  enableAxis(QwtPlot::yRight );

  plotLayout()->setAlignCanvasToScales(true);

  replot();

  // LeftButton for the zooming
  // MidButton for the panning
  // RightButton: zoom out by 1
  // Ctrl+RighButton: zoom out to full size
  {
    m_zoomer = boost::make_shared<QwtSurfacePlotterZoomer>(canvas());
    m_zoomer->setMousePattern( QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    m_zoomer->setMousePattern( QwtEventPattern::MouseSelect3,Qt::RightButton );
    const QColor c(Qt::white);
    m_zoomer->setRubberBandPen(c);
    m_zoomer->setTrackerPen(c);
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

void ribi::QwtSurfacePlotterPlot::SetData(
  const std::string& function_str,
  const double minx, const double maxx,
  const double miny, const double maxy,
  const double minz, const double maxz
)
{
  const auto f = boost::make_shared<FunctionParser>();
  f->Parse(function_str,"x,y");
  if (f->GetParseErrorType() != FunctionParser::FP_NO_ERROR)
  {
    std::stringstream s;
    s << "ribi::QwtSurfacePlotterPlot::SetData: Cannot parse " << function_str;
    throw std::logic_error(s.str().c_str());
  }
  SetData(
    f,
    minx,maxx,
    miny,maxy,
    minz,maxz
  );
}

void ribi::QwtSurfacePlotterPlot::SetData(
  const boost::shared_ptr<FunctionParser>& function_parser,
  const double minx, const double maxx,
  const double miny, const double maxy,
  const double minz, const double maxz
  )
{
  m_data
    = boost::make_shared<QwtSurfacePlotterData>(
      function_parser,
      minx,maxx,
      miny,maxy,
      minz,maxz
    );
  assert(m_data);
  m_spectrogram->setData(m_data.get());
  replot();

  //Set the contour levels and colors
  {
    QList<double> contour_levels;
    const double dz = (maxz-minz)/5.0;

    contour_levels.append(minz + (0.0 * dz));
    m_color_map = boost::make_shared<QwtLinearColorMap>(Qt::red,Qt::blue);

    contour_levels.append(minz + (1.0 * dz));
    m_color_map->addColorStop(0.2,Qt::yellow);

    contour_levels.append(minz + (2.0 * dz));
    m_color_map->addColorStop(0.4,Qt::green);

    contour_levels.append(minz + (3.0 * dz));
    m_color_map->addColorStop(0.6,Qt::cyan);

    contour_levels.append(minz + (4.0 * dz));
    m_color_map->addColorStop(0.8,Qt::blue);

    contour_levels.append(minz + (5.0 * dz));

    m_spectrogram->setContourLevels(contour_levels );


  }


  assert(m_spectrogram->data());
  const QwtInterval zInterval = m_spectrogram->data()->interval(Qt::ZAxis );
  // A color bar on the right axis
  QwtScaleWidget * const rightAxis = axisWidget( QwtPlot::yRight );
  rightAxis->setColorBarEnabled(true);

  rightAxis->setColorMap(zInterval,m_color_map.get());
  //rightAxis->setColorMap(zInterval,new QwtLinearColorMap(Qt::black,Qt::white));
  m_spectrogram->setColorMap(m_color_map.get());

  setAxisScale( QwtPlot::yRight,minz,maxz);
  rightAxis->repaint();

  replot();

}

void ribi::QwtSurfacePlotterPlot::showContour(const bool do_show)
{
  m_spectrogram->setDisplayMode(QwtPlotSpectrogram::ContourMode,do_show);
  replot();
}

void ribi::QwtSurfacePlotterPlot::showSpectrogram(const bool do_show)
{
  m_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode,do_show);
  m_spectrogram->setDefaultContourPen(
      do_show ? QPen(Qt::black, 0) : QPen(Qt::NoPen) );

  replot();
}
