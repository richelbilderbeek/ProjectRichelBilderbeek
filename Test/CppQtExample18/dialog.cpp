#include "dialog.h"
#include "ui_dialog.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_scene(new QGraphicsScene),
    m_background(new QGraphicsPixmapItem)
{
  ui->setupUi(this);
  ui->graphicsView->setScene(m_scene.get());
  m_scene->addItem(m_background.get());
  m_background->setPixmap(QPixmap(":/images/R.bmp"));
  //Draw image 20x as large
  m_background->setScale(20.0);
  //Rotate image by 30 degree
  m_background->setRotation(30.0);
}

Dialog::~Dialog()
{
  delete ui;
}

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
