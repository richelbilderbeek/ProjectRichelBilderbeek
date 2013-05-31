#ifndef QTRICHELBILDERBEEKPROGRAM_H
#define QTRICHELBILDERBEEKPROGRAM_H

#include <QDialog>
#include "richelbilderbeekprogramtype.h"
#include "qthideandshowdialog.h"

struct QtRichelBilderbeekProgram
{
  ///Create the menu dialog corresponding to the program type
  ///Might return a nullprt, if the program type has no Qt menu
  static QDialog * CreateQtMenuDialog(const RichelBilderbeek::ProgramType type);

  ///Create a placeholder dialog for the program type
  static QtHideAndShowDialog * CreateQtPlaceholderDialog(const RichelBilderbeek::ProgramType type);
};

#endif // QTRICHELBILDERBEEKPROGRAM_H
