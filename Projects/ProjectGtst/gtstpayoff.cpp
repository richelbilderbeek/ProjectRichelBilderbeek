//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
#include <sstream>

#include "gtstpayoff.h"
//#include "trace.h"

ribi::gtst::Payoff::Payoff(const int period, const double payoff)
  : m_payoff(payoff), m_period(period)
{
  assert(m_period >= 0);
}

ribi::gtst::PayoffAssign::PayoffAssign(const int period, const double payoff)
  : Payoff(period,payoff)
{

}

const std::string ribi::gtst::PayoffAssign::ToXml() const
{
  std::stringstream s;
  s
    << "<payoff_assign>"
      << "<period>"
        << this->m_period
      << "</period>"
      << "<payoff>"
        << this->m_payoff
      << "</payoff>"
    << "</payoff_assign>";
  return s.str();
}

ribi::gtst::PayoffIpgg::PayoffIpgg(
    const int period,
    const int ipgg_round,
    const double payoff,
    const bool did_contribute,
    const boost::logic::tribool& did_get_caught)
  : Payoff(period,payoff),
    m_ipgg_round(ipgg_round),
    m_did_contribute(did_contribute),
    m_did_get_caught(did_get_caught)
{
  assert(m_ipgg_round >= 0);
}

const std::string ribi::gtst::PayoffIpgg::ToXml() const
{
  std::stringstream s;
  s
    << "<payoff_ipgg>"
      << "<period>"
        << this->m_period
      << "</period>"
      << "<ipgg_round>"
        << this->m_ipgg_round
      << "</ipgg_round>"
      << "<payoff>"
        << this->m_payoff
      << "</payoff>"
      << "<did_contribute>"
        << this->m_did_contribute
      << "</did_contribute>"
      << "<did_get_caught>"
        << this->m_did_get_caught
      << "</did_get_caught>"
    << "</payoff_ipgg>";
  return s.str();
}

ribi::gtst::PayoffReAssign::PayoffReAssign(const int period, const double payoff)
  : Payoff(period,payoff)
{

}

const std::string ribi::gtst::PayoffReAssign::ToXml() const
{
  std::stringstream s;
  s
    << "<payoff_reassign>"
      << "<period>"
        << this->m_period
      << "</period>"
      << "<payoff>"
        << this->m_payoff
      << "</payoff>"
    << "</payoff_reassign>";
  return s.str();
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const Payoff& p)
{
  os << p.ToXml();
  return os;
}

