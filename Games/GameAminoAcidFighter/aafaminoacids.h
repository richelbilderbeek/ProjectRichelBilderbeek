#ifndef AAFAMINOACIDS_H
#define AAFAMINOACIDS_H

#include <string>
#include <vector>

#include "aafaminoacid.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace aaf {

struct AminoAcids
{
  static std::vector<AminoAcid> GetAll() noexcept;
  static std::string ToStr(const AminoAcid s) noexcept;
  static AminoAcid ToType(const std::string& s);

  private:
  static boost::bimap<AminoAcid,std::string> m_map;
  static boost::bimap<AminoAcid,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace aaf
} //~namespace ribi

#endif // AAFAMINOACIDS_H
