#ifndef CODETOHTMLFOLDERTYPES_H
#define CODETOHTMLFOLDERTYPES_H

#include <string>
#include "codetohtmlfwd.h"

namespace ribi {
namespace c2h {


struct FolderTypes
{
  static FolderType DeduceFolderType(const std::string& folder_name);
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFOLDERTYPES_H
