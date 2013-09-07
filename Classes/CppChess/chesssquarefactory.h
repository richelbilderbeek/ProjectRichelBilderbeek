#ifndef CHESSSQUAREFACTORY_H
#define CHESSSQUAREFACTORY_H

#include <boost/shared_ptr.hpp>

#include "chessfwd.h"

namespace ribi {
namespace Chess {

struct SquareFactory
{
  static boost::shared_ptr<Square> Create(
    const Chess::File& x,
    const Chess::Rank& y);

  ///Obtain a Square from its notational form
  template <class T = Square, template <typename> class Cont = boost::shared_ptr>
  static Cont<T> Create(
    const std::string& s);


  static boost::shared_ptr<Square> DeepCopy(const Square& s);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSSQUAREFACTORY_H
