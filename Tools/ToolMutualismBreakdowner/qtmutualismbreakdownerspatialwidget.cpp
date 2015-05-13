#include "qtmutualismbreakdownerspatialwidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "ui_qtmutualismbreakdownerspatialwidget.h"

QtMutualismBreakdownerSpatialWidget::QtMutualismBreakdownerSpatialWidget(
  const int width,
  const int height,
  QWidget *parent
)
  : QWidget(parent),
    ui(new Ui::QtMutualismBreakdownerSpatialWidget),
    m_image(width,height,QImage::Format_RGB32)
{
  ui->setupUi(this);
}

QtMutualismBreakdownerSpatialWidget::~QtMutualismBreakdownerSpatialWidget()
{
  delete ui;
}

void QtMutualismBreakdownerSpatialWidget::SetPixel(const int x, const int y, const QColor color)
{
  m_image.setPixel(x,y,color.rgb());
}

void QtMutualismBreakdownerSpatialWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(
    this->rect(),
    QPixmap::fromImage(m_image)
  );
}
