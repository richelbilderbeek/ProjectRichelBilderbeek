#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qteverythingtopiecesshootergamewidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#pragma GCC diagnostic pop

QtEverythingToPiecesShooterGameWidget::QtEverythingToPiecesShooterGameWidget()
  : m_direction{Direction::down},
    m_keys{},
    m_x{0.0},
    m_y{0.0}
{
  {
    QTimer * const timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(20);
    timer->start();
  }
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
    m_x = (this->rect().center().x() / 2) - (32 / 2);
    m_y = (this->rect().center().y() / 2) - (32 / 2);
  }
}

void QtEverythingToPiecesShooterGameWidget::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_keys.insert(Key::up); m_direction = Direction::up; break;
    case Qt::Key_Right: m_keys.insert(Key::right); m_direction = Direction::right;break;
    case Qt::Key_Down: m_keys.insert(Key::down); m_direction = Direction::down;break;
    case Qt::Key_Left: m_keys.insert(Key::left); m_direction = Direction::left; break;
  }
}

void QtEverythingToPiecesShooterGameWidget::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_keys.erase(Key::up); break;
    case Qt::Key_Right: m_keys.erase(Key::right); break;
    case Qt::Key_Down: m_keys.erase(Key::down); break;
    case Qt::Key_Left: m_keys.erase(Key::left); break;
  }
}

void QtEverythingToPiecesShooterGameWidget::OnTimer()
{
  for (auto k: m_keys)
  {
    switch (k)
    {
      case Key::up   : --m_y; break;
      case Key::right: ++m_x; break;
      case Key::down : ++m_y; break;
      case Key::left : --m_x; break;
    }
  }
  repaint();
}

void QtEverythingToPiecesShooterGameWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  std::string s = ":/GameEverythingToPiecesShooter/images/GameEverythingToPiecesShooterPlayer";
  switch (m_direction)
  {
    case Direction::up   : s += "WalkUp1.png"; break;
    case Direction::right: s += "WalkRight1.png"; break;
    case Direction::down : s += "WalkDown1.png"; break;
    case Direction::left : s += "WalkLeft1.png"; break;
  }

  QPixmap p(s.c_str());
  painter.drawPixmap(m_x,m_y,34,34,p);
}
