#ifndef PVDBCONCEPTMAP_H
#define PVDBCONCEPTMAP_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbcluster.h"
#include "pvdbconcept.h"
#include "pvdbedge.h"
#include "pvdbnode.h"
#endif

namespace pvdb {

struct ConceptMapFactory;

struct ConceptMap : public boost::noncopyable
{
  ///Test if this ConceptMap can be constructed successfully
  static bool CanConstruct(
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
    const std::vector<boost::shared_ptr<pvdb::Edge> >& edges);

  ///Create all sub-conceptmaps
  ///Note that CreateSubs()[0] is the concept map around the focal question
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > CreateSubs() const;


  ///Check if the ConceptMap is empty
  bool Empty() const;

  ///Get the edges
  const std::vector<boost::shared_ptr<const pvdb::Edge> >  GetEdges() const;
  const std::vector<boost::shared_ptr<      Edge> >& GetEdges() { return m_edges; }

  ///Get the nodes
  const std::vector<boost::shared_ptr<const pvdb::Node> >  GetNodes() const;
  const std::vector<boost::shared_ptr<      Node> >& GetNodes() { return m_nodes; }

  ///Get the focus question
  const std::string GetQuestion() const;

  ///Similar to operator==, except that the GUI member variables aren't checked for equality
  static bool HasSameContent(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs);
  static bool HasSameContent(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs);
  static bool HasSameContent(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs);
  static bool HasSameContent(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs);

  ///Convert a ConceptMap from an XML std::string
  static const std::string ToXml(const boost::shared_ptr<const pvdb::ConceptMap>& c);

private:

  ///The edges
  std::vector<boost::shared_ptr<pvdb::Edge> > m_edges;

  ///The nodes
  std::vector<boost::shared_ptr<pvdb::Node> > m_nodes;

  ///Prepend the question as a first node, before adding the supplied nodes
  static const std::vector<boost::shared_ptr<pvdb::Node> > CreateNodes(
    const std::string& question,
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes);

  ///Test this class
  static void Test();

  ///Block constructor, except for the friend ConceptMapFactory
  ConceptMap(const std::string& question);
  //Nodes[0] must be the focal question
  ConceptMap(
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
    const std::vector<boost::shared_ptr<pvdb::Edge> >& edges = {});
  ///Create a concept map from a cluster
  ConceptMap(
    const std::string& question,
    const boost::shared_ptr<pvdb::Cluster>& cluster);
  friend ConceptMapFactory;

  ///Block destructor, except for the friend boost::checked_delete
  ~ConceptMap() {}
  friend void boost::checked_delete<>(ConceptMap* x);
};

bool IsEqual(const pvdb::ConceptMap& lhs, const pvdb::ConceptMap& rhs);

/*
bool operator==(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs) = delete;
bool operator==(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs) = delete;
bool operator==(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs) = delete;
bool operator==(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs) = delete;
bool operator==(const pvdb::ConceptMap& lhs, const pvdb::ConceptMap& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs) = delete;
bool operator!=(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<const pvdb::ConceptMap>& rhs) = delete;
bool operator!=(const boost::shared_ptr<pvdb::ConceptMap>& lhs, const boost::shared_ptr<pvdb::ConceptMap>& rhs) = delete;
bool operator!=(const pvdb::ConceptMap& lhs, const pvdb::ConceptMap& rhs) = delete;
*/

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbconceptmapfactory.h"
#endif

#endif // PVDBCONCEPTMAP_H
