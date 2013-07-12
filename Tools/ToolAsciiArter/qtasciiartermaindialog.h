//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef QTASCIIARTERDIALOG_H
#define QTASCIIARTERDIALOG_H

#include <QDialog>

#include <boost/scoped_ptr.hpp>

#include "asciiartermaindialog.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtAsciiArterMainDialog;
}

struct QImage;

class QtAsciiArterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAsciiArterMainDialog(QWidget *parent = 0);
  ~QtAsciiArterMainDialog();

protected:
  void changeEvent(QEvent *e);
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtAsciiArterMainDialog *ui;
  const boost::scoped_ptr<AsciiArterMainDialog> m_dialog;
  void DrawAsciiArt();

  static const std::vector<std::vector<double> >
    ConvertToGreyYx(const QImage * const i);

private slots:
  void on_edit_width_textChanged(QString );
  void on_button_load_clicked();
};

#endif // QTASCIIARTERDIALOG_H
