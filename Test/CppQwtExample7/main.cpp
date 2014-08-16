#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qslider.h>
#include "plot.h"
#pragma GCC diagnostic pop

class MainWindow: public QMainWindow
{
public:
    MainWindow(QWidget * parent = nullptr);
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

private:
    Plot *d_plot;
};

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    d_plot(new Plot(this))
{


    setCentralWidget( d_plot );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnSpectrogram = new QToolButton( toolBar );
    btnSpectrogram->setText( "Spectrogram" );
    btnSpectrogram->setCheckable( true );
    btnSpectrogram->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnSpectrogram );
    connect( btnSpectrogram, SIGNAL( toggled( bool ) ),
        d_plot, SLOT( showSpectrogram( bool ) ) );

    QToolButton *btnContour = new QToolButton( toolBar );
    btnContour->setText( "Contour" );
    btnContour->setCheckable( true );
    btnContour->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnContour );
    connect( btnContour, SIGNAL( toggled( bool ) ),
        d_plot, SLOT( showContour( bool ) ) );

#ifndef QT_NO_PRINTER
    QToolButton *btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL( clicked() ),
        d_plot, SLOT( printPlot() ) );
#endif

    QSlider *slider = new QSlider( Qt::Horizontal );
    slider->setRange( 0, 255 );
    slider->setValue( 255 );
    connect( slider, SIGNAL( valueChanged( int ) ),
        d_plot, SLOT( setAlpha( int ) ) );

    toolBar->addWidget( slider );

    addToolBar( toolBar );

    btnSpectrogram->setChecked( true );
    btnContour->setChecked( false );

}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow mainWindow;
    mainWindow.resize( 600, 400 );
    mainWindow.show();

    return a.exec();
}

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/math/constants/constants.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QApplication>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"
#include "qwt_plot_spectrogram.h"
#include "qwt_matrix_raster_data.h"

#ifdef _WIN32
#include "qwt_point_data.h"
#endif
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const auto curve = boost::make_shared<QwtPlotCurve>("Sine");
  const boost::shared_ptr<QwtPlotSpectrogram> plot = boost::make_shared<QwtPlotSpectrogram>();
  const double tau = boost::math::constants::two_pi<double>();


  QwtMatrixRasterData * const data = new QwtMatrixRasterData;

  const int n_rows = 10;
  for (int row = 0; row != n_rows; ++row)
  {
    const int n_cols = 10;
    for (int col = 0; col != n_cols; ++col)
    {
      const double x = tau * static_cast<double>(col) / static_cast<double>(n_cols);
      const double y = tau * static_cast<double>(row) / static_cast<double>(n_rows);
      const double z = std::sin(x) * cos(y);
      data->setValue(row,col,z);
    }
  }
  plot->setData(data);
  plot->setDisplayMode(QwtPlotSpectrogram::ImageMode);
  //plot->renderContourLines(QRectF(0.0,0.0,10.0,10.0),QSize(10,10));
  plot->show();
  return a.exec();
}


*/
