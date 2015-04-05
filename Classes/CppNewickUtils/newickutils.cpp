#include "newickutils.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>

const std::string NewickUtils::sm_newick_utils_path{"../../Libraries/newick_utils/src"};

NewickUtils::NewickUtils()
{
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  if (!IsRegularFileStl(executable))
  {
    std::stringstream s;
    s
      << "Error: nw_display executable '" << executable << "' not found\n"
      << "Please change the path\n"
    ;
    throw std::logic_error(s.str().c_str());
  }

}

void NewickUtils::Display(const std::string& newick)
{
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  assert(IsRegularFileStl(executable) && "Checked in constructor");
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" -"};
  std::system(cmd.c_str());
}

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool NewickUtils::IsRegularFileStl(
  const std::string& filename
) const noexcept
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
