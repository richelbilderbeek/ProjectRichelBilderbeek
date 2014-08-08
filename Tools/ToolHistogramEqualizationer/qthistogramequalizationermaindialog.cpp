#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthistogramequalizationermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QFileDialog>
#include <QLabel>

#include "histogramequalizationermaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qthistogramequalizationermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtHistogramEqualizationerMainDialog::QtHistogramEqualizationerMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtHistogramEqualizationerMainDialog),
    m_target(nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtHistogramEqualizationerMainDialog::~QtHistogramEqualizationerMainDialog() noexcept
{
  delete ui;
}

void ribi::QtHistogramEqualizationerMainDialog::on_button_load_clicked()
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

    const QImage source(filename.c_str());
    assert(!source.isNull());
    const QImage target {
      HistogramEqualizationerMainDialog::DoHistogramEqualization(source)
    };
    assert(!target.isNull());
    m_target->setPixmap( QPixmap::fromImage(target) );
    m_target->setAlignment(Qt::AlignCenter);
  }
}

void ribi::QtHistogramEqualizationerMainDialog::on_button_save_clicked()
{
  const std::string filename {
    QFileDialog::getSaveFileName(0,"Please name the target file").toStdString()
  };
  if (filename.empty()) return;

  m_target->pixmap()->save(filename.c_str());
}

#ifndef NDEBUG
void ribi::QtHistogramEqualizationerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const QImage source(":/histogramequalizationer/images/ToolHistogramEqualizationerTest.png");
  assert(!source.isNull());
  const QImage target {

    HistogramEqualizationerMainDialog::DoHistogramEqualization(source)
  };
  assert(!target.isNull());
  assert(target != source);
  const QImage target_again {
    HistogramEqualizationerMainDialog::DoHistogramEqualization(source)
  };
  assert(!target_again.isNull());
  assert(target == target_again
    && "A second histogram equalization will result in the original");
}
#endif
