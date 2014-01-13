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

ribi::MultiCanvas::MultiCanvas(
  const std::vector<boost::shared_ptr<Canvas>>& canvases,
  const int maxx,
  const int maxy,
  const CanvasColorSystem color_system = CanvasColorSystem::normal,
  const CanvasCoordinatSystem coordinat_system = CanvasCoordinatSystem::screen
);

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

std::ostream& ribi::operator<<(std::ostream& os, const MultiCanvas& c)
{
  const auto text = c.ToStrings();
  std::copy(text.begin(),text.end(),
    std::ostream_iterator<std::string>(os,"\n")
  );
  return os;
}
