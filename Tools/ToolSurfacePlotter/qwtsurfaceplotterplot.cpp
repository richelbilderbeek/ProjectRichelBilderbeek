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

#include "fparser.hh"

#include "qwtsurfaceplotterplot.h"
#include "qwt_color_map.h"
#include "qwtsurfaceplotterzoomer.h"
#include "qwtsurfaceplotterdata.h"
#include "qwtsurfaceplottercolormap.h"
#pragma GCC diagnostic pop

ribi::QwtSurfacePlotterPlot::QwtSurfacePlotterPlot(QWidget *parent )
  : QwtPlot(parent),
    m_spectrogram(new QwtPlotSpectrogram)
{
  m_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count

  m_spectrogram->setColorMap(new QwtLinearColorMap(Qt::black,Qt::white));
  m_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

  {
    this->SetData(
      "cos(x*y*100)",
      -1.0,1.0,
      -1.0,1.0,
      -1.0,1.0
    );
  }


  m_spectrogram->attach(this);



  enableAxis( QwtPlot::yRight );

  plotLayout()->setAlignCanvasToScales( true );
  replot();

  // LeftButton for the zooming
  // MidButton for the panning
  // RightButton: zoom out by 1
  // Ctrl+RighButton: zoom out to full size

  QwtPlotZoomer* zoomer = new MyZoomer( canvas() );
  zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
      Qt::RightButton, Qt::ControlModifier );
  zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
      Qt::RightButton );

  QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
  panner->setAxisEnabled( QwtPlot::yRight, false );
  panner->setMouseButton( Qt::MidButton );

  // Avoid jumping when labels with more/less digits
  // appear/disappear when scrolling vertically

  const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
  QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
  sd->setMinimumExtent( fm.width( "100.00" ) );

  const QColor c( Qt::darkBlue );
  zoomer->setRubberBandPen( c );
  zoomer->setTrackerPen( c );
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

  //Set the contour levels
  {
    QList<double> contour_levels;
    for (double contour_level = minz; contour_level<maxz; contour_level+=((maxz-minz)/4.0))
    {
      contour_levels.append(contour_level);
    }
    m_spectrogram->setContourLevels(contour_levels );
  }

  assert(m_spectrogram->data());
  const QwtInterval zInterval = m_spectrogram->data()->interval(Qt::ZAxis );
  // A color bar on the right axis
  QwtScaleWidget * const rightAxis = axisWidget( QwtPlot::yRight );
  rightAxis->setColorBarEnabled(true);
  rightAxis->setColorMap(zInterval,new QwtLinearColorMap(Qt::black,Qt::white));
  setAxisScale( QwtPlot::yRight,minz,maxz);

  replot();
}

void ribi::QwtSurfacePlotterPlot::SetData(
  const boost::shared_ptr<FunctionParser>& function_parser,
  const double minx, const double maxx,
  const double miny, const double maxy,
  const double minz, const double maxz
  )
{
  MyData * const data
    = new MyData(
      function_parser,
      minx,maxx,
      miny,maxy,
      minz,maxz
    );
  assert(data);
  m_spectrogram->setData(data);
  replot();
}

void ribi::QwtSurfacePlotterPlot::showContour( bool on )
{
  m_spectrogram->setDisplayMode(QwtPlotSpectrogram::ContourMode, on );
  replot();
}

void ribi::QwtSurfacePlotterPlot::showSpectrogram( bool on )
{
  m_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, on );
  m_spectrogram->setDefaultContourPen(
      on ? QPen(Qt::black, 0) : QPen(Qt::NoPen) );

  replot();
}
