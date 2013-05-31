//---------------------------------------------------------------------------
/*
TestEncranger, tool to test the Encranger class
Copyright (C) 2009-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestEncranger.htm
//---------------------------------------------------------------------------
#ifndef WTTESTENCRANGERDIALOG_H
#define WTTESTENCRANGERDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
//---------------------------------------------------------------------------
struct TestEncrangerDialog;
//---------------------------------------------------------------------------
struct WtTestEncrangerMainDialog : public Wt::WContainerWidget
{
  WtTestEncrangerMainDialog();

  private:
  boost::scoped_ptr<TestEncrangerDialog> m_dialog;
  Wt::WLineEdit * m_edit_encrypted_text;
  Wt::WLineEdit * m_edit_key;
  Wt::WLineEdit * m_edit_plain_text;

  void OnDeencryptClick();
  void OnEncryptClick();
  void ShowMain();
};
//---------------------------------------------------------------------------
#endif // WTTESTENCRANGERDIALOG_H
