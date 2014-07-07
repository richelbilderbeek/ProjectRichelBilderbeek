#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include <qwt_plot.h>
#pragma GCC diagnostic pop



struct FunctionParser;
struct QwtPlotSpectrogram;

namespace ribi {

struct MyData;

class QwtSurfacePlotterPlot: public QwtPlot
{
    Q_OBJECT

public:
  QwtSurfacePlotterPlot(QWidget * parent = nullptr);
  QwtSurfacePlotterPlot(const QwtSurfacePlotterPlot&) = delete;
  QwtSurfacePlotterPlot& operator=(const QwtSurfacePlotterPlot&) = delete;

public slots:
  void SetData(
    const boost::shared_ptr<FunctionParser>& function_parser,
    const double minx, const double maxx,
    const double miny, const double maxy,
    const double minz, const double maxz
  );
  void SetData(
    const std::string& function_str,
    const double minx, const double maxx,
    const double miny, const double maxy,
    const double minz, const double maxz
  );
  void showContour(bool on);
  void showSpectrogram(bool on);

private:
  QwtPlotSpectrogram * const m_spectrogram;
};

} //~namespace ribi
