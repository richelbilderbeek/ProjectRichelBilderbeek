#ifndef OPENFOAMBOUNDARYFILE_H
#define OPENFOAMBOUNDARYFILE_H

#include <iosfwd>
#include <string>
#include <vector>
#include "fileiofwd.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM boundary file
struct BoundaryFile
{
  struct BoundaryFileItem
  {
    BoundaryFileItem() : m_name{}, m_type{}, m_n_faces{}, m_start_face{} {}
    std::string m_name;
    std::string m_type;
    int m_n_faces;
    int m_start_face;
  };

  BoundaryFile(const fileio::Filename& filename)
    : BoundaryFile(Parse(filename)) {}
  private:
  BoundaryFile(const std::vector<BoundaryFileItem>& items);

  const std::vector<BoundaryFileItem> m_items;

  static const std::vector<BoundaryFileItem> Parse(const fileio::Filename& filename);
  static const std::vector<std::string> SplitLine(const std::string& line);

  friend std::ostream& operator<<(std::ostream& os, const BoundaryFile& f);
};

std::ostream& operator<<(std::ostream& os, const BoundaryFile& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMBOUNDARYFILE_H
