#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtthresholdfilterermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QFileDialog>
#include <QLabel>

#include "thresholdfilterermaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtthresholdfilterermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtThresholdFiltererMainDialog::QtThresholdFiltererMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtThresholdFiltererMainDialog),
    m_source{nullptr},
    m_target{nullptr}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

}

ribi::QtThresholdFiltererMainDialog::~QtThresholdFiltererMainDialog() noexcept
{
  delete ui;
}

void ribi::QtThresholdFiltererMainDialog::on_button_load_clicked()
{
  const std::string filename {
    QFileDialog::getOpenFileName(0,"Please select a file").toStdString()
  };
  if (filename.empty()) return;

  //Check if the pixmap is valid
  {
    const QPixmap pixmap(filename.c_str());
    if (pixmap.isNull()) return;
  }
  //Refresh source
  if (m_source)
  {
    delete m_source;
    m_source = nullptr;
  }
  assert(!m_source);
  m_source = new QPixmap(filename.c_str());
  assert(m_source);
  assert(!m_source->isNull());

  //Refresh target
  {
    if (ui->contents->layout())
    {
      delete m_target;
      m_target = nullptr;
      delete ui->contents->layout();
    }
    assert(!ui->contents->layout());

    QVBoxLayout * const layout = new QVBoxLayout;
    ui->contents->setLayout(layout);
    m_target = new QLabel;
    layout->addWidget(m_target);

    const int pixel_size { ui->pixels->value() };

    const QPixmap target {
      ThresholdFiltererMainDialog::DoThresholdFiltering(*m_source,pixel_size)
    };
    assert(!target.isNull());
    m_target->setPixmap(target);
  }
}

void ribi::QtThresholdFiltererMainDialog::on_button_save_clicked()
{
  const std::string filename {
    QFileDialog::getSaveFileName(0,"Please name the target file").toStdString()
  };
  if (filename.empty()) return;

  m_target->pixmap()->save(filename.c_str());
}

#ifndef NDEBUG
void ribi::QtThresholdFiltererMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QPixmap source(":/thresholdfilterer/images/ToolThresholdFiltererTest.png");
  assert(!source.isNull());
  assert(source.width() > 0);
  assert(source.height() > 0);
  const int max = source.width() + 1; //Be nasty
  for (int pixel_size = 1; pixel_size != max; ++pixel_size)
  {
    const QPixmap target {
      ThresholdFiltererMainDialog::DoThresholdFiltering(source,pixel_size)
    };
    assert(!target.isNull());
    assert(target.width() > 0);
    assert(target.height() > 0);
  }
}
#endif

void ribi::QtThresholdFiltererMainDialog::on_pixels_valueChanged(int value)
{
  const int pixel_size { value };

  const QPixmap target {
    ThresholdFiltererMainDialog::DoThresholdFiltering(*m_source,pixel_size)
  };
  assert(!target.isNull());
  m_target->setPixmap(target);
}
