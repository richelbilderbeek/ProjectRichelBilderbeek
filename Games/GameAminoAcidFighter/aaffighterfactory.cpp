#include "aaffighterfactory.h"

#include <cassert>

#include "trace.h"

ribi::aaf::FighterFactory::FighterFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::aaf::Fighter> ribi::aaf::FighterFactory::Create(const ribi::aaf::AminoAcid a) const noexcept
{
  boost::shared_ptr<Fighter> f;

  assert(f);
  return f;
}


#ifndef NDEBUG
void ribi::aaf::FighterFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::ProgramTypes::Test");
  TRACE("Finished ribi::ProgramTypes::Test successfully");
}
#endif
