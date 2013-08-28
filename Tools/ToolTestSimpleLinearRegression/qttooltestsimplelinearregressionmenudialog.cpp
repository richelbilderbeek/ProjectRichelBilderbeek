//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestsimplelinearregressionmenudialog.h"

#include <boost/units/systems/si.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "simplelinearregression.h"
#include "tooltestsimplelinearregressionmenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestsimplelinearregressionmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestsimplelinearregressionmenudialog.h"

QtToolTestSimpleLinearRegressionMenuDialog::QtToolTestSimpleLinearRegressionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestSimpleLinearRegressionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtToolTestSimpleLinearRegressionMenuDialog::~QtToolTestSimpleLinearRegressionMenuDialog()
{
  delete ui;
}

void QtToolTestSimpleLinearRegressionMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_about_clicked()
{
  About a = ToolTestSimpleLinearRegressionMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_start_clicked()
{
  QtToolTestSimpleLinearRegressionMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestSimpleLinearRegressionMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolTestSimpleLinearRegressionMenuDialog::Test");
  QtToolTestSimpleLinearRegressionMainDialog();
  //Let Boost.Units check for compiling
  {
    typedef boost::units::quantity<boost::units::si::time> Time;
    typedef boost::units::quantity<boost::units::si::length> Distance;
    typedef boost::units::quantity<boost::units::si::velocity> Velocity;
    const std::vector<Time> xs
      =
      {
        Time(1.0 * boost::units::si::second),
        Time(2.0 * boost::units::si::second),
        Time(3.0 * boost::units::si::second)
      };
    const std::vector<Distance> ys
      =
      {
        Distance(2.0 * boost::units::si::meter),
        Distance(3.0 * boost::units::si::meter),
        Distance(4.0 * boost::units::si::meter)
      };

    const Velocity expected_slope(1.0 * boost::units::si::meter / boost::units::si::second);
    const Distance expected_offset(1.0 * boost::units::si::meter);

    const std::pair<Velocity,Distance> p
      = SimpleLinearRegression::CalculateBestFit(xs,ys);
    const Velocity slope(p.first);
    const Distance offset(p.second);
    assert(std::abs( Velocity(slope - expected_slope).value() )
      < Velocity(0.0001 * boost::units::si::meter / boost::units::si::second).value() );
    assert(std::abs( Distance(offset - expected_offset).value() )
      < Distance(0.0001 * boost::units::si::meter).value() );

  }

  TRACE("Finished QtToolTestSimpleLinearRegressionMenuDialog::Test successfully");
}
#endif
