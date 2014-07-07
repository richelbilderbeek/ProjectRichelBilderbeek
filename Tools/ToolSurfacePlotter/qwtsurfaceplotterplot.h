#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <qwt_plot.h>
#pragma GCC diagnostic pop



struct QwtPlotSpectrogram;

namespace ribi {

class QwtSurfacePlotterPlot: public QwtPlot
{
    Q_OBJECT

public:
  QwtSurfacePlotterPlot(QWidget * parent = nullptr);
  QwtSurfacePlotterPlot(const QwtSurfacePlotterPlot&) = delete;
  QwtSurfacePlotterPlot& operator=(const QwtSurfacePlotterPlot&) = delete;

public Q_SLOTS:
  void showContour(bool on);
  void showSpectrogram(bool on);

private:
  QwtPlotSpectrogram * const m_spectrogram;
};

} //~namespace ribi
