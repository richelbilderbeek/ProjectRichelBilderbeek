#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestledmodifydialog.h"

#include <boost/make_shared.hpp>

#include <QGridLayout>

#include "led.h"
#include "qtled.h"
#include "qtleddialog.h"

#include "ui_qttestledmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedModifyDialog::QtTestLedModifyDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestLedModifyDialog),
    m_dialog_left(boost::make_shared<QtLedDialog>()),
    m_dialog_right(boost::make_shared<QtLedDialog>()),
    m_led_left(boost::make_shared<QtLed>()),
    m_led_right(boost::make_shared<QtLed>())

{
  ui->setupUi(this);

  {
    assert(!ui->widget_left->layout());
    QGridLayout * const my_layout = new QGridLayout;
    assert(my_layout);
    ui->widget_left->setLayout(my_layout);
    assert(ui->widget_left->layout());
    my_layout->addWidget(m_led_left.get());
  }
  {
    assert(!ui->widget_right->layout());
    QGridLayout * const my_layout = new QGridLayout;
    assert(my_layout);
    ui->widget_right->setLayout(my_layout);
    assert(ui->widget_right->layout());
    my_layout->addWidget(m_led_right.get());
  }
  {
    assert(this->layout());
    auto my_layout = this->layout();
    my_layout->addWidget(m_dialog_left.get());
    my_layout->addWidget(m_dialog_right.get());
  }

  const auto led = boost::make_shared<Led>();
  m_dialog_left->SetLed(led);
  m_dialog_right->SetLed(led);
  m_led_left->SetLed(led);
  m_led_right->SetLed(led);

}

ribi::QtTestLedModifyDialog::~QtTestLedModifyDialog() noexcept
{
  delete ui;
}
