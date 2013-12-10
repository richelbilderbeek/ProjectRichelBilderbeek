#ifndef QTRICHELBILDERBEEKMENUITEM_H
#define QTRICHELBILDERBEEKMENUITEM_H

#include "richelbilderbeekprogramtype.h"
#include "qtroundedtextrectitem.h"

namespace ribi {

struct QtRichelBilderbeekMenuItem : public QtRoundedTextRectItem
{
  QtRichelBilderbeekMenuItem(const ProgramType program_type);

  ProgramType GetProgramType() const noexcept { return m_program_type; }

  const ProgramType m_program_type;
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKMENUITEM_H
