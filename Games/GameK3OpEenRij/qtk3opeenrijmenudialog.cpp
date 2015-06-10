#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtk3opeenrijmenudialog.h"

#include "k3opeenrijmenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreewidget.h"
#include "qtk3opeenrijresources.h"
#include "qtk3opeenrijinstructionsdialog.h"
#include "testtimer.h"
#include "qtk3opeenrijselectplayerwidget.h"
#include "ui_qtk3opeenrijmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtK3OpEenRijMenuDialog::QtK3OpEenRijMenuDialog(
  const boost::shared_ptr<const QtK3OpEenRijResources> resources,
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtK3OpEenRijMenuDialog),
    m_select(new QtK3OpEenRijSelectPlayerWidget(resources)),
    m_resources{resources}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout_horizontal->addWidget(m_select.get());
}

ribi::QtK3OpEenRijMenuDialog::~QtK3OpEenRijMenuDialog() noexcept
{
  delete ui;

  //Clean up all resources
  m_resources->RemoveFiles();
}

void ribi::QtK3OpEenRijMenuDialog::on_button_about_clicked() noexcept
{
  About about = K3OpEenRijMenuDialog().GetAbout();
  about.AddLibrary("QtConnectThreeWidget version: " + con3::QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtK3OpEenRijMenuDialog::on_button_instructions_clicked() noexcept
{
  QtK3OpEenRijInstructionsDialog d;
  this->ShowChild(&d);
}

void ribi::QtK3OpEenRijMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtK3OpEenRijMenuDialog::on_button_start_clicked() noexcept
{
  //Supply the correct resources, depending on if player 3 chose Kathleen or Josje
  const boost::shared_ptr<QtK3OpEenRijResources> resources(
    new QtK3OpEenRijResources(
      m_select->GetIsPlayer3Kathleen()
      ? Tribool::True
      : Tribool::False
    )
  );

  con3::QtConnectThreeGameDialog d(
    resources,
    nullptr,
    m_select->GetIsPlayerHuman()
  );
  d.setWindowTitle("K3OpEenRij");
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtK3OpEenRijMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const boost::shared_ptr<const QtK3OpEenRijResources> resources(new QtK3OpEenRijResources);
    con3::QtConnectThreeWidget widget(resources);
    con3::QtConnectThreeGameDialog d(resources,nullptr,std::bitset<3>(false));
  }
  {
    QtK3OpEenRijInstructionsDialog d;
  }
  {
    About about = K3OpEenRijMenuDialog().GetAbout();
    QtAboutDialog d(about);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
