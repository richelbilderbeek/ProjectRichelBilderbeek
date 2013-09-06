#ifndef PVDBNODE_H
#define PVDBNODE_H

#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

struct NodeFactory;

///A Node is the GUI independent part as used in QtPvdbConceptMapItem
struct Node : public boost::noncopyable
{

  ///Obtain a Node from an XML std::string
  static const boost::shared_ptr<ribi::pvdb::Node> FromXml(const std::string& s);

  ///Get the Concept
  const boost::shared_ptr<const ribi::pvdb::Concept>  GetConcept() const { return m_concept; }
  const boost::shared_ptr<      ribi::pvdb::Concept>& GetConcept() { return m_concept; }

  #ifndef NDEBUG
  ///Get boost::shared_ptr::use_count
  int GetConceptUseCount() const { return m_concept.use_count(); }
  #endif

  ///Get some test nodes
  static const std::vector<boost::shared_ptr<ribi::pvdb::Node> > GetTests();

  ///Similar to operator==, except that GUI elements are not tested for equality
  static bool HasSameContent(const boost::shared_ptr<const pvdb::Node>& lhs, const boost::shared_ptr<const pvdb::Node>& rhs);

  ///Get the x coordinat
  double GetX() const { return m_x; }

  ///Get the y coordinat
  double GetY() const { return m_y; }

  ///Set the concept
  void SetConcept(const boost::shared_ptr<ribi::pvdb::Concept> concept);

  ///Set the position
  void SetPos(const double x, const double y) { SetX(x); SetY(y); }

  ///Set the x coordinat
  void SetX(const double x);

  ///Set the y coordinat
  void SetY(const double y);

  ///Convert a Node from an XML std::string
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Node>& c);

  boost::signals2::signal<void(const pvdb::Node *)> m_signal_node_changed;

  protected:
  ///Block construction, except for NodeFactory and derived classes
  Node() = delete;
  friend NodeFactory;

  explicit Node(
    const boost::shared_ptr<ribi::pvdb::Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  ///Block destructor, except for the friend boost::checked_delete
  virtual ~Node() {}
  friend void boost::checked_delete<>(Node* x);

  private:

  ///The Concept
  boost::shared_ptr<ribi::pvdb::Concept> m_concept;

  ///The x-coordinat
  double m_x;

  ///The y-coordinat
  double m_y;

  ///Test this class
  static void Test();

};

bool IsEqual(const pvdb::Node& lhs, const pvdb::Node& rhs);

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBNODE_H
