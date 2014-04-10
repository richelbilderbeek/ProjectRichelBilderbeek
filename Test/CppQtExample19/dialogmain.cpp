#include "dialogmain.h"

#include <cassert>
#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "ui_dialogmain.h"
#pragma GCC diagnostic pop

DialogMain::DialogMain(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogMain),
  m_timer(new QTimer(this)),
  m_scene(new QGraphicsScene(this)),
  m_sprite(new QGraphicsPixmapItem),
  m_angle(0.0)
{
  ui->setupUi(this);

  //Load the sprite
  m_sprite->setPixmap(QPixmap(":/images/R.png"));
  assert(!m_sprite->pixmap().isNull());

  //Set the center of the sprite for rotation
  m_sprite->setTransformOriginPoint(
    static_cast<double>(m_sprite->pixmap().width()) / 2.0,
    static_cast<double>(m_sprite->pixmap().height()) / 2.0);

  //Add the sprite to the scene
  m_scene->addItem(m_sprite);

  //Add the scene to the view
  ui->graphicsView->setScene(m_scene);

  //Connect and start a timer
  QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(onTick()));
  QObject::connect(ui->check_auto_rotate,SIGNAL(clicked()),this,SLOT(onCheck()));
  QObject::connect(ui->button_left,SIGNAL(clicked()),this,SLOT(onButtonLeft()));
  QObject::connect(ui->button_right,SIGNAL(clicked()),this,SLOT(onButtonRight()));


  //Start the timer
  m_timer->start(100);

  this->setGeometry(0,0,
    static_cast<int>(640),
    static_cast<int>(640));
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

DialogMain::~DialogMain()
{
  delete ui;
  delete m_sprite;
}

//Sets the scale of the maze
void DialogMain::resizeEvent(QResizeEvent*)
{
  const int size = std::max(
    m_sprite->pixmap().width(),
    m_sprite->pixmap().height());

  const double scale = 0.9
    * std::min(ui->graphicsView->width(),
        ui->graphicsView->height())
    / (static_cast<double>(size) * std::sqrt(2.0));
  m_sprite->setScale(scale);
}

void DialogMain::keyPressEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    case Qt::Key_Left: case Qt::Key_Minus: case Qt::Key_A:
      m_angle-=1.0;
      m_sprite->setRotation(m_angle);
      break;
    case Qt::Key_Right: case Qt::Key_Plus: case Qt::Key_D:
      m_angle+=1.0;
      m_sprite->setRotation(m_angle);
      break;
  }
}

void DialogMain::onTick()
{
  m_angle+=1.0;
  m_sprite->setRotation(m_angle);
}

void DialogMain::onCheck()
{
  if (ui->check_auto_rotate->isChecked())
  {
    m_timer->start();
  }
  else
  {
    m_timer->stop();
  }

}

void DialogMain::onButtonLeft()
{
  m_angle-=1.0;
  m_sprite->setRotation(m_angle);
}

void DialogMain::onButtonRight()
{
  m_angle+=1.0;
  m_sprite->setRotation(m_angle);
}
