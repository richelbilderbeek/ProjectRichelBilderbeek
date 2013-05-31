#ifndef PVDBEDGE_H
#define PVDBEDGE_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

namespace pvdb {

struct EdgeFactory;

///An Edge is the GUI-independent part of the edges used in QtPvdbConceptMap.
///An Edge goes from one Node to another, which must a different Node
struct Edge : public boost::noncopyable
{
  ///Obtain an Edge from an XML std::string
  static const boost::shared_ptr<pvdb::Edge> FromXml(const std::string& s);

  const boost::shared_ptr<const pvdb::Concept>  GetConcept() const { return m_concept; }
  const boost::shared_ptr<      pvdb::Concept>  GetConcept()       { return m_concept; }

  ///Get the Node index this edge originates from
  int GetFrom() const { return m_from; }

  ///Get the Node index this edge goes to
  int GetTo() const { return m_to; }

  ///Get the x coordinat
  double GetX() const { return m_x; }

  ///Get the y coordinat
  double GetY() const { return m_y; }

  ///Does the edge have an arrow at the head?
  bool HasHeadArrow() const { return m_head_arrow; }

  //Similar to operator==, except that the coordinats are not checked
  static bool HasSameContent(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs);

  ///Does the edge have an arrow at the tail?
  bool HasTailArrow() const { return m_tail_arrow; }

  ///Get some testing edges
  static const std::vector<boost::shared_ptr<pvdb::Edge> > GetTests();

  void SetConcept(const boost::shared_ptr<pvdb::Concept> concept) { m_concept = concept; } //NEW 2013-01-07

  ///Set the Node index this edge originates from
  void SetFrom(const int from);

  ///Set if the head has an arrow
  void SetHeadArrow(const bool has_head_arrow);

  ///Set if the tail has an arrow
  void SetTailArrow(const bool has_tail_arrow);

  ///Set the Node index this edge goes to
  void SetTo(const int to);

  ///Convert an Edge from an XML std::string
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Edge>& c);

  ///Emitted when an Edge attribute has changed
  boost::signals2::signal<void (const Edge*)> m_signal_changed;

  private:

  ///The Concept on the Edge
  boost::shared_ptr<pvdb::Concept> m_concept;

  ///The Node index this edge originates from
  int m_from;

  ///Is there an arrowhead at the 'to' node?
  bool m_head_arrow;

  ///Is there an arrowhead at the 'from' node?
  bool m_tail_arrow;

  ///The Node index this edge goes to
  int m_to;

  ///The x-coordinat
  double m_x;

  ///The y-coordinat
  double m_y;

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif

  Edge() = delete;

  ///Block destructor, except for the friend boost::checked_delete
  ~Edge() {}
  friend void boost::checked_delete<>(Edge* x);

  ///Block constructor, except for EdgeFactory
  friend EdgeFactory;
  Edge(
    const boost::shared_ptr<pvdb::Concept> & concept,
    const double concept_x,
    const double concept_y,
    const int from,
    const bool tail_arrow,
    const int to,
    const bool head_arrow);

};

bool IsEqual(const pvdb::Edge& lhs, const pvdb::Edge& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs);
bool operator==(const pvdb::Edge& lhs, const pvdb::Edge& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs);
bool operator!=(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs);
bool operator!=(const pvdb::Edge& lhs, const pvdb::Edge& rhs) = delete;


} //~namespace pvdb


#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbedgefactory.h"
#endif

#endif // PVDBEDGE_H
