#include "dotmatrixtext.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "dotmatrixstring.h"

#include <cassert>

#include <QImage>

#include "dotmatrixchar.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::DotMatrixText::DotMatrixText(
  const std::vector<std::string>& s,
  const int spacing,
  const ColorSystem color_system
)
  : m_color_system(color_system),
    m_spacing(spacing),
    m_v{CreateDotMatrixText(s,spacing)}
{
  assert(m_spacing >= 0);
  assert(GetText() == s);
}

const std::vector<boost::shared_ptr<const ribi::DotMatrixString>>
  ribi::DotMatrixText::CreateDotMatrixText(
    const std::vector<std::string>& text,
    const int spacing
  )
{
  std::vector<boost::shared_ptr<const DotMatrixString>> v;
  for (const std::string line: text)
  {
    boost::shared_ptr<const DotMatrixString> s {
      new DotMatrixString(line,spacing)
    };
    assert(s);
    v.push_back(s);
  }
  return v;
}

const boost::shared_ptr<QImage> ribi::DotMatrixText::CreateImage() const noexcept
{
  const int total_height = GetMatrixHeight();
  const int line_height  = m_v[0]->GetMatrixHeight() + m_spacing;
  const int total_width  = GetMatrixWidth();
  const boost::shared_ptr<QImage> image {
    new QImage(total_width,total_height,QImage::Format_RGB32)
  };
  int offset = 0;
  for (const auto v: m_v)
  {
    const int height = line_height;
    const int width  = total_width;
    for (int y=0; y!=height; ++y)
    {
      for (int x=0; x!=width; ++x)
      {
        const bool matrix_color
          = y < v->GetMatrixHeight()
          && x < v->GetMatrixWidth()
          && v->GetMatrix(x,y);
        const bool final_color {
            m_color_system == ColorSystem::normal
          ?  matrix_color
          : !matrix_color
        };
        const QRgb color( final_color ? qRgb(0,0,0) : qRgb(255,255,255) );
        image->setPixel(x,offset + y,color);
      }
    }

    offset += height;
  }
  return image;
}

const std::vector<std::string> ribi::DotMatrixText::GetText() const noexcept
{
  std::vector<std::string> s;
  for (const auto c: m_v) { s.push_back(c->GetString()); }
  return s;
}

bool ribi::DotMatrixText::GetMatrix(const int x, const int y) const
{
  assert(x >= 0);
  assert(x < GetMatrixWidth());
  assert(y >= 0);
  assert(y < GetMatrixHeight());
  assert(!m_v.empty());
  assert(m_v[0]);
  const int char_width  = m_v[0]->GetMatrixWidth()  + m_spacing;
  const int char_height = m_v[0]->GetMatrixHeight() + m_spacing;
  const int line_index = y / char_height;
  const int char_x     = x % char_width;
  const int char_y     = y % char_height;
  assert(line_index < static_cast<int>(m_v.size()));
  assert(m_v[line_index]);
  if (char_y >= m_v[line_index]->GetMatrixHeight()) return false;
  return m_v[line_index]->GetMatrix(char_x,char_y);
}

int ribi::DotMatrixText::GetMatrixHeight() const noexcept
{
  if (m_v.empty()) return 0;
  return (m_v[0]->GetMatrixHeight() + m_spacing) * static_cast<int>(m_v.size());
}

int ribi::DotMatrixText::GetMatrixWidth() const noexcept
{
  if (m_v.empty()) return 0;
  return (*std::max_element(m_v.begin(),m_v.end(),
    [](const boost::shared_ptr<const DotMatrixString>& lhs, const boost::shared_ptr<const DotMatrixString>& rhs)
    {
      assert(lhs);
      assert(rhs);
      return lhs->GetMatrixWidth() < rhs->GetMatrixWidth();
    }
  ))->GetMatrixWidth();
}

#ifndef NDEBUG
void ribi::DotMatrixText::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::DotMatrixText::Test");
  TRACE("Finished ribi::DotMatrixText::Test successfully");
}
#endif


std::ostream& ribi::operator<<(std::ostream& os, const DotMatrixText& m)
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
