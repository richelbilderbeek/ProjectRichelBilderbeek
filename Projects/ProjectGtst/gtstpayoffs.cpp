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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>

#include "gtstpayoff.h"
#include "gtstpayoffs.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::gtst::Payoffs::Payoffs()
  : m_v{}
{

}

void ribi::gtst::Payoffs::Add(boost::shared_ptr<Payoff> payoff)
{
  assert(payoff);
  m_v.push_back(payoff);
}

int ribi::gtst::Payoffs::GetSize() const
{
  return boost::numeric_cast<int>(m_v.size());
}

bool ribi::gtst::Payoffs::IsEmpty() const
{
  return m_v.empty();
}

const boost::shared_ptr<const ribi::gtst::Payoff> ribi::gtst::Payoffs::GetLast() const
{
  assert(!m_v.empty());
  return m_v.back();
}

///Get the sum of the last n obtained payoffs
double ribi::gtst::Payoffs::GetLast(const int n) const
{
  #define DEBUG_TEMP_732487276655432842
  #ifdef  DEBUG_TEMP_732487276655432842
  if (n > boost::numeric_cast<int>(m_v.size()))
  {
    TRACE(n);
    TRACE(m_v.size());
  }
  #endif

  assert(n <= boost::numeric_cast<int>(m_v.size()));
  return std::accumulate(
    m_v.end() - n, m_v.end(),
    0.0,
    [](double& sum, const boost::shared_ptr<Payoff> p)
    {
      return sum + p->m_payoff;
    }
  );
}

double ribi::gtst::Payoffs::GetTotal() const
{
  return std::accumulate(
    m_v.begin(),m_v.end(),0.0,
    [](double& sum,const boost::shared_ptr<Payoff>& payoff)
    {
      return sum + payoff->m_payoff;
    }
  );
}

