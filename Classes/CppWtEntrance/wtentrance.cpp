//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestEntrance.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>

#include "ipaddress.h"
#include "wtentrance.h"

const std::string ribi::WtEntrance::m_filename_names  = "wtentrance_names.txt";
const std::string ribi::WtEntrance::m_filename_visits = "wtentrance_visits.txt";
ribi::WtEntrance * ribi::WtEntrance::m_instance = 0;

ribi::WtEntrance::WtEntrance()
{
  if (!boost::filesystem::exists(m_filename_names))
  {
    std::ofstream f(m_filename_names);
  }
  if (!boost::filesystem::exists(m_filename_visits))
  {
    std::ofstream f(m_filename_visits);
  }

  assert(boost::filesystem::exists(m_filename_names));
  assert(boost::filesystem::exists(m_filename_visits));
}

const std::vector<std::string> ribi::WtEntrance::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    if (!s.empty()) v.push_back(s);
  }
  return v;
}

ribi::WtEntrance * ribi::WtEntrance::Get()
{
  if (!m_instance) m_instance = new WtEntrance();
  assert(m_instance);
  return m_instance;
}

const std::string ribi::WtEntrance::GetDateIso8601()
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  const std::string s
    = boost::gregorian::to_iso_extended_string(today);
  assert(s.size()==10);
  assert(s[4]=='-');
  assert(s[7]=='-');
  return s;
}

const std::string ribi::WtEntrance::GetName(const IpAddress * const ip_address) const
{
  const std::vector<std::pair<std::string,std::string> > v = GetNames();
  const std::string ip_address_str = ip_address->Get();
  const auto i = std::find_if(v.begin(),v.end(),
    [ip_address_str](const std::pair<std::string,std::string>& p)
    {
      return p.first == ip_address_str;
    }
  );
  if (i == v.end()) return ip_address_str;
  return (*i).second;

}

const std::vector<std::pair<std::string,std::string> > ribi::WtEntrance::GetNames() const
{
  const std::vector<std::string> v = FileToVector(m_filename_names);
  std::vector<std::pair<std::string,std::string> > x;
  std::transform(v.begin(),v.end(),
    std::back_inserter(x),
    [this](const std::string& s)
    {
      const std::vector<std::string> w = this->SeperateString(s,',');
      if (w.size() != 2)
      {
        std::cerr << s << '\n';
      }
      assert(w.size() == 2);
      return std::make_pair(w[0],w[1]);
    }
  );

  return x;
}

const std::string ribi::WtEntrance::GetTime()
{
  //Get the local time
  boost::posix_time::ptime now
    = boost::posix_time::second_clock::local_time();
  //Convert the time to std::stringstream
  std::stringstream s;
  s << now.time_of_day();
  //Return the std::string
  return s.str();
}

const std::string ribi::WtEntrance::GetTimestamp()
{
  std::string s = GetDateIso8601() + '_' + GetTime();
  std::replace(s.begin(),s.end(),':','_');
  std::replace(s.begin(),s.end(),'-','_');
  return s;
}

const std::string ribi::WtEntrance::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::WtEntrance::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-19: version 1.0: initial version");
  return v;
}

const std::vector<std::pair<std::string,std::string> > ribi::WtEntrance::GetVisits() const
{
  const std::vector<std::string> v = FileToVector(m_filename_visits);
  std::vector<std::pair<std::string,std::string> > x;
  std::transform(v.begin(),v.end(),
    std::back_inserter(x),
    [this](const std::string& s)
    {
      const std::vector<std::string> w = this->SeperateString(s,',');
      assert(w.size() == 2);
      return std::make_pair(w[0],w[1]);
    }
  );

  return x;
}

const std::vector<std::string> ribi::WtEntrance::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::istringstream is(input);
  std::vector<std::string> v;
  for (
    std::string sub;
    std::getline(is, sub, seperator);
    v.push_back(sub))
  {
    //Empty for loop
  }
  return v;
}

void ribi::WtEntrance::SetName(const IpAddress * const ip_address, const std::string& name) const
{
  std::vector<std::pair<std::string,std::string> > v = GetNames();
  const std::string ip_address_str = ip_address->Get();
  const auto i = std::find_if(v.begin(),v.end(),
    [ip_address_str](const std::pair<std::string,std::string>& p)
    {
      return p.first == ip_address_str;
    }
  );
  if (i == v.end())
  {
    v.push_back(std::make_pair(ip_address_str,name));
  }
  else
  {
    (*i).second = name;
  }
  {
    std::ofstream f(m_filename_names);
    std::transform(v.begin(),v.end(),
      std::ostream_iterator<std::string>(f,"\n"),
      [&f](const std::pair<std::string,std::string>& p)
      {
        return p.first + "," + p.second;
      }
    );
  }
  m_signal_name_changed();
}

void ribi::WtEntrance::Visit(const IpAddress * const ip_address)
{
  std::ofstream f(m_filename_visits,std::ios::app);
  f << ip_address->Get() << ',' << this->GetTimestamp() << '\n';
  m_signal_new_visit();
}


