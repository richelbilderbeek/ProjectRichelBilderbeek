//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestChess.htm
//---------------------------------------------------------------------------
#include "qttestchessviewresourcesdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QLabel>

#include "chessresources.h"
#include "fileio.h"
#include "ui_qttestchessviewresourcesdialog.h"
#pragma GCC diagnostic pop

ribi::QtTestChessViewResourcesDialog::QtTestChessViewResourcesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestChessViewResourcesDialog)
{
  ui->setupUi(this);

  {
    const std::vector<std::string> v = Chess::Resources::GetFilenames();
    const std::size_t j = v.size();
    for (std::size_t i = 0; i!=j; ++i)
    {
      QLabel * const label = new QLabel;
      assert(fileio::FileIo().IsRegularFile(v[i]));
      label->setPixmap(QPixmap(v[i].c_str()));
      ui->gridLayout->addWidget(label,i%12,i/12);
    }
  }
}

ribi::QtTestChessViewResourcesDialog::~QtTestChessViewResourcesDialog() noexcept
{
  delete ui;
}
