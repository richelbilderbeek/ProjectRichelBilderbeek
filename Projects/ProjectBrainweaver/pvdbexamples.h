#ifndef PVDBEXAMPLES_H
#define PVDBEXAMPLES_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbexample.h"
#endif

namespace pvdb {

///Container of Example instances
struct Examples
{
  Examples(const std::vector<boost::shared_ptr<pvdb::Example> >& v);
  Examples(const Example& rhs) = delete;
  Examples& operator=(const Example& rhs) = delete;


  const std::vector<boost::shared_ptr<pvdb::Example> >& Get() { return m_v; }
  const std::vector<boost::shared_ptr<const pvdb::Example> > Get() const;

  static const boost::shared_ptr<pvdb::Examples> FromXml(const std::string& s);

  static const std::string ToXml(const boost::shared_ptr<const pvdb::Examples> &c);

  ///Something of one of the examples was changed
  mutable boost::signals2::signal<void(const Examples*)> m_signal_examples_changed;
private:
  ~Examples() {}

  std::vector<boost::shared_ptr<pvdb::Example> > m_v;

  void Add(const boost::shared_ptr<pvdb::Example>& example); //?not used

  ///All signals emitted from the examples are connected to this member function
  void OnExampleChanged();

  ///Test this class
  static void Test();

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(Examples* x);
};


bool IsEqual(const pvdb::Examples& lhs, const pvdb::Examples& rhs);

///Two pvdb::Examples instances are sorted as follows:
///(1) By their number of examples
///(2) (if the sizes are equal) Alphabetically on the first different example
bool operator<(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs);
bool operator<(const boost::shared_ptr<const pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs);
bool operator<=(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<const pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator<=(const boost::shared_ptr<pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<const pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>(const boost::shared_ptr<pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<const pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<pvdb::Examples>& lhs, const boost::shared_ptr<const pvdb::Examples>& rhs) = delete;
bool operator>=(const boost::shared_ptr<pvdb::Examples>& lhs, boost::shared_ptr<const pvdb::Examples>& rhs) = delete;

} //~namespace pvdb

#endif // PVDBEXAMPLES_H
