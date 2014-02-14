#include "trianglemeshfacefactory.h"

#include <cassert>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trianglemeshface.h"
#include "trace.h"

const boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::Create(
  const std::vector<boost::shared_ptr<Point>>& points,
  const FaceOrientation any_orientation,
  const boost::weak_ptr<const Face> face_below
)
{
  #ifndef NDEBUG
  Test();
  #endif
  PROFILE_FUNC();
  const boost::shared_ptr<Face> face(
    new Face(
      points,
      any_orientation,
      face_below
    )
  );
  assert(face);
  for (auto point: face->GetPoints())
  {
    assert(point);
    point->AddConnected(face);
  }

  return face;
}

#ifndef NDEBUG
void ribi::trim::FaceFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::FaceFactory::Test");
  TRACE("Finished ribi::trim::FaceFactory::Test successfully");
}
#endif
