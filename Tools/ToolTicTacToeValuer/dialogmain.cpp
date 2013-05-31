//---------------------------------------------------------------------------
/*
TicTacToeValuer, tool to solve TicTacToe
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
//From http://www.richelbilderbeek.nl/ToolTicTacToeValuer.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
#include <QDesktopWidget>
#include <QFile>
#include <QPainter>
//---------------------------------------------------------------------------
#include "dialogabout.h"
#include "dialogmain.h"
#include "ui_dialogmain.h"
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::DialogMain)
{
  ui->setupUi(this);

  QObject::connect(ui->button_about,SIGNAL(clicked()),
    this,SLOT(OnAboutClick()));
  QObject::connect(ui->button_start,SIGNAL(clicked()),
    this,SLOT(OnStart()));

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(screen);
  this->move( screen.center() - this->rect().center() );

  //this->DisplayGraph();
}
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void DialogMain::OnAboutClick()
{
  DialogAbout d;
  d.exec();
}
//---------------------------------------------------------------------------
void DialogMain::OnStart()
{
  std::queue<TicTacToe> todo;
  todo.push(m_board);

  for(int tick=0; !todo.empty(); ++tick)
  {
    if (tick%100==0) std::clog << "tick: " << tick << '\n';
    //std::clog << "TODO: " << todo.size() << '\n';
    const TicTacToe b = todo.front();
    //std::clog << b << '\n';
    //Obtain possible moves
    typedef boost::tuples::tuple<int,int,int> Tuple;
    std::vector<Tuple> v;
    for (int i=0; i!=9; ++i)
    {
      const int x = i/3;
      const int y = i%3;
      if (b.CanDoMove(x,y))
      {
        v.push_back(boost::tuples::make_tuple(x,i,y));
      }
    }
    //Limit graph
    std::random_shuffle(v.begin(),v.end());
    if (v.size() > 2) v.resize(2);


    if (v.empty())
    {
      todo.pop();
      //std::clog << "Pop, due to no moves, TODO: " << todo.size() << '\n';
      continue;
    }
    //std::clog << "New moves: " << v.size() << '\n';
    //Obtain next states
    const int state_now = b.GetSummarizedState();
    BOOST_FOREACH(const Tuple& p,v)
    {
      TicTacToe temp(b.GetSummarizedState());
      assert(temp.CanDoMove(boost::get<0>(p),boost::get<2>(p)));
      temp.DoMove(boost::get<0>(p),boost::get<2>(p));
      const int state_next = temp.GetSummarizedState();
      m_graph.AddEdge(state_now,boost::get<1>(p),state_next);
      todo.push(temp);
    }
    //std::clog << "Pop, due to finished move, TODO: " << todo.size() << '\n';
    todo.pop();
    //DisplayGraph();
    //QCoreApplication::processEvents();
  }
  DisplayGraph();
}
//---------------------------------------------------------------------------
void DialogMain::DisplayGraph()
{
  //Write graph to file
  {
    std::ofstream f("out.dot");
    f << m_graph;
  }
  //Load graph to QLabel
  {
    assert(QFile::exists("out.dot"));
    std::system("dot -Tpng out.dot > out.png");
    QImage png("out.png");
    ui->label_graph->setPixmap(QPixmap::fromImage(png));
  }
  //Text output
  ui->text_out->clear();
  ui->text_out->appendPlainText(
    QString("Number of vertices: ")
    + QString::number(m_graph.GetNumVertices()));
  ui->text_out->appendPlainText(
    QString("Number of edges: ")
    + QString::number(m_graph.GetNumEdges()));

  //Append text file
  {
    ui->text_out->appendPlainText(" ");
    ui->text_out->appendPlainText("Graph file ('out.dot') content:");
    ui->text_out->appendPlainText(" ");
    const std::vector<std::string> v = FileToVector("out.dot");
    BOOST_FOREACH(const std::string& s, v)
    {
      ui->text_out->appendPlainText(s.c_str());
    }
  }
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
{
  assert(QFile::exists(fileName.c_str()));
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
