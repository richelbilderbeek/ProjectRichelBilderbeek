#ifndef CHESSSQUAREFACTORY_H
#define CHESSSQUAREFACTORY_H

#include <boost/shared_ptr.hpp>

#include "chessfwd.h"

namespace Chess {

struct SquareFactory
{
  static boost::shared_ptr<Square> Create(
    const Chess::File& x,
    const Chess::Rank& y);

  ///Obtain a Square from its notational form
  static boost::shared_ptr<Square> Create(
    const std::string& s);


  static boost::shared_ptr<Square> DeepCopy(const Square& s);
};

} //~namespace Chess

#endif // CHESSSQUAREFACTORY_H
