#ifndef RIBI_TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H
#define RIBI_TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H

#include <string>
#include <vector>

#include "trianglemeshcreateverticalfacesstrategy.h"

namespace ribi {
namespace trim {

struct CreateVerticalFacesStrategies
{
  //friend class Cell;
  //friend class CellFactory;
  //friend class CellsCreator;
  //friend class CellsCreatorFactory;
  //friend class Dialog;
  //friend class Face;
  //friend class FaceFactory;
  //friend class TriangleMeshBuilder;
  //friend class TriangleMeshBuilderImpl;

  CreateVerticalFacesStrategies() noexcept {}

  std::vector<CreateVerticalFacesStrategy> GetAll() const noexcept;

  int GetFacesPerCell(const CreateVerticalFacesStrategy s) const noexcept;

  std::string ToStr(const CreateVerticalFacesStrategy s) const noexcept;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHCREATEVERTICALFACESSTRATEGIES_H
