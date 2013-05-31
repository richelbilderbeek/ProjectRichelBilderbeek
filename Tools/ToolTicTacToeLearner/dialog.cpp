//---------------------------------------------------------------------------
/*
TicTacToeLearner, evolving neural network playing tic-tac-toe
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
#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
//---------------------------------------------------------------------------
#include "dialog.h"
#include "dialogabout.h"
#include "ui_dialog.h"
//---------------------------------------------------------------------------
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_plot(new QwtPlot),
    m_curve_worst(new QwtPlotCurve),
    m_curve_best(new QwtPlotCurve)
{
  ui->setupUi(this);

  QObject::connect(ui->button_start,SIGNAL(clicked()),this,SLOT(onStartClick()));
  QObject::connect(ui->button_about,SIGNAL(clicked()),this,SLOT(onAboutClick()));

  ui->verticalLayout->addWidget(m_plot.get());
  m_plot->setAutoReplot(true);

  m_curve_worst->attach( m_plot.get() );
  m_curve_best->attach( m_plot.get() );
}
//---------------------------------------------------------------------------
Dialog::~Dialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void Dialog::changeEvent(QEvent *e)
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
void Dialog::onStartClick()
{
  const int n_timesteps = 10000;
  const int n_nets = 10;
  m_xs.resize(0);
  m_ys_worst.resize(0);
  m_ys_best.resize(0);

  //Set up the plot
  m_plot->setAxisScale(QwtPlot::xBottom,0.0,boost::numeric_cast<double>(n_timesteps));
  m_plot->setAxisScale(QwtPlot::yLeft,0.0,boost::numeric_cast<double>(n_nets*2*10));

  //Create the neural networks
  std::vector<NeuralNet> v;
  v.reserve(n_nets);
  for (int i=0; i!=n_nets; ++i)
  {
    v.push_back(NeuralNet(9,9,9));
  }
  //Mutate all nets
  BOOST_FOREACH(NeuralNet& n,v) n.Mutate(10.0);

  for (int t=0; t!=n_timesteps; ++t)
  {
    //std::cout << "Start t = " << t << '\n';
    std::vector<double> ratings(n_nets,0.0);
    for (int i=0; i!=n_nets; ++i)
    {
      for (int j=0; j!=n_nets; ++j)
      {
        const std::pair<double,double> rating = Rate_match(v[i],v[j]);
        ratings[i]+=rating.first;
        ratings[j]+=rating.second;
      }
    }
    //std::copy(ratings.begin(),ratings.end(),std::ostream_iterator<double>(std::cout," "));
    //std::cout << std::endl;
    const int worst_rating_index
      = std::distance(ratings.begin(),
          std::min_element(ratings.begin(),ratings.end()));
    assert(worst_rating_index >= 0 && worst_rating_index < n_nets);

    const double worst_rating = ratings[worst_rating_index];

    const int best_rating_index
      = std::distance(ratings.begin(),
          std::max_element(ratings.begin(),ratings.end()));
    assert(best_rating_index >= 0 && best_rating_index < n_nets);

    const double best_rating = ratings[best_rating_index];
    //std::cout << "Best rating " << best_rating << std::endl;

    //Plot
    m_xs.push_back(t);
    m_ys_worst.push_back(worst_rating);
    m_ys_best.push_back(best_rating);
    m_curve_worst->setData( &m_xs[0], &m_ys_worst[0],m_xs.size());
    m_curve_best->setData( &m_xs[0], &m_ys_best[0],m_xs.size());

    //Create the next generation
    v[worst_rating_index]   = v[best_rating_index];
    BOOST_FOREACH(NeuralNet& n,v) n.Mutate(0.001);

    #ifdef USE_TOO_GREEDY_APPROACH_468235464
    std::vector<NeuralNet> next_gen(n_nets - 1,v[best_rating_index]);
    assert(next_gen[0] == v[best_rating_index]);
    BOOST_FOREACH(NeuralNet& n,next_gen) n.Mutate(0.001);
    next_gen.push_back(v[best_rating_index]);
    assert(next_gen.size() == v.size());
    std::swap(v,next_gen);
    #endif
  }

  //m_curve_worst->setData( &m_xs[0], &m_ys_worst[0],m_xs.size());
  //m_curve_best->setData( &m_xs[0], &m_ys_best[0],m_xs.size());

  //m_curve_worst->attach( m_plot.get() );
  //m_curve_best->attach( m_plot.get() );
}
//---------------------------------------------------------------------------
void Dialog::onAboutClick()
{
  DialogAbout d;
  d.exec();
}
//---------------------------------------------------------------------------
///'player' is the index of the player
///player1 has index 1
///player2 has index 2
std::vector<double> ConvertToInput(const TicTacToe& t, const int player)
{
  assert(player == 1 || player == 2);
  std::vector<double> v;
  v.reserve(9);
  const boost::multi_array<int,2>& b = t.GetBoard();
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      const int z = b[x][y];
      if (z == 0) { v.push_back(0.0); continue; }
      v.push_back(z == player ? 1.0 : -1.0);
    }
  }
  assert(v.size() == 9);
  return v;
}
//---------------------------------------------------------------------------
std::pair<int,int> ConvertToMove(const std::vector<double>& outputs)
{
  const int index
    = std::distance(outputs.begin(),
        std::max_element(outputs.begin(),outputs.end()));
  assert(index >= 0);
  assert(index <  9);
  return std::make_pair(index % 3, index / 3);
}
//---------------------------------------------------------------------------
std::pair<double,double> Rate_match(const NeuralNet& n1, const NeuralNet& n2)
{
  TicTacToe t;
  assert(t.GetWinner() == 0);

  std::pair<double,double> ratings(0.0,0.0);
  //Turn 1
  {
    assert(t.GetCurrentTurn()==0);
    assert(t.GetCurrentPlayer()==1);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n1.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    ratings.first+=1.0;
    assert(t.GetWinner()==0);
    t.DoMove(move.first,move.second);
  }
  //Turn 2
  {
    assert(t.GetCurrentTurn()==1);
    assert(t.GetCurrentPlayer()==2);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n2.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    ratings.second+=1.0;
    assert(t.GetWinner()==0);
    t.DoMove(move.first,move.second);
  }
  //Turn 3
  {
    assert(t.GetCurrentTurn()==2);
    assert(t.GetCurrentPlayer()==1);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n1.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    ratings.first+=1.0;
    assert(t.GetWinner()==0);
    t.DoMove(move.first,move.second);
  }
  //Turn 4
  {
    assert(t.GetCurrentTurn()==3);
    assert(t.GetCurrentPlayer()==2);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n2.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    ratings.second+=1.0;
    assert(t.GetWinner()==0);
    t.DoMove(move.first,move.second);
  }
  //Turn 5
  {
    assert(t.GetCurrentTurn()==4);
    assert(t.GetCurrentPlayer()==1);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n1.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    t.DoMove(move.first,move.second);
    assert(t.GetWinner()==0 || t.GetWinner() == 1);
    if (t.GetWinner() == 1)
    {
      ratings.first = 10.0;
      return ratings;
    }
    ratings.first+=1.0;
  }
  //Turn 6
  {
    assert(t.GetCurrentTurn()==5);
    assert(t.GetCurrentPlayer()==2);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n2.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    t.DoMove(move.first,move.second);
    assert(t.GetWinner()==0 || t.GetWinner() == 2);
    if (t.GetWinner() == 2)
    {
      ratings.second = 10.0;
      return ratings;
    }
    ratings.second+=1.0;
  }
  //Turn 7
  {
    assert(t.GetCurrentTurn()==6);
    assert(t.GetCurrentPlayer()==1);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n1.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    t.DoMove(move.first,move.second);
    assert(t.GetWinner()==0 || t.GetWinner() == 1);
    if (t.GetWinner() == 1)
    {
      ratings.first = 10.0;
      return ratings;
    }
    ratings.first+=1.0;
  }
  //Turn 8
  {
    assert(t.GetCurrentTurn()==7);
    assert(t.GetCurrentPlayer()==2);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n2.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    t.DoMove(move.first,move.second);
    assert(t.GetWinner()==0 || t.GetWinner() == 2);
    if (t.GetWinner() == 2)
    {
      ratings.second = 10.0;
      return ratings;
    }
    ratings.second+=1.0;
  }
  //Turn 9
  {
    assert(t.GetCurrentTurn()==8);
    assert(t.GetCurrentPlayer()==1);
    const std::vector<double> inputs = ConvertToInput(t,t.GetCurrentPlayer());
    const std::vector<double> outputs = n1.Propagate(inputs);
    const std::pair<int,int> move = ConvertToMove(outputs);
    if (!t.CanDoMove(move.first,move.second)) return ratings;
    t.DoMove(move.first,move.second);
    assert(t.GetWinner()==0 || t.GetWinner() == 1 || t.GetWinner() == 3);
    if (t.GetWinner() == 1)
    {
      ratings.first = 10.0;
      return ratings;
    }
    ratings.first+=1.0;
  }
  return ratings;
}
//---------------------------------------------------------------------------
