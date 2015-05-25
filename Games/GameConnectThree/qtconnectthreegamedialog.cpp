//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconnectthreegamedialog.h"

#include <QDesktopWidget>
#include <QTimer>

#include "connectthree.h"
#include "connectthreewidget.h"
#include "connectthreeresources.h"
#include "qtconnectthreeresources.h"
#include "ui_qtconnectthreegamedialog.h"
#include "testtimer.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreewidget.h"
#include "qtshowwinnerdialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::con3::QtConnectThreeGameDialog::QtConnectThreeGameDialog(
  const boost::shared_ptr<const ConnectThreeResources> resources,
  QWidget *parent,
  const std::bitset<3>& is_player_human) noexcept
  : QtHideAndShowDialog(parent),
    m_signal_close{},
    ui(new Ui::QtConnectThreeGameDialog),
    m_board{
      new QtConnectThreeWidget(
        resources,
        nullptr,is_player_human,16,8),
    },
    m_is_player_human(is_player_human),
    m_resources(resources)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  //Add board widget
  {
    assert(!ui->widget->layout());
    QLayout * const mylayout = new QVBoxLayout;
    mylayout->addWidget(m_board);
    ui->widget->setLayout(mylayout);
    m_board->setMinimumSize(100,100);
  }

  QObject::connect(ui->button_quit,&QPushButton::clicked,this,&ribi::con3::QtConnectThreeGameDialog::close);
  m_board->m_signal_valid_move.connect(boost::bind(&ribi::con3::QtConnectThreeGameDialog::OnValidMove,this));

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );

  ui->button_quit->setText(resources->GetQuitText().c_str());

  OnValidMove(); //Draw screen
}

ribi::con3::QtConnectThreeGameDialog::~QtConnectThreeGameDialog() noexcept
{
  delete m_board;
  delete ui;
}

void ribi::con3::QtConnectThreeGameDialog::DoComputerTurn() noexcept
{
  this->m_board->DoComputerTurn();
  OnValidMove();
}

void ribi::con3::QtConnectThreeGameDialog::OnValidMove() noexcept
{
  if (m_board->GetWinner() == Winner::no_winner)
  {
    const Player active_player = m_board->GetActivePlayer();
    switch(active_player)
    {
      case Player::player1:
        ui->label_player1->setPixmap(QPixmap(m_resources->GetPlayersFilenames()[0].c_str()));
        ui->label_player2->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[1].c_str()));
        ui->label_player3->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[2].c_str()));
        break;
      case Player::player2:
        ui->label_player1->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[0].c_str()));
        ui->label_player2->setPixmap(QPixmap(m_resources->GetPlayersFilenames()[1].c_str()));
        ui->label_player3->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[2].c_str()));
        break;
      case Player::player3:
        ui->label_player1->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[0].c_str()));
        ui->label_player2->setPixmap(QPixmap(m_resources->GetPlayersGreyFilenames()[1].c_str()));
        ui->label_player3->setPixmap(QPixmap(m_resources->GetPlayersFilenames()[2].c_str()));
        break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("Known value of GetCurrentPlayer in WtConnectThreeGameDialog::OnValidMove");
    }
    if (this->m_board->IsComputerTurn())
    {
      //Do a computer turn after a second
      QTimer::singleShot(100,
        this,
        //&ribi::con3::QtConnectThreeGameDialog::DoComputerTurn //Does not work
        SLOT(DoComputerTurn())
      );
    }

    return;
  }
  //There is a winner, or the screen is full
  {
    std::string filename;
    switch(m_board->GetWinner())
    {
        case Winner::player1  : filename = m_resources->GetPlayersFilenames()[0]; break;
        case Winner::player2  : filename = m_resources->GetPlayersFilenames()[1]; break;
        case Winner::player3  : filename = m_resources->GetPlayersFilenames()[2]; break;
        case Winner::no_winner: filename = m_resources->GetEmptyFilename(); break;
        default:
          assert(!"Should not get here");
          throw std::logic_error("Known value of GetCurrentPlayer in WtConnectThreeGameDialog::OnValidMove");
    }
    QtShowWinnerDialog d(filename,m_resources->GetWinnerText());
    d.setStyleSheet(this->styleSheet());
    d.setWindowIcon(this->windowIcon());

    //this->hide();
    d.exec();
  }
  this->close();
}

#ifndef NDEBUG
void ribi::con3::QtConnectThreeGameDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const boost::shared_ptr<const ConnectThreeResources> resources(new QtConnectThreeResources);
  assert(resources);
  const boost::shared_ptr<const QtConnectThreeGameDialog> d {
    new QtConnectThreeGameDialog(resources,nullptr,std::bitset<3>(false))
  };
  assert(d);
}
#endif
