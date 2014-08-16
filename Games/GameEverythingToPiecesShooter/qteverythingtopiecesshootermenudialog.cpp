/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkenmenudialog.h"

#include <cassert>


#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/timer.hpp>

#include "boenkenmenudialog.h"
#include "boenkenarenasettings.h"
#include "qtboenkengame.h"
#include "qtaboutdialog.h"
#include "qtboenkenarenadialog.h"
#include "qtboenkencontrolsdialog.h"
#include "qtboenkenmaindialog.h"
#include "qtboenkenplayersdialog.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspritenonmoving.h"
#include "qtboenkenspriteplayer.h"
#include "trace.h"
#include "ui_qtboenkenmenudialog.h"

#pragma GCC diagnostic pop

ribi::QtEverythingToPiecesShooterMenuDialog::QtEverythingToPiecesShooterMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtEverythingToPiecesShooterMenuDialog),
    m_controls(new QtEverythingToPiecesShooterControlsDialog),
    m_players( new QtEverythingToPiecesShooterPlayersDialog),
    m_arena(new QtEverythingToPiecesShooterArenaDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  QObject::connect(ui->button_set_controls,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onControlsClick);
  QObject::connect(ui->button_set_players ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onPlayersClick );
  QObject::connect(ui->button_set_arena   ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onArenaClick   );
  QObject::connect(ui->button_start       ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onStartClick   );
  QObject::connect(ui->button_train       ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onTrainClick   );
  QObject::connect(ui->button_about       ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::onAboutClick   );
  QObject::connect(ui->button_quit        ,&QAbstractButton::clicked,this,&ribi::QtEverythingToPiecesShooterMenuDialog::close          );
}

ribi::QtEverythingToPiecesShooterMenuDialog::~QtEverythingToPiecesShooterMenuDialog() noexcept
{
  delete ui;
}

const std::vector<boost::shared_ptr<ribi::EverythingToPiecesShooter::SpritePlayer> > ribi::QtEverythingToPiecesShooterMenuDialog::CreatePlayers(
  const EverythingToPiecesShooter::ArenaSettings& a)
{
  //Create two
  std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer> > v;
  const int n_players = 2;
  const int size = 32;

  const double mid_x
    = boost::numeric_cast<double>(a.screen_size.first) / 2.0;
  const double mid_y
    = boost::numeric_cast<double>(a.screen_size.second) / 2.0;

  if (a.formation==EverythingToPiecesShooter::straight_line)
  {
    const int x_left  = (1 * (a.width() / 4) ) - (size / 2);
    const int x_right = (3 * (a.width() / 4) ) - (size / 2);
    const int players_height = size * (n_players / 2);
    int y = (a.height()) / 2 - (players_height / 2);
    for (int i=0; i!=n_players; ++i,y+=(size/2))
    {
      const int x = (i % 2 ? x_right : x_left);
      const double pi = boost::math::constants::pi<double>();
      const double face_angle = (i % 2 ? 1.5 * pi : 0.5 * pi);
      const unsigned char r = (i % 2 ?   0 : 255);
      const unsigned char g = (i % 2 ?   0 :   0);
      const unsigned char b = (i % 2 ? 255 :   0);
      boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer> p(
        new EverythingToPiecesShooter::SpritePlayer(x,y,face_angle,size,r,g,b));
      assert(p);
      v.push_back(p);
    }

  }
  else
  {
    assert(a.formation==EverythingToPiecesShooter::circle_inward || a.formation==EverythingToPiecesShooter::circle_outward);
    const double ray_x = mid_x / 2.0;
    const double ray_y = mid_y / 2.0;
    const double pi = boost::math::constants::pi<double>();
    const double d_angle = (2.0 * pi) / boost::numeric_cast<double>(n_players);
    double angle = 1.5 * pi;

    for (int i=0; i!=n_players; ++i,angle+=d_angle)
    {
      const double x
       = mid_x + (std::sin(angle) * ray_x)
       - (boost::numeric_cast<double>(size) / 2.0);
      const double y
        = mid_y - (std::cos(angle) * ray_y)
        - (boost::numeric_cast<double>(size) / 2.0);
      const unsigned char r = (i % 2 ?   0 : 255);
      const unsigned char g = (i % 2 ?   0 :   0);
      const unsigned char b = (i % 2 ? 255 :   0);
      const double face_angle = angle
        + (a.formation==EverythingToPiecesShooter::circle_inward ? pi : 0.0);

      boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer> p(
        new EverythingToPiecesShooter::SpritePlayer(x,y,face_angle,size,r,g,b));
      assert(p);
      v.push_back(p);
    }
  }

  return v;
}

const std::vector<boost::shared_ptr<ribi::EverythingToPiecesShooter::SpriteBall> > ribi::QtEverythingToPiecesShooterMenuDialog::CreateBalls(
  const EverythingToPiecesShooter::ArenaSettings& a)
{
  const int size = 32;
  //A ball is always green
  const unsigned char r =   0;
  const unsigned char g = 255;
  const unsigned char b =   0;
  std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteBall> > v;
  switch (a.n_balls)
  {
    case 1:
    {
      const int x
        = a.screen_size.first / 2 - (size / 2);
      const int y
        = a.screen_size.second / 2 - (size / 2);
      boost::shared_ptr<EverythingToPiecesShooter::SpriteBall> s(
        new EverythingToPiecesShooter::SpriteBall(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }
    break;
    case 2:
    {
      const int x1
        = (a.screen_size.first / 2)
        - size;
      const int x2 = x1 + size + 1;
      const int y
        = (a.screen_size.second / 2)
        - (size / 2);
      boost::shared_ptr<EverythingToPiecesShooter::SpriteBall> s1(
        new EverythingToPiecesShooter::SpriteBall(x1,y,size,r,g,b));
      boost::shared_ptr<EverythingToPiecesShooter::SpriteBall> s2(
        new EverythingToPiecesShooter::SpriteBall(x2,y,size,r,g,b));
      assert(s1);
      assert(s2);
      v.push_back(s1);
      v.push_back(s2);
    }
    break;
    default:
      assert(!"Should not get here");
  }
  return v;
}

///Always creates the four goalposts
const std::vector<boost::shared_ptr<ribi::EverythingToPiecesShooter::SpriteNonMoving> > ribi::QtEverythingToPiecesShooterMenuDialog::CreateObstacles(
  const EverythingToPiecesShooter::ArenaSettings& a)
{
  const int size = 32;
  //A obstacle is always grey
  const unsigned char r = 255;
  const unsigned char g = 255;
  const unsigned char b = 255;

  std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> > v;
  {
    //Top-left goalpost
    const int x = 0;
    const int y = a.screen_size.second / 4;
    boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
      new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const int x = 0;
    const int y = 3 * a.screen_size.second / 4;
    boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
      new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  {
    //Top-left goalpost
    const int x = a.screen_size.first - size;
    const int y = a.screen_size.second / 4;
    boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
      new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const int x = a.screen_size.first - size;
    const int y = 3 * a.screen_size.second / 4;
    boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
      new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  if (a.n_obstacles == 2)
  {
    {
      //Left obstacle
      const int x = ( (1 * a.width() ) / 8) - (size / 2);
      const int y = ( (1 * a.height()) / 2) - (size / 2);
      boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
        new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }
    {
      //Right obstacle
      const int x = ( (7 * a.width() ) / 8) - (size / 2);
      const int y = ( (1 * a.height()) / 2) - (size / 2);
      boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> s(
        new EverythingToPiecesShooter::SpriteNonMoving(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }

  }
  return v;
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onControlsClick()
{
  this->ShowChild(m_controls.get());
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onPlayersClick()
{
  this->ShowChild(m_players.get());
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onArenaClick()
{
  this->ShowChild(m_arena.get());
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onStartClick()
{
  const EverythingToPiecesShooter::ArenaSettings a = this->m_arena->GetSettings();
  const EverythingToPiecesShooter::Controls c = this->m_controls->GetControls();
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer   > > players   = CreatePlayers(a);
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteBall     > > balls     = CreateBalls(a);
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> > obstacles = CreateObstacles(a);
  boost::shared_ptr<EverythingToPiecesShooter::Game> b(new EverythingToPiecesShooter::Game(a,c,players,balls,obstacles));
  assert(b);
  QtEverythingToPiecesShooterMainDialog d(0,b);

  this->hide();
  d.exec();
  this->show();
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onTrainClick()
{
  const EverythingToPiecesShooter::ArenaSettings a = this->m_arena->GetSettings();
  const EverythingToPiecesShooter::Controls c = this->m_controls->GetControls();
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer   > > players   = CreatePlayers(a);
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteBall     > > balls     = CreateBalls(a);
  const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> > obstacles = CreateObstacles(a);

  boost::shared_ptr<EverythingToPiecesShooter::Game> b(new EverythingToPiecesShooter::Game(a,c,players,balls,obstacles));
  assert(b);
  this->hide();
  QtEverythingToPiecesShooterMainDialog d(0,b);

  for (int i=0; i!=1000; ++i)
  {
    d.show();
    for(const boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer>& p: players)
    {
      p->Accelerate();
      p->TurnRight();
    }
    b->tick();
    d.repaint();
  }
  this->show();
}

void ribi::QtEverythingToPiecesShooterMenuDialog::onAboutClick()
{
  About a = EverythingToPiecesShooter::MenuDialog().GetAbout();
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtEverythingToPiecesShooterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtEverythingToPiecesShooterMenuDialog::Test");
  {

    EverythingToPiecesShooter::ArenaSettings a;
    a.formation = EverythingToPiecesShooter::circle_inward;
    a.friction = 0.999;
    a.n_balls = 1;
    a.n_obstacles = 4;
    a.screen_size = std::make_pair(320,200);
    EverythingToPiecesShooter::Controls c;
    const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpritePlayer   > > players   = CreatePlayers(a);
    const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteBall     > > balls     = CreateBalls(a);
    const std::vector<boost::shared_ptr<EverythingToPiecesShooter::SpriteNonMoving> > obstacles = CreateObstacles(a);
    boost::shared_ptr<EverythingToPiecesShooter::Game> b(new EverythingToPiecesShooter::Game(a,c,players,balls,obstacles));
    assert(b);
    QtEverythingToPiecesShooterMainDialog d(0,b);
  }
  TRACE("Finished ribi::QtEverythingToPiecesShooterMenuDialog::Test successfully");
}
#endif
*/
