#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "multicanvas.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>

#include <boost/math/constants/constants.hpp>
#include <boost/algorithm/string/split.hpp>

#include <QString>
#include <QRegExp>

#include "canvascolorsystems.h"
#include "canvascoordinatsystems.h"
//#include "dotmatrixstring.h"
#include "fileio.h"
#include "trace.h"
//#include "xml.h"

#pragma GCC diagnostic pop

const std::string ribi::MultiCanvas::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::MultiCanvas::GetVersionHistory() noexcept
{
  return {
    "2014-01-13: version 1.0: initial version"
  };
}
