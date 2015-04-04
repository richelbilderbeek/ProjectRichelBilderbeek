#include <cassert>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFileStl(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

int main()
{
  const std::string executable{"../../Libraries/newick_utils/src/nw_display"};
  if (!IsRegularFileStl(executable))
  {
    std::cerr
      << "Error: nw_display executable '" << executable << "' not found\n"
      << "Please change the path\n"
    ;
    return 1;
  }
  const std::string newick{"((A:1,B:2),C:3);"};
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" -"};

  std::system(cmd.c_str());
}
