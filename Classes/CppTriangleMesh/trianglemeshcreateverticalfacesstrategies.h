#ifndef TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H
#define TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H

#include <string>
#include <vector>

#include "trianglemeshcreateverticalfacesstrategy.h"

namespace ribi {
namespace trim {

struct CreateVerticalFacesStrategies
{
  CreateVerticalFacesStrategies() noexcept {}

  std::vector<CreateVerticalFacesStrategy> GetAll() const noexcept;

  int GetFacesPerCell(const CreateVerticalFacesStrategy s) const noexcept;

  std::string ToStr(const CreateVerticalFacesStrategy s) const noexcept;
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H
