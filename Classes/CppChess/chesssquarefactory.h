#ifndef CHESSSQUAREFACTORY_H
#define CHESSSQUAREFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#pragma GCC diagnostic pop

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
