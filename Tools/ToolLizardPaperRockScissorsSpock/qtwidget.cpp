#include "qtwidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "simulation.h"
#include "ui_qtwidget.h"

QtWidget::QtWidget(
  const int width,
  const int height,
  QWidget *parent
)
  : QWidget(parent),
    ui(new Ui::QtWidget),
    m_pixmap{QPixmap(width,height)},
    m_simulation{Simulation(width,height)}
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

QtWidget::~QtWidget()
{
  delete ui;
}

void QtWidget::OnTimer()
{
  using CellType = LizardPaperRockScissorsSpock;

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
      const int mid{0};
      const int high{255};
      switch (celltype)
      {
        case CellType::lizard: color = qRgb(high,mid,mid); break;
        case CellType::paper: color = qRgb(mid,high,mid); break;
        case CellType::rock: color = qRgb(mid,high,high); break;
        case CellType::scissors: color = qRgb(high,mid,high); break;
        case CellType::spock: color = qRgb(high,high,mid); break;
      }
      image.setPixel(x,y,color);
    }
  }
  m_pixmap = QPixmap::fromImage(image);
  update();
}

void QtWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    m_pixmap
  );
}
