#include "aaffighterfactory.h"

#include <cassert>

#include "trace.h"
#include "aaffighter.h"
#include "aafmoleculefactory.h"
#include "testtimer.h"

ribi::aaf::FighterFactory::FighterFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::aaf::Fighter> ribi::aaf::FighterFactory::Create(const ribi::aaf::AminoAcid a) const noexcept
{
  const boost::shared_ptr<Molecule> molecule {
    MoleculeFactory().Create(a)
  };
  boost::shared_ptr<Fighter> f {
    new Fighter(molecule)
  };
  assert(f);
  return f;
}


#ifndef NDEBUG
void ribi::aaf::FighterFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
