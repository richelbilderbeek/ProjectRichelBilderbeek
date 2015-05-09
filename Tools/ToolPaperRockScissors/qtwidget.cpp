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
  m_simulation.Next();

  const int height{m_pixmap.height()};
  const int width{m_pixmap.width()};
  QImage image(width,height,QImage::Format_RGB32);
  const auto& grid = m_simulation.GetGrid();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const CellType celltype = grid[y][x];
      auto color = qRgb(0,0,0);
      switch (celltype)
      {
        case CellType::paper: color = qRgb(255,255,255); break;
        case CellType::rock: color = qRgb(0,0,0); break;
        case CellType::scissors: color = qRgb(128,128,128); break;
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
