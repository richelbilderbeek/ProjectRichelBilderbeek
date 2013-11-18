#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtathleticlandmaindialog.h"

#include <cassert>

#include <QKeyEvent>
#include <QGridLayout>

#include "qtathleticlandmainwidget.h"
#include "ui_qtathleticlandmaindialog.h"
#pragma GCC diagnostic pop

ribi::athl::QtAthleticLandMainDialog::QtAthleticLandMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAthleticLandMainDialog),
    m_main_widget{new QtAthleticLandMainWidget}
{
  ui->setupUi(this);

  assert(!this->layout());
  QLayout * const layout { new QGridLayout };
  layout->setMargin(0);
  this->setLayout(layout);

  layout->addWidget(m_main_widget);

}

ribi::athl::QtAthleticLandMainDialog::~QtAthleticLandMainDialog()
{
  delete ui;
}

void ribi::athl::QtAthleticLandMainDialog::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Left:
      m_main_widget->OnKeyPress(QtAthleticLandMainWidget::Key::left);
      break;
    case Qt::Key_Right:
      m_main_widget->OnKeyPress(QtAthleticLandMainWidget::Key::right);
      break;
  }
}
