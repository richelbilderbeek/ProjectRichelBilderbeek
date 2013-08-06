#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtk3opeenrijmenudialog.h"

#include "k3opeenrijmenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreewidget.h"
#include "qtk3opeenrijresources.h"
#include "qtk3opeenrijinstructionsdialog.h"
#include "qtk3opeenrijselectplayerwidget.h"
#include "ui_qtk3opeenrijmenudialog.h"

QtK3OpEenRijMenuDialog::QtK3OpEenRijMenuDialog(
  const boost::shared_ptr<const QtK3OpEenRijResources> resources,
  QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtK3OpEenRijMenuDialog),
    m_select(new QtK3OpEenRijSelectPlayerWidget(resources))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout_horizontal->addWidget(m_select.get());
}

QtK3OpEenRijMenuDialog::~QtK3OpEenRijMenuDialog()
{
  delete ui;
}

#ifndef NDEBUG
void QtK3OpEenRijMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const boost::shared_ptr<const QtK3OpEenRijResources> resources(new QtK3OpEenRijResources);
  QtConnectThreeGameDialog d(resources,nullptr,std::bitset<3>(false));
}
#endif

void QtK3OpEenRijMenuDialog::on_button_start_clicked()
{
  //Supply the correct resources, depending on if player 3 chose Kathleen or Josje
  const boost::shared_ptr<QtK3OpEenRijResources> resources(
    new QtK3OpEenRijResources(m_select->GetIsPlayer3Kathleen()));

  QtConnectThreeGameDialog d(
    resources,
    nullptr,this->
    m_select->GetIsPlayerHuman());
  d.setWindowTitle("K3OpEenRij (C) 2007-2013");
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void QtK3OpEenRijMenuDialog::on_button_about_clicked()
{
  About about = K3OpEenRijMenuDialog::GetAbout();
  about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void QtK3OpEenRijMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtK3OpEenRijMenuDialog::on_button_instructions_clicked()
{
  QtK3OpEenRijInstructionsDialog d;
  this->ShowChild(&d);
}
