#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "dotmatrixstring.h"

#include "dotmatrixchar.h"
#pragma GCC diagnostic pop

ribi::DotMatrixString::DotMatrixString(const std::string& s,
  const int spacing)
  : m_spacing(spacing),
    m_v{CreateDotMatrixChars(s)}
{
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
