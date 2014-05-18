#include "qtconceptmaptestexampledialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include <boost/lexical_cast.hpp>

#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "qtconceptmapexampledialog.h"
#include "ui_qtconceptmaptestexampledialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestExampleDialog::QtConceptMapTestExampleDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtConceptMapTestExampleDialog),
  m_example_dialog{new QtExampleDialog}
{
  ui->setupUi(this);

  assert(this->layout());
  layout()->addWidget(m_example_dialog.get());

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

ribi::cmap::QtConceptMapTestExampleDialog::~QtConceptMapTestExampleDialog()
{
  delete ui;
}


void ribi::cmap::QtConceptMapTestExampleDialog::on_button_load_example_clicked()
{
  const int i = ui->box_load_example->currentIndex();
  assert(i >= 0);
  assert(i < ExampleFactory().GetNumberOfTests());
  const auto example = ExampleFactory().GetTest(i);
  m_example_dialog->SetExample(example);

  assert(m_example_dialog->GetExample() == example);
}
