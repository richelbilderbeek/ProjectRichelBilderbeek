#ifndef PVDBHINTS_H
#define PVDBHINTS_H

/*
 *
#include <map>
#include <string>

#include <boost/checked_delete.hpp>

namespace pvdb {

enum class Hint
{
  create_concept,
  edit_concept,
  edit_arrow
};

///Manages all Pvdb hints
struct Hints
{
  Hints();

  ///Get a hint its text
  const std::string& GetText(const pvdb::Hint hint) const;

  ///Has the user followed the hint already?
  bool IsDone(const pvdb::Hint hint) const;

  ///The user followed the hint
  void SetDone(const pvdb::Hint hint);

  private:
  ///Block destructor, except for the friend boost::checked_delete
  ~Hints() {}

  ///All hints and if these are done
  std::map<Hint,std::pair<bool,std::string> > m_m;

  ///Create all hints their texts
  static const std::map<Hint,std::pair<bool,std::string> > CreateMap();

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(Hints* x);

  ///Test this class
  static void Test();
};

} //~namespace pvdb

*/

#endif // PVDBHINTS_H
