#include "tictactoeais.h"

#include <cassert>
#include "tictactoeai.h"

std::vector<boost::shared_ptr<ribi::tictactoe::Ai>> ribi::tictactoe::Ais::GetAll() const noexcept
{
  std::vector<boost::shared_ptr<Ai>> v;
  {
    boost::shared_ptr<Ai> p(new AiEnforceDraw);
    assert(p);
    v.push_back(p);
  }
  {
    boost::shared_ptr<Ai> p(new AiEnforceWin);
    assert(p);
    v.push_back(p);
  }
  {
    boost::shared_ptr<Ai> p(new AiPlayRandom);
    assert(p);
    v.push_back(p);
  }
  return v;
}

