//---------------------------------------------------------------------------
/*
QtRichelBilderbeekGalleryDialog, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtRichelBilderbeekGalleryDialog.htm
//---------------------------------------------------------------------------
#ifndef QTRICHELBILDERBEEKGALLERYDIALOG_H
#define QTRICHELBILDERBEEKGALLERYDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui { class QtRichelBilderbeekGalleryDialog; }
struct QModelIndex;

namespace ribi {

struct Program;

class QtRichelBilderbeekGalleryDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtRichelBilderbeekGalleryDialog(QWidget *parent = 0);
  QtRichelBilderbeekGalleryDialog(const QtRichelBilderbeekGalleryDialog&) = delete;
  QtRichelBilderbeekGalleryDialog& operator=(const QtRichelBilderbeekGalleryDialog&) = delete;
  ~QtRichelBilderbeekGalleryDialog() noexcept;

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

protected:
  void keyPressEvent(QKeyEvent* e) noexcept;


private slots:
  void on_table_clicked(const QModelIndex &index) noexcept;

  void on_table_cellEntered(int row, int column) noexcept;

  void on_table_entered(const QModelIndex &index) noexcept;

private:
  Ui::QtRichelBilderbeekGalleryDialog *ui;
  const std::vector<boost::shared_ptr<Program> > m_programs;

  ///Show the screenshot requested by the item in [col,row]
  void ShowScreenshot(const int col, const int row) noexcept;
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKGALLERYDIALOG_H

