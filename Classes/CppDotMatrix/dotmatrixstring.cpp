#include "dotmatrixstring.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <QImage>

#include "dotmatrixchar.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::DotMatrixString::DotMatrixString(const std::string& s,
  const int spacing)
  : m_spacing(spacing),
    m_v{CreateDotMatrixChars(s)}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_spacing >= 0);
  assert(GetString() == s);
}

const std::vector<boost::shared_ptr<const ribi::DotMatrixChar> >
  ribi::DotMatrixString::CreateDotMatrixChars(const std::string& s)
{
  std::vector<boost::shared_ptr<const DotMatrixChar> > v;
  for (const char c: s)
  {
    boost::shared_ptr<const DotMatrixChar> p {
      new DotMatrixChar(c)
    };
    assert(p);
    v.push_back(p);
  }
  return v;
}

const boost::shared_ptr<QImage> ribi::DotMatrixString::CreateImage() const noexcept
{
  const int height = GetMatrixHeight();
  const int width  = GetMatrixWidth();
  const boost::shared_ptr<QImage> image {
    new QImage(width,height,QImage::Format_RGB32)
  };

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const bool b = GetMatrix(x,y);
      const QRgb color( b ? qRgb(0,0,0) : qRgb(255,255,255) );
      image->setPixel(x,y,color);
    }
  }
  return image;
}


const std::string ribi::DotMatrixString::GetString() const noexcept
{
  std::string s;
  for (const auto c: m_v) { s += c->GetChar(); }
  return s;
}

bool ribi::DotMatrixString::GetMatrix(const int x, const int y) const
{
  assert(x >= 0);
  assert(x < GetMatrixWidth());
  assert(y >= 0);
  if (!(y < GetMatrixHeight()))
  {
    TRACE("BREAK");
  }
  assert(y < GetMatrixHeight());
  assert(!m_v.empty());
  assert(m_v[0]);
  const int char_width = m_v[0]->GetMatrixWidth() + m_spacing;
  const int char_index = x / char_width;
  const int char_x     = x % char_width;
  assert(char_index < static_cast<int>(m_v.size()));
  assert(m_v[char_index]);
  const boost::shared_ptr<const DotMatrixChar> m = m_v[char_index];
  if ( char_x >= m->GetMatrixWidth()
    ||      y >= m->GetMatrixHeight())
  {
    //In spacing
    return false;
  }
  return m->GetMatrix(char_x,y);

}

int ribi::DotMatrixString::GetMatrixHeight() const noexcept
{
  if (m_v.empty()) return 0;
  return m_v[0]->GetMatrixHeight() + m_spacing;
}

int ribi::DotMatrixString::GetMatrixWidth() const noexcept
{
  if (m_v.empty()) return 0;
  const int n_chars = static_cast<int>(m_v.size());
  assert(m_v[0]);
  const int char_width = m_v[0]->GetMatrixWidth() + m_spacing;
  return n_chars * char_width;
}

const std::string ribi::DotMatrixString::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::DotMatrixString::GetVersionHistory() noexcept
{
  return {
    "201x-xx-xx: Version 1.0: initial version",
    "2014-02-27: Version 1.1: started versioning"
  };
}

#ifndef NDEBUG
void ribi::DotMatrixString::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::DotMatrixString::Test");
  const std::string text = "Hello world";
  const int spacing = 1;
  const boost::shared_ptr<const ribi::DotMatrixString> m {
    new ribi::DotMatrixString(text,spacing)
  };
  std::stringstream s;
  s << *m;
  assert(!s.str().empty());
  TRACE("Finished ribi::DotMatrixString::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const DotMatrixString& m)
{
  const int height  = m.GetMatrixHeight();
  const int width   = m.GetMatrixWidth();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      os << m.GetMatrix(x,y);
    }
    if (y + 1 != height) os << '\n';
  }
  return os;
}
