#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
//#include <qprinter.h>
//#include <qprintdialog.h>
//#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
//#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
//#include <qwt_scale_draw.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
//#include <qwt_plot_renderer.h>
#include "myplot.h"
#include "myzoomer.h"
#include "mydata.h"
#include "mycolormap.h"
#pragma GCC diagnostic pop

MyPlot::MyPlot( QWidget *parent )
  : QwtPlot( parent ),
    m_spectrogram(new QwtPlotSpectrogram())
{
  m_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count

  m_spectrogram->setColorMap( new MyColorMap() );
  m_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

  m_spectrogram->setData( new MyData() );
  m_spectrogram->attach( this );

  QList<double> contourLevels;
  for ( double level = 0.5; level < 10.0; level += 1.0 )
      contourLevels += level;
  m_spectrogram->setContourLevels( contourLevels );

  const QwtInterval zInterval = m_spectrogram->data()->interval( Qt::ZAxis );
  // A color bar on the right axis
  QwtScaleWidget *rightAxis = axisWidget( QwtPlot::yRight );
  rightAxis->setTitle( "Intensity" );
  rightAxis->setColorBarEnabled( true );
  rightAxis->setColorMap( zInterval, new MyColorMap() );

  setAxisScale( QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue() );
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

void MyPlot::showContour( bool on )
{
  m_spectrogram->setDisplayMode(QwtPlotSpectrogram::ContourMode, on );
  replot();
}

void MyPlot::showSpectrogram( bool on )
{
  m_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, on );
  m_spectrogram->setDefaultContourPen(
      on ? QPen(Qt::black, 0) : QPen(Qt::NoPen) );

  replot();
}
