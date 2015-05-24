#include "qtlizardpaperrockscissorsspockwidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "lizardpaperrockscissorsspocksimulation.h"
#include "ui_qtlizardpaperrockscissorsspockwidget.h"

QtLizardPaperRockScissorsSpockWidget::QtLizardPaperRockScissorsSpockWidget(
  const int width,
  const int height,
  const ribi::lprss::Simulation::Initialization initialization,
  QWidget *parent
)
  : QWidget(parent),
    ui(new Ui::QtLizardPaperRockScissorsSpockWidget),
    m_pixmap{QPixmap(width,height)},
    m_simulation{ribi::lprss::Simulation(width,height,initialization)}
{
  ui->setupUi(this);
  OnTimer();
  //Start a timer
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(1);
    timer->start();
  }
}

QtLizardPaperRockScissorsSpockWidget::~QtLizardPaperRockScissorsSpockWidget()
{
  delete ui;
}

void QtLizardPaperRockScissorsSpockWidget::OnTimer()
{
  using CellType = ribi::LizardPaperRockScissorsSpock;

  m_simulation.Next();

  const int height{m_pixmap.height()};
  const int width{m_pixmap.width()};
  QImage image(width,height,QImage::Format_RGB32);
  const auto& grid = m_simulation.GetGrid();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const auto celltype = grid[y][x];
      auto color = qRgb(0,0,0);
      const int high{196};
      switch (celltype)
      {
        case CellType::lizard: color = qRgb(0,high,0); break;
        case CellType::paper: color = qRgb(high,high,0); break;
        case CellType::rock: color = qRgb(high,0,0); break;
        case CellType::scissors: color = qRgb(high,0,high); break;
        case CellType::spock: color = qRgb(0,0,high); break;
      }
      image.setPixel(x,y,color);
    }
  }
  m_pixmap = QPixmap::fromImage(image);
  update();
}

void QtLizardPaperRockScissorsSpockWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap
  );
}

void QtLizardPaperRockScissorsSpockWidget::SetAll(
  const int width,
  const int height,
  const Init initialization
)
{
  m_pixmap = QPixmap(width,height);
  m_simulation = ribi::lprss::Simulation(
    width,
    height,
    initialization
  );
  update();
}
