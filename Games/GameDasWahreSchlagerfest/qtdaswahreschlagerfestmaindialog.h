//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifndef QTDASWAHRESCHLAGERFESTMAINDIALOG_H
#define QTDASWAHRESCHLAGERFESTMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
class QtDasWahreSchlagerfestMainDialog;
}

namespace ribi {

class QtDasWahreSchlagerfestMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtDasWahreSchlagerfestMainDialog(QWidget *parent = 0);
    QtDasWahreSchlagerfestMainDialog(const QtDasWahreSchlagerfestMainDialog&) = delete;
    QtDasWahreSchlagerfestMainDialog& operator=(const QtDasWahreSchlagerfestMainDialog&) = delete;
    ~QtDasWahreSchlagerfestMainDialog() noexcept;

private:
    Ui::QtDasWahreSchlagerfestMainDialog *ui;
};

} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTMAINDIALOG_H
