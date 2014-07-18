#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtathleticlandmaindialog.h"

#include <cassert>

#include <QKeyEvent>
#include <QGridLayout>

#include "qtathleticlandmainwidget.h"
#include "ui_qtathleticlandmaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::athl::QtAthleticLandMainDialog::QtAthleticLandMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAthleticLandMainDialog),
    m_main_widget{new QtAthleticLandMainWidget}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(!this->layout());
  QLayout * const layout { new QGridLayout };
  layout->setMargin(0);
  this->setLayout(layout);

  layout->addWidget(m_main_widget);

}

ribi::athl::QtAthleticLandMainDialog::~QtAthleticLandMainDialog() noexcept
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

#ifndef NDEBUG
void ribi::athl::QtAthleticLandMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::athl::QtAthleticLandMainDialog::Test");
  QtAthleticLandMainWidget();
  TRACE("Finished ribi::athl::QtAthleticLandMainDialog::Test successfully");
}
#endif
