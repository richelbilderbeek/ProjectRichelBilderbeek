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
#include "gtstadministrator.h"
#include "gtstadministrators.h"
#include "counter.h"

ribi::gtst::Administrators::Administrators()
  : m_administrators{},
    m_last_id_administrator(new Counter(1))
{
}

boost::weak_ptr<ribi::gtst::Administrator> ribi::gtst::Administrators::CreateNewAdministrator()
{
  #ifndef NDEBUG
  const int n_administrators_old = m_administrators.size();
  std::for_each(m_administrators.begin(),m_administrators.end(),
    [](const boost::shared_ptr<Administrator>& p)
    {
      assert(p && "Assume all Administrators are valid");
    } );
  #endif

  const int new_id = m_last_id_administrator->Get();
  assert(new_id > 0);

  #ifndef NDEBUG
  std::for_each(m_administrators.begin(),m_administrators.end(),
    [new_id](const boost::shared_ptr<Administrator>& p)
    {
      assert(p->GetId() != new_id && "Assume new ID is really a unique ID");
    } );
  #endif

  boost::shared_ptr<Administrator> new_administrator(
    new Administrator(new_id));
  assert(new_administrator);

  //Keep one copy of the administrator
  m_administrators.insert(new_administrator);

  #ifndef NDEBUG
  const int n_administrators_new = m_administrators.size();
  assert(n_administrators_new == n_administrators_old + 1
    && "Assume the new administrator has really been added to m_administrators");
  #endif

  return new_administrator;
}

