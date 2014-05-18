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
  QDialog(parent),
  ui(new Ui::QtConceptMapTestExampleDialog)
{
  ui->setupUi(this);

  {
    const int n_tests = ExampleFactory().GetNumberOfTests();
    for (int i=0; i!=n_tests; ++i)
    {
      ui->box_load_example->addItem(boost::lexical_cast<std::string>(i).c_str());
    }
  }
}

ribi::cmap::QtConceptMapTestExampleDialog::~QtConceptMapTestExampleDialog()
{
  delete ui;
}


void ribi::cmap::QtConceptMapTestExampleDialog::on_button_load_example_clicked()
{
  //
}
