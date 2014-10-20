#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtimagerotatermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QFileDialog>
#include <QLabel>

#include "imagerotatermaindialog.h"
#include "trace.h"
#include "plane.h"
#include "testtimer.h"
#include "ui_qtimagerotatermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtImageRotaterMainDialog::QtImageRotaterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtImageRotaterMainDialog),
    m_source(":/imagerotater/images/ToolImageRotaterTest.png"),
    m_target(nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(!m_source.isNull());
  OnAnyChange();
}

ribi::QtImageRotaterMainDialog::~QtImageRotaterMainDialog() noexcept
{
  delete ui;
}

double ribi::QtImageRotaterMainDialog::GetAngle() const noexcept
{
  assert(ui->dial_angle->minimum() == 0);
  const double f {
      static_cast<double>(ui->dial_angle->value())
    / static_cast<double>(ui->dial_angle->maximum())
  };
  const double angle = f * boost::math::constants::two_pi<double>();
  return angle;
}

void ribi::QtImageRotaterMainDialog::on_button_load_clicked()
{
  const std::string filename {
    QFileDialog::getOpenFileName(0,"Please select a file").toStdString()
  };
  if (filename.empty()) return;

  //Check if the pixmap is valid
  const QImage image(filename.c_str());
  if (image.isNull()) return;
  m_source = image;
  OnAnyChange();
}

void ribi::QtImageRotaterMainDialog::OnAnyChange()
{
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
    m_target->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout->addWidget(m_target);

    assert(!m_source.isNull());
    QImage target(m_source);
    ImageRotaterMainDialog::Rotate(
      m_source,
      target,
      GetAngle()
    );
    assert(!target.isNull());
    m_target ->setPixmap(QPixmap::fromImage(target));
  }
}

void ribi::QtImageRotaterMainDialog::on_button_save_clicked()
{
  const std::string filename {
    QFileDialog::getSaveFileName(0,"Please name the target file").toStdString()
  };
  if (filename.empty()) return;

  m_target->pixmap()->save(filename.c_str());
}

#ifndef NDEBUG
void ribi::QtImageRotaterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const Plane::Coordinat3D p1( 1.0, 2.0,3.0);
    const Plane::Coordinat3D p2( 4.0, 6.0,9.0);
    const Plane::Coordinat3D p3(12.0,11.0,9.0);
    const boost::shared_ptr<Plane> p(
      boost::make_shared<Plane>(p1,p2,p3)
    );
    assert(p);
  }
  ImageRotaterMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const QImage source(":/imagerotater/images/ToolImageRotaterTest.png");
  assert(!source.isNull());
  QImage target(source);
  ImageRotaterMainDialog::Rotate(
    source,
    target,
    0.235
  );
  assert(!target.isNull());
  assert(target != source
    && "Images do not look identical after rotation");
}
#endif

void ribi::QtImageRotaterMainDialog::on_dial_angle_sliderMoved(int )
{
  OnAnyChange();
}
