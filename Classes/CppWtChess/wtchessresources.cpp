//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
#include <QFile>
//---------------------------------------------------------------------------
#include "chessresources.h"
#include "wtchessresources.h"
//---------------------------------------------------------------------------
namespace Chess {
//---------------------------------------------------------------------------
WtResources::WtResources()
{
  const std::vector<std::string> v = Resources::GetFilenames();
  std::for_each(v.begin(),v.end(),
    [](const std::string& s)
    {
      if (!boost::filesystem::exists(s))
      {
        QFile f( (std::string(":/images/") + s).c_str() );
        f.copy(s.c_str());
        if (!boost::filesystem::exists(s.c_str()))
        {
          const std::string error = "File not found: " + s;
          std::cerr << error << '\n';
          std::clog << error << '\n';
          std::cout << error << '\n';
        }
      }
      assert(boost::filesystem::exists(s.c_str()));
    }
  );
}
//---------------------------------------------------------------------------
const std::string WtResources::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtResources::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-01-27: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
} //~ namespace Chess
//---------------------------------------------------------------------------
