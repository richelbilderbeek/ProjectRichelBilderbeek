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
#ifndef DIALOG_H
#define DIALOG_H
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
#include "../ToolTestNeuralNet/neuralnet.h"
#include "../ToolTestTicTacToe/tictactoe.h"
//---------------------------------------------------------------------------
struct QwtPlot;
struct QwtPlotCurve;
namespace Ui {
  class Dialog;
}
//---------------------------------------------------------------------------
class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::Dialog *ui;
  boost::shared_ptr<QwtPlot> m_plot;
  boost::shared_ptr<QwtPlotCurve> m_curve_worst;
  boost::shared_ptr<QwtPlotCurve> m_curve_best;
  std::vector<double> m_xs;
  std::vector<double> m_ys_best;
  std::vector<double> m_ys_worst;

private slots:
  void onStartClick();
  void onAboutClick();
};
//---------------------------------------------------------------------------
std::vector<double> ConvertToInput(const TicTacToe& t, const int player);
//---------------------------------------------------------------------------
std::pair<int,int> ConvertToMove(const std::vector<double>& outputs);
//---------------------------------------------------------------------------
std::pair<double,double> Rate_match(const NeuralNet& n1, const NeuralNet& n2);
//---------------------------------------------------------------------------
#endif // DIALOG_H
