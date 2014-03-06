
#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <QFile>
#include "fileio.h"
#include "chessresources.h"
#include "qtchessresources.h"
//#include "trace.h"
#pragma GCC diagnostic pop


ribi::Chess::QtResources::QtResources()
  : m_square_black{},
    m_square_white{}
{
  const std::vector<std::string> v = Resources::GetFilenames();
  std::for_each(v.begin(),v.end(),
    [](const std::string& s)
    {
      if (!fileio::IsRegularFile(s))
      {
        QFile f( (":/images/" + s).c_str() );
        f.copy(s.c_str());
        if (!fileio::IsRegularFile(s))
        {
          const std::string error = "File not found: " + s;
          std::cerr << error << '\n';
          std::clog << error << '\n';
          std::cout << error << '\n';
        }
      }
      assert(fileio::IsRegularFile(s));
    }
  );

  #ifndef NDEBUG
  this->Test();
  #endif
}

std::string ribi::Chess::QtResources::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::QtResources::GetVersionHistory()
{
  return {
    "2012-01-27: version 1.0: initial version"
  };
}
