#include "qtroundededitrectitempadding.h"

#include <iostream>

bool ribi::operator==(
  const QtRoundedEditRectItemPadding& lhs,
  const QtRoundedEditRectItemPadding& rhs
) noexcept
{
  return lhs.bottom == rhs.bottom
    && lhs.left == rhs.left
    && lhs.right == rhs.right
    && lhs.top == rhs.top
  ;
}

bool ribi::operator!=(
  const QtRoundedEditRectItemPadding& lhs,
  const QtRoundedEditRectItemPadding& rhs
) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::operator<<(std::ostream& os, const QtRoundedEditRectItemPadding &p) noexcept
{
  os
    << '(' << p.left << ',' << p.top << ')'
    << '-'
    << '(' << p.right << ',' << p.bottom << ')'
  ;
  return os;
}
