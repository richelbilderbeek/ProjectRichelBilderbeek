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
struct Cluster
{
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
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Cluster>& c);

  private:

  ///A Cluster is a list of Concepts. The Concepts contain examples.
  std::vector<boost::shared_ptr<ribi::cmap::Concept> > m_v;

  ///Test this class
  static void Test();


  ///Block constructor, except for ClusterFactory
  friend ClusterFactory;
  Cluster(const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& v);

  ///Block destructor, except for the friend boost::checked_delete
  ~Cluster() {}
  friend void boost::checked_delete<>(Cluster* x);
};

bool IsEqual(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs);

} //~namespace pvdb
} //~namespace ribi


#endif // PVDBCLUSTER_H
