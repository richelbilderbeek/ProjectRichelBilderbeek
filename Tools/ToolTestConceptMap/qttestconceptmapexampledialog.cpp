#include "qttestconceptmapexampledialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QLabel>
#include <QKeyEvent>

#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "qtconceptmapexampledialog.h"
#include "ui_qttestconceptmapexampledialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestExampleDialog::QtTestExampleDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestExampleDialog),
  m_example_1{new QtExampleDialog},
  m_example_2{new QtExampleDialog}
{
  ui->setupUi(this);

  {
    assert(this->layout());
    QLabel * const label_1 = new QLabel;
    label_1->setText("#1");
    layout()->addWidget(label_1);

    layout()->addWidget(m_example_1.get());

    QLabel * const label_2 = new QLabel;
    label_2->setText("#2");
    layout()->addWidget(label_2);

    layout()->addWidget(m_example_2.get());
  }

  {
    const int n_tests = ExampleFactory().GetNumberOfTests();
    for (int i=0; i!=n_tests; ++i)
    {
      ui->box_load_example->addItem(boost::lexical_cast<std::string>(i).c_str());
    }
    ui->box_load_example->setCurrentIndex(0);
  }
  on_button_load_example_clicked();
}

ribi::cmap::QtTestExampleDialog::~QtTestExampleDialog()
{
  delete ui;
}

void ribi::cmap::QtTestExampleDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::cmap::QtTestExampleDialog::on_button_load_example_clicked()
{
  const int i = ui->box_load_example->currentIndex();
  assert(i >= 0);
  assert(i < ExampleFactory().GetNumberOfTests());
  const auto example = ExampleFactory().GetTest(i);
  m_example_1->SetExample(example);
  m_example_2->SetExample(example);

  assert(m_example_1->GetExample() == example);
  assert(m_example_2->GetExample() == example);
}
