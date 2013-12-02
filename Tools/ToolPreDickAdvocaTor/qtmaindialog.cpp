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

#include "maindialog.h"
#include "ui_maindialog.h"
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    m_team_names(GetTeamNames()),
    m_team_scores(GetTeamScores())
{
  ui->setupUi(this);

  const int sz = static_cast<int>(m_team_names.size());
  for (int i = 0; i!=sz; ++i)
  {
    const QString name = m_team_names[i].c_str();
    ui->comboBox1->addItem(name);
    ui->comboBox2->addItem(name);
  }

  this->connect(ui->comboBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(OnChanged(int)));
  this->connect(ui->comboBox2,SIGNAL(currentIndexChanged(int)),this,SLOT(OnChanged(int)));

  OnChanged(0);

}

MainDialog::~MainDialog()
{
  delete ui;
}

void MainDialog::OnChanged(int)
{
  const int index1 = ui->comboBox1->currentIndex();
  const int index2 = ui->comboBox2->currentIndex();
  if (index1==index2)
  {
    ui->label1->setText("-");
    ui->label2->setText("-");
  }
  else
  {
    const int score1 = m_team_scores[index1][index2];
    const int score2 = m_team_scores[index2][index1];
    QString s1; s1.setNum(score1);
    QString s2; s2.setNum(score2);

    ui->label1->setText(s1);
    ui->label2->setText(s2);
  }
}

void MainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

const std::vector<std::string> GetTeamNames()
{
  std::vector<std::string> v;
  v.push_back("Algerije");
  v.push_back("Argentinie");
  v.push_back("Australie");
  v.push_back("Brazilie");
  v.push_back("Chili");
  v.push_back("Denemarken");
  v.push_back("Duitsland");
  v.push_back("Engeland");
  v.push_back("Frankrijk");
  v.push_back("Ghana");
  v.push_back("Griekenland");
  v.push_back("Honduras");
  v.push_back("Italie");
  v.push_back("Ivoorkust");
  v.push_back("Japan");
  v.push_back("Kameroen");
  v.push_back("Mexico");
  v.push_back("Nederland");
  v.push_back("Nieuw-Zeeland");
  v.push_back("Nigeria");
  v.push_back("Noord-Korea");
  v.push_back("Paraguay");
  v.push_back("Portugal");
  v.push_back("Servie");
  v.push_back("Slovenie");
  v.push_back("Slowakije");
  v.push_back("Spanje");
  v.push_back("USA");
  v.push_back("Uruguay");
  v.push_back("Zuid-Afrika");
  v.push_back("Zuid-Korea");
  v.push_back("Zwitserland");
  assert(v.size()==32);
  return v;
}

const std::vector<std::vector<int> > GetTeamScores(const std::size_t sz)
{
  assert(sz == 32);
  std::vector<std::vector<int> > v(sz,std::vector<int>(sz,0));

  for (std::size_t y = 0; y!=sz; ++y)
  {
    for (std::size_t x = 0; x!=sz; ++x)
    {
      v[y][x] = GetScore();
    }
    //Add known score for The Netherlands
    v[y][17] = 0;
  }
  //Add known scores for The Netherlands
  v[17] = std::vector<int>(sz,10);

  return v;
}

int GetScore()
{
  const int max_score = 9;
  int r = std::rand() % 256;
  for (int score=0; score!=max_score; ++score)
  {
    if ((r%2)==1) return score;
    r >>= 1;
  }
  return max_score;
}
