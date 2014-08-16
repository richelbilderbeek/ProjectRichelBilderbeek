#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <qwt_plot.h>
#pragma GCC diagnostic pop

struct QwtPlotSpectrogram;

class MyPlot: public QwtPlot
{
    Q_OBJECT

public:
  MyPlot(QWidget * parent = nullptr);
  MyPlot(const MyPlot&) = delete;
  MyPlot& operator=(const MyPlot&) = delete;

public Q_SLOTS:
  void showContour(bool on);
  void showSpectrogram(bool on);

private:
  QwtPlotSpectrogram * const m_spectrogram;
};
