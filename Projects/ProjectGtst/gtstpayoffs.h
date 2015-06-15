
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

#ifndef PROJECTGTSTPAYOFFS_H
#define PROJECTGTSTPAYOFFS_H

#include <vector>

#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"

namespace ribi {
namespace gtst {

///Payoffs is a Facade to work with a collection of Payoff instances
struct Payoffs
{
  Payoffs();

  ///Add a new Payoff to the collection
  void Add(boost::shared_ptr<Payoff> payoff);

  ///Check if there are some instances of Payoff stored
  bool IsEmpty() const;

  ///Get the last obtained payoff
  const boost::shared_ptr<const Payoff> GetLast() const;

  ///Get the sum of the last n obtained payoffs
  double GetLast(const int n) const;

  ///Get the size of the collection of Payoff
  int GetSize() const;

  ///Sum the total payoff
  double GetTotal() const;

  private:
  ~Payoffs() {}
  friend void boost::checked_delete<>(Payoffs*);

  std::vector<boost::shared_ptr<Payoff> > m_v;
};

} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTPAYOFFS_H
