/*
PreDickAdvocaTor, tool to predict WC scores
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppToolPreDickAdvocaTor.htm

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <string>
#include <vector>
#include <QDialog>

namespace Ui {
  class MainDialog;
}

class MainDialog : public QDialog {
  Q_OBJECT
public:
  MainDialog(QWidget *parent = 0);
  ~MainDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::MainDialog *ui;
  const std::vector<std::string> m_team_names;
  const std::vector<std::vector<int> > m_team_scores;

  private slots:
    void OnChanged(int);
};

const std::vector<std::string> GetTeamNames();
const std::vector<std::vector<int> > GetTeamScores(const std::size_t sz = 32);
int GetScore();

#endif // MAINDIALOG_H
