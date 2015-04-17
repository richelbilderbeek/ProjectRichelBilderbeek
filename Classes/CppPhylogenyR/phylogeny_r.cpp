#include "phylogeny_r.h"

#include <cassert>

PhylogenyR::PhylogenyR()
{
  #ifndef NDEBUG
  Test();
  #endif
}
