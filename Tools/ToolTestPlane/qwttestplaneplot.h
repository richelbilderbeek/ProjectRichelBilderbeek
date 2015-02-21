#ifndef QWTTESTPLANEPLOT_H
#define QWTTESTPLANEPLOT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>

#include <qwt_plot.h>
#pragma GCC diagnostic pop



struct QwtLinearColorMap;
struct QwtPlotSpectrogram;

namespace ribi {

struct QwtTestPlaneData;
struct QwtTestPlaneZoomer;
struct Plane;

class QwtTestPlanePlot: public QwtPlot
{
    Q_OBJECT

public:
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  QwtTestPlanePlot(
    const boost::shared_ptr<Plane>& plane,
    const std::function<Coordinat3D(const double, const double)>& f,
    QWidget * parent = nullptr
  );
  QwtTestPlanePlot(const QwtTestPlanePlot&) = delete;
  QwtTestPlanePlot& operator=(const QwtTestPlanePlot&) = delete;

  void SetData(
    const boost::shared_ptr<Plane>& plane,
    const std::function<Coordinat3D(const double, const double)>& f,
    const double miny, const double maxy,
    const double minz, const double maxz
  );

public slots:


private:
  QwtPlotSpectrogram * const m_spectrogram;
  //boost::shared_ptr<QwtTestPlaneZoomer> m_zoomer;

  static QwtLinearColorMap * CreateColorMap() noexcept;

};

} //~namespace ribi

#endif // QWTTESTPLANEPLOT_H
