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
  const std::vector<boost::shared_ptr<Canvas>>& canvases
) : m_canvases(canvases)
{

}

int ribi::MultiCanvas::GetHeight() const noexcept
{
  if (m_canvases.empty()) return 0;
  int h = m_canvases[0]->GetHeight();
  for (auto c: m_canvases) { h = std::min(h,c->GetHeight()); }
  return h;
}

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

int ribi::MultiCanvas::GetWidth() const noexcept
{
  if (m_canvases.empty()) return 0;
  int w = m_canvases[0]->GetWidth();
  for (auto c: m_canvases) { w = std::min(w,c->GetWidth()); }
  return w;
}

const std::vector<std::string> ribi::MultiCanvas::ToStrings() const noexcept
{
  const int maxy = GetHeight();
  const int maxx = GetWidth();
  if (maxx == 0 || maxy == 0) { return std::vector<std::string>(); }
  const int n_layers = static_cast<int>(m_canvases.size());
  std::vector<std::vector<std::string>> v;
  for (auto c: m_canvases) { v.push_back(c->ToStrings()); }
  //Let the first canvas be drawn last, to give it the heighest Z order
  std::reverse(v.begin(),v.end());

  std::vector<std::string> w;
  for (int y=0; y!=maxy; ++y)
  {
    std::string to(maxx,' ');
    for (int layer=0; layer!=n_layers; ++layer)
    {
      assert(layer < static_cast<int>(v.size()));
      assert(y < static_cast<int>(v[layer].size()));
      const std::string from { v[layer][y] };
      for (int x=0; x!=maxx; ++x)
      {
        assert(x < static_cast<int>(from.size()));
        const char c { from[x] };
        if (c == ' ') continue;
        assert(x < static_cast<int>(to.size()));
        to[x] = c;
      }
    }
    w.push_back(to);
  }
  return w;
}

std::ostream& ribi::operator<<(std::ostream& os, const MultiCanvas& c)
{
  const auto text = c.ToStrings();
  std::copy(text.begin(),text.end(),
    std::ostream_iterator<std::string>(os,"\n")
  );
  return os;
}
