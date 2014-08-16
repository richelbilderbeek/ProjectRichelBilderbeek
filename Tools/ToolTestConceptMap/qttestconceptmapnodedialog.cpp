#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestconceptmapnodedialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QLabel>

#include "conceptmapcompetencies.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapnodedialog.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapnodedialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestNodeDialog::QtTestNodeDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestNodeDialog),
    m_qtnodedialog_1{new QtNodeDialog},
    m_qtnodedialog_2{new QtNodeDialog}
    //m_concept(cmap::ConceptFactory().GetTests().at(1)),
    //m_display_concept(nullptr),
    //m_edit_concept(nullptr),
    //m_rate_concept(nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(layout());

  ui->box_test->setMinimum(0);
  ui->box_test->setMaximum(NodeFactory().GetNumberOfTests() - 1);

  //QGridLayout * const grid_layout = dynamic_cast<QGridLayout*>(layout());
  //QGridLayout * const grid_layout = dynamic_cast<QGridLayout*>(ui->scrollAreaWidgetContents);
  //assert(grid_layout);
  if (!ui->widget_left->layout())
  {
    QLayout * const layout = new QVBoxLayout;
    ui->widget_left->setLayout(layout);

  }
  if (!ui->widget_right->layout())
  {
    QLayout * const layout = new QVBoxLayout;
    ui->widget_right->setLayout(layout);

  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(0);
    QLabel * const label = new QLabel("#1");
    label->setSizePolicy(policy);
    assert(ui->widget_left->layout());
    ui->widget_left->layout()->addWidget(label);
    //grid_layout->addWidget(label,1,0);
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(2);
    m_qtnodedialog_1->setSizePolicy(policy);
    ui->widget_left->layout()->addWidget(m_qtnodedialog_1.get());
    //grid_layout->addWidget(m_qtnodedialog_1.get(),2,0);
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(0);
    QLabel * const label = new QLabel("#2");
    label->setSizePolicy(policy);
    ui->widget_right->layout()->addWidget(label);
    //grid_layout->addWidget(label,1,1);
  }
  {
    QSizePolicy policy;
    policy.setVerticalStretch(2);
    m_qtnodedialog_2->setSizePolicy(policy);
    ui->widget_right->layout()->addWidget(m_qtnodedialog_2.get());
    //grid_layout->addWidget(m_qtnodedialog_2.get(),2,1);
  }

  m_qtnodedialog_1->setMinimumHeight(100);
  m_qtnodedialog_2->setMinimumHeight(100);
  m_qtnodedialog_1->setMinimumWidth(100);
  m_qtnodedialog_2->setMinimumWidth(100);

  ui->box_test->setValue(1);
  on_button_load_clicked();

}

ribi::cmap::QtTestNodeDialog::~QtTestNodeDialog() noexcept
{
  delete ui;
}


void ribi::cmap::QtTestNodeDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtTestNodeDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::cmap::QtTestNodeDialog::on_button_load_clicked()
{
  const int i = ui->box_test->value();
  assert(i >= 0);
  assert(i < NodeFactory().GetNumberOfTests());
  const auto node = NodeFactory().GetTest(i);
  m_qtnodedialog_1->SetNode(node);
  m_qtnodedialog_2->SetNode(node);
  assert(m_qtnodedialog_1->GetNode() == node);
  assert(m_qtnodedialog_2->GetNode() == node);
  m_qtnodedialog_1->repaint();
  m_qtnodedialog_2->repaint();
}
