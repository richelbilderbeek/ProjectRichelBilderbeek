#include "trianglemeshcreateverticalfacesstrategies.h"

#include <cassert>
#include <stdexcept>

std::vector<ribi::trim::CreateVerticalFacesStrategy> ribi::trim::CreateVerticalFacesStrategies::GetAll() const noexcept
{
  return {
    CreateVerticalFacesStrategy::one_face_per_square,
    CreateVerticalFacesStrategy::two_faces_per_square
  };
}

int ribi::trim::CreateVerticalFacesStrategies::GetFacesPerCell(const CreateVerticalFacesStrategy s) const noexcept
{
  switch (s)
  {
    case CreateVerticalFacesStrategy::one_face_per_square: return 5;
    case CreateVerticalFacesStrategy::two_faces_per_square: return 8;
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::trim::CreateVerticalFacesStrategies::ToStr: unknown strategy");
  };
  assert(!"Should not get here");
  throw std::logic_error("ribi::trim::CreateVerticalFacesStrategies::ToStr: unknown strategy");
}


std::string ribi::trim::CreateVerticalFacesStrategies::ToStr(const CreateVerticalFacesStrategy s) const noexcept
{
  switch (s)
  {
    case CreateVerticalFacesStrategy::one_face_per_square: return "one_face_per_square";
    case CreateVerticalFacesStrategy::two_faces_per_square: return "two_faces_per_square";
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::trim::CreateVerticalFacesStrategies::ToStr: unknown strategy");
  };
  assert(!"Should not get here");
  throw std::logic_error("ribi::trim::CreateVerticalFacesStrategies::ToStr: unknown strategy");
}
