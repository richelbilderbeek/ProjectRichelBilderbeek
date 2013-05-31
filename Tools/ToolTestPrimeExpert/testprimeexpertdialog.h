//---------------------------------------------------------------------------
/*
TestPrimeExpert, tool to test the PrimeExpert class
Copyright (C) 2008-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPrimeExpert.htm
//---------------------------------------------------------------------------
#ifndef TESTPRIMEEXPERTDIALOG_H
#define TESTPRIMEEXPERTDIALOG_H
//------------------------------------------------------------
#include "primeexpert.h"
#include <QDialog>
//------------------------------------------------------------
namespace Ui {
  class TestPrimeExpertDialog;
}
//------------------------------------------------------------
class TestPrimeExpertDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TestPrimeExpertDialog(QWidget *parent = 0);
  ~TestPrimeExpertDialog();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::TestPrimeExpertDialog *ui;
  PrimeExpert m_expert;

private slots:
    void on_button_about_clicked();
    void on_edit_value_textChanged(QString );
};
//------------------------------------------------------------
#endif // TESTPRIMEEXPERTDIALOG_H
//------------------------------------------------------------
