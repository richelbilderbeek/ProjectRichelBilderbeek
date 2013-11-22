#include "codetohtmlfoldertypes.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>

#include "fileio.h"
#include "trace.h"
#include "codetohtmlfoldertype.h"
#pragma GCC diagnostic pop

ribi::c2h::FolderType ribi::c2h::FolderTypes::DeduceFolderType(const std::string& folder_name)
{
  assert(fileio::IsFolder(folder_name));

  const std::vector<std::string> files {
    fileio::GetFilesInFolder(folder_name)
  };

  //Search for pro files
  {
    //Copy all filenames matching the regex in the resulting std::vector
    const int n_pro_files {
      std::count_if(files.begin(),files.end(),
        [](const std::string& s)
        {
          static const boost::xpressive::sregex pro_file_regex {
            boost::xpressive::sregex::compile(".*\\.(pro)\\>")
          };
          boost::xpressive::smatch what;
          return boost::xpressive::regex_match(s, what, pro_file_regex);
        }
      )
    };
    if (n_pro_files > 0) return FolderType::pro;
  }

  //Search for foam files
  {
    //Copy all filenames matching the regex in the resulting std::vector
    const int n_foam_files {
      std::count_if(files.begin(),files.end(),
        [](const std::string& s)
        {
          static const boost::xpressive::sregex foam_file_regex {
            boost::xpressive::sregex::compile(".*\\.(foam)\\>")
          };
          boost::xpressive::smatch what;
          return boost::xpressive::regex_match(s, what, foam_file_regex);
        }
      )
    };
    if (n_foam_files > 0) return FolderType::foam;
  }
  return FolderType::txt;
}
