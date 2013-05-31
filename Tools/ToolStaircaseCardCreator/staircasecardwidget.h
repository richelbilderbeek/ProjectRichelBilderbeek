//---------------------------------------------------------------------------
/*
Staircase Card Creator, tool to create staircase cards
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm
//---------------------------------------------------------------------------
#ifndef STAIRCASECARDWIDGET_H
#define STAIRCASECARDWIDGET_H
//---------------------------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------------------------
#include "staircasecard.h"
//---------------------------------------------------------------------------
class StaircaseCardWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StaircaseCardWidget(
    QWidget *parent = 0,
    const int n_cols = 16,
    const int n_rows = 20);

signals:

public slots:

private:
  StaircaseCard m_card;
};
//---------------------------------------------------------------------------
#endif // STAIRCASECARDWIDGET_H
