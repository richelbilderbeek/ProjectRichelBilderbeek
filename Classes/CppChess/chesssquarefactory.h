#ifndef RIBI_CHESSSQUAREFACTORY_H
#define RIBI_CHESSSQUAREFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

struct SquareFactory
{
  SquareFactory() noexcept;

  const boost::shared_ptr<Square> Create(
    const Chess::File& x,
    const Chess::Rank& y
  ) const noexcept;

  ///Obtain a Square from its notational form
  const boost::shared_ptr<Square> Create(
    const std::string& s
  ) const noexcept;

  ///Obtain the from Square from a move, that is, the first two non-piece characters
  const boost::shared_ptr<Square> CreateFromMove(
    const std::string& s
  ) const noexcept;

  boost::shared_ptr<Square> DeepCopy(const boost::shared_ptr<const Square> s) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSSQUAREFACTORY_H
