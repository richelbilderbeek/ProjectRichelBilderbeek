#include "tribool.h"

#include <ostream>

std::ostream& ribi::operator<<(std::ostream& os, const Tribool tribool)
{

  switch (tribool)
  {
    case Tribool::False: os << '0'; break;
    case Tribool::Indeterminate: os << '?'; break;
    case Tribool::True: os << '1'; break;
  }
  return os;
}
