
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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTPAYOFF_H
#define PROJECTGTSTPAYOFF_H

#include <iosfwd>
#include <string>

#include <boost/checked_delete.hpp>
#include <boost/logic/tribool.hpp>


namespace ribi {
namespace gtst {

///Payoff is a class for the different types of payoff
struct Payoff
{
  Payoff(const int period, const double payoff);

  //Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules,
  //guidelines, and best practices. ISBN: 0-32-111358-6. Item 50: 'Make base
  //class destructors public and virtual, or protected and nonvirtual'.
  virtual ~Payoff() {}

  ///Convert the Payoff to an XML string
  virtual const std::string ToXml() const = 0;

  ///The payoff in points
  const double m_payoff;

  ///The period (larger cycle) number
  const int m_period;
};

struct PayoffAssign : public Payoff
{
  PayoffAssign(const int period, const double payoff);

  ///Convert the Payoff to an XML string
  const std::string ToXml() const;

  private:
  ~PayoffAssign() {}
  friend void boost::checked_delete<>(PayoffAssign*);
};

struct PayoffIpgg : public Payoff
{
  PayoffIpgg(
    const int period,
    const int ipgg_round,
    const double payoff,
    const bool did_contribute,
    const boost::logic::tribool& did_get_caught);

  ///Convert the Payoff to an XML string
  const std::string ToXml() const;

  ///The IPGG round this payoff was assigned in
  const int m_ipgg_round;

  ///Did the Participant contribute?
  const bool m_did_contribute;

  ///Did a non-contributing Participant get caught by the supervisor?
  ///- true: yes
  ///- no: no
  ///- indeterminate: Participant did contribute
  const boost::logic::tribool m_did_get_caught;

  private:
  ~PayoffIpgg() {}
  friend void boost::checked_delete<>(PayoffIpgg*);
};

struct PayoffReAssign : public Payoff
{
  PayoffReAssign(const int period, const double payoff);

  ///Convert the Payoff to an XML string
  const std::string ToXml() const;

  private:
  ~PayoffReAssign() {}
  friend void boost::checked_delete<>(PayoffReAssign*);
};

std::ostream& operator<<(std::ostream& os,const Payoff& p);

} //~namespace gtst
} //~namespace ribi

#endif // PAYOFF_H
