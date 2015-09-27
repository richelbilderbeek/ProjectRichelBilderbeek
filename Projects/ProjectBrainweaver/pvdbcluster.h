//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef PVDBCLUSTER_H
#define PVDBCLUSTER_H

#include <map>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct ClusterFactory;

///The data behind a QtPvdbClusterWidget
class Cluster
{
  public:

  ///Add a Concept to the Cluster
  void Add(const boost::shared_ptr<ribi::cmap::Concept>& concept);

  ///See if the cluster is empty
  bool Empty() const;

  ///Obtain a Cluster from an XML std::string
  static const boost::shared_ptr<pvdb::Cluster> FromXml(const std::string& s);

  ///Obtain the list of Concepts
  const std::vector<boost::shared_ptr<const ribi::cmap::Concept> > Get() const;
  const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& Get() { return m_v; }

  ///Set the concepts
  void SetConcepts(const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& concepts);

  ///Convert a Cluster from an XML std::string
  static std::string ToXml(const boost::shared_ptr<const pvdb::Cluster>& c) noexcept;

  private:

  ///A Cluster is a list of Concepts. The Concepts contain examples.
  std::vector<boost::shared_ptr<ribi::cmap::Concept> > m_v;

  ///Test this class
  static void Test() noexcept;


  ///Block constructor, except for ClusterFactory
  friend ClusterFactory;
  Cluster(const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& v);

  ///Block destructor, except for the friend boost::checked_delete
  ~Cluster() {}
  friend void boost::checked_delete<>(Cluster* x);
};

bool operator==(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs);

} //~namespace pvdb
} //~namespace ribi


#endif // PVDBCLUSTER_H
