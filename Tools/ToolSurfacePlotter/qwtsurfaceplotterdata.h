#ifndef MYDATA_H
#define MYDATA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qwt_matrix_raster_data.h"
#pragma GCC diagnostic pop

struct FunctionParser;

namespace ribi {

///The spectrogram data
struct MyData: public QwtRasterData
{
  MyData(
    const boost::shared_ptr<FunctionParser>& function_parser,
    //const std::string& function_str = "cos(x*y*100)",
    const double minx = -1.0, const double maxx = 1.0,
    const double miny = -1.0, const double maxy = 1.0,
    const double minz = -1.0, const double maxz = 1.0

  );

  //void SetFunctionParser(const boost::shared_ptr<FunctionParser>& function_parser);

  double value(const double x, const double y) const noexcept;

  private:
  const boost::shared_ptr<FunctionParser> m_function_parser;
};

} //~namespace ribi


#endif // MYDATA_H
