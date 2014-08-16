#include "openfoamparseerror.h"

#include <sstream>

ribi::foam::ParseError::ParseError(
  const std::string& filename,
  const int line)
: std::runtime_error(CreateErrorMsg(filename,line).c_str()),
  m_filename(filename),
  m_line(line)
{

}

std::string ribi::foam::ParseError::CreateErrorMsg(
  const std::string& filename,
  const int line) noexcept
{
  std::stringstream s;
  s << "OpenFOAM file parsing error in ";
  if (filename.empty())
  {
    s << "unknown file";
  }
  else
  {
    s << "file '" << filename << "'";
  }
  s << " in ";
  if (line < 0)
  {
    s << "unknown line";
  }
  else
  {
    s << "line " << line;
  }
  return s.str();
}
