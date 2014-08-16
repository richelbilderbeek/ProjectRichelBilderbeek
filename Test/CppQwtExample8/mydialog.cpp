#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "mydialog.h"

#include <cassert>

#include <QGridLayout>
#include <QKeyEvent>
#include "myplot.h"

#include "ui_mydialog.h"
#pragma GCC diagnostic pop

MyDialog::MyDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MyDialog),
  m_plot(new MyPlot(this))
{
  ui->setupUi(this);

  assert(!this->layout());
  QGridLayout * const my_layout = new QGridLayout;
  this->setLayout(my_layout);
  my_layout->addWidget(m_plot);

  m_plot->showSpectrogram(true);
  m_plot->showContour(true);
}

MyDialog::~MyDialog()
{
  delete ui;
}

void MyDialog::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_plot->showSpectrogram(true); break;
    case Qt::Key_Down: m_plot->showSpectrogram(false); break;
    case Qt::Key_Right: m_plot->showContour(true); break;
    case Qt::Key_Left: m_plot->showContour(false); break;
    case Qt::Key_Escape: close(); return;
  }
}
