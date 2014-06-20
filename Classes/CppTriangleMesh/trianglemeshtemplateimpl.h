#ifndef TRIANGLEMESHTEMPLATEIMPL_H
#define TRIANGLEMESHTEMPLATEIMPL_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

class TemplateImpl
{
  friend class Template;
  TemplateImpl();

  private:
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHTEMPLATEIMPL_H
