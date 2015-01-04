//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "regextesterqtmaindialog.h"

#include <stdexcept>

#include <QRegExp>

#include "trace.h"
#pragma GCC diagnostic pop

boost::shared_ptr<ribi::RegexTesterMainDialog> ribi::RegexTesterQtMainDialog::Clone() const noexcept
{
  boost::shared_ptr<RegexTesterMainDialog> d(
    new RegexTesterQtMainDialog);
  return d;
}

std::vector<std::string> ribi::RegexTesterQtMainDialog::GetRegexMatches(
  const std::string& s,
  const std::string& r) const
{
  if (!this->GetRegexValid(r)) return std::vector<std::string>();

  return GetRegexMatches(s,QRegExp(r.c_str()));
}

///Obtain all regex matches in a std::string
//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::RegexTesterQtMainDialog::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original)
{
  QRegExp r = r_original;
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
}

bool ribi::RegexTesterQtMainDialog::GetRegexMatchLine(
  const std::string& /* line */,
  const std::string& /* regex_str */) const noexcept
{
  assert(!"Qt does not have a regex match algorithm");
  //if (!GetRegexValid(regex_str)) return false;

  return false;
  //const QRegExp(regex_str);
  //return boost::regex_match(line,r);
}

std::string ribi::RegexTesterQtMainDialog::GetRegexReplace(
  const std::string& /* str */,
  const std::string& /* regex_str */,
  const std::string& /* format_str */) const
{
  return "Qt does not have a regex replace algorithm";
}


bool ribi::RegexTesterQtMainDialog::GetRegexValid(
  const std::string& /* regex_str */) const noexcept
{
  assert(!"TODO");
  //try { const boost::regex regex_temp(regex_str); }
  //catch (boost::regex_error& e) { return false; }
  //return true;
  throw std::runtime_error("TODO: ribi::RegexTesterQtMainDialog::GetRegexValid");
}
