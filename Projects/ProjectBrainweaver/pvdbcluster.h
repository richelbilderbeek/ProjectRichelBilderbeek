#ifndef PVDBCLUSTER_H
#define PVDBCLUSTER_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

namespace pvdb {

struct ClusterFactory;

///The data behind a QtPvdbClusterWidget
struct Cluster
{
  ///Add a Concept to the Cluster
  void Add(const boost::shared_ptr<pvdb::Concept>& concept);

  ///See if the cluster is empty
  bool Empty() const;

  ///Obtain a Cluster from an XML std::string
  static const boost::shared_ptr<pvdb::Cluster> FromXml(const std::string& s);

  ///Obtain the list of Concepts
  const std::vector<boost::shared_ptr<const pvdb::Concept> > Get() const;
  const std::vector<boost::shared_ptr<pvdb::Concept> >& Get() { return m_v; }

  ///Convert a Cluster from an XML std::string
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Cluster>& c);

  private:

  ///A Cluster is a list of Concepts. The Concepts contain examples.
  std::vector<boost::shared_ptr<pvdb::Concept> > m_v;

  ///Test this class
  static void Test();


  ///Block constructor, except for ClusterFactory
  friend ClusterFactory;
  Cluster(const std::vector<boost::shared_ptr<pvdb::Concept> >& v);

  ///Block destructor, except for the friend boost::checked_delete
  ~Cluster() {}
  friend void boost::checked_delete<>(Cluster* x);
};

bool IsEqual(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs);
/*
bool operator==(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs);
bool operator!=(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs);
bool operator!=(const boost::shared_ptr<const pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<const pvdb::Cluster>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Cluster>& lhs, const boost::shared_ptr<pvdb::Cluster>& rhs);
*/

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbclusterfactory.h"
#endif


#endif // PVDBCLUSTER_H
