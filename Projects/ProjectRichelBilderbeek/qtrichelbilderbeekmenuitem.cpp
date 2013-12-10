#include "qtrichelbilderbeekmenuitem.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QPen>

#include "richelbilderbeekprogramtypes.h"
#pragma GCC diagnostic pop

ribi::QtRichelBilderbeekMenuItem::QtRichelBilderbeekMenuItem(const ProgramType program_type)
  : m_program_type(program_type)
{

  QPen pen = GetFocusPen();
  pen.setWidth(3);
  pen.setColor(QColor(255,0,0));
  SetFocusPen(pen);

  this->SetText(ProgramTypes::ProgramTypeToScreenName(program_type));

  //Rotation
  {
    const double f = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    const double angle = -3.0 + (6.0 * f);
    this->setRotation(angle);
  }
}
