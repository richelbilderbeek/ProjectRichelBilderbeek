
#include <cstdlib>
#include <ctime>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/tuple/tuple.hpp>

#include "BigInteger.hh"

#include "binarynewickvector.h"
#include "newick.h"
#include "newickvector.h"
#include "qtaboutdialog.h"
#include "qttestnewickdialog.h"
#include "sortedbinarynewickvector.h"
#include "twodigitnewick.h"
#include "ui_qttestnewickdialog.h"
#pragma GCC diagnostic pop

ribi::QtTestNewickDialog::QtTestNewickDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtTestNewickDialog),
    m_dialog{}
{
  ui->setupUi(this);
  #ifdef NDEBUG
  this->setWindowTitle( this->windowTitle() + " (release)");
  #else
  this->setWindowTitle( this->windowTitle() + " (debug)");
  #endif


  QObject::connect(ui->edit_max_complexity,SIGNAL(textChanged(QString)),
    this,SLOT(on_any_change()));
  QObject::connect(ui->edit_newick,SIGNAL(textChanged(QString)),
    this,SLOT(on_any_change()));
  QObject::connect(ui->edit_theta,SIGNAL(textChanged(QString)),
    this,SLOT(on_any_change()));
  this->on_button_compare_clicked();
}

ribi::QtTestNewickDialog::~QtTestNewickDialog()
{
  delete ui;
}

void ribi::QtTestNewickDialog::Display()
{
  //Display text
  ui->text->clear();
  ui->text->appendPlainText(m_dialog.GetText().c_str());

  //Display table
  const std::vector<TestNewickResult>& table = m_dialog.GetTable();
  const int n_results = boost::numeric_cast<int>(table.size());

  ui->table->clear();
  ui->table->setRowCount(n_results);
  for (int result = 0; result!=n_results; ++result)
  {
    //Newick
    ui->table->setItem(result,0,
      new QTableWidgetItem(QString(
        boost::lexical_cast<std::string>(table[result].newick).c_str())));
    //Theta
    ui->table->setItem(result,1,
      new QTableWidgetItem(QString(
        boost::lexical_cast<std::string>(table[result].theta).c_str())));
    //Test name
    ui->table->setItem(result,2,
      new QTableWidgetItem(QString(
        boost::lexical_cast<std::string>(table[result].test_name).c_str())));
    //Probability
    ui->table->setItem(result,3,
      new QTableWidgetItem(QString(
        boost::lexical_cast<std::string>(table[result].probability).c_str())));
    //Time
    ui->table->setItem(result,4,
      new QTableWidgetItem(QString(
        boost::lexical_cast<std::string>(table[result].time).c_str())));
  }
}

void ribi::QtTestNewickDialog::resizeEvent(QResizeEvent *)
{
  const int n_cols = ui->table->columnCount();
  const int col_width = ui->table->width() / n_cols;
  for (int i=0; i!=n_cols; ++i)
  {
    ui->table->setColumnWidth(i,col_width);
  }
}

void ribi::QtTestNewickDialog::on_button_compare_clicked()
{
  m_dialog.DoCalculate(
    ui->edit_newick->text().toStdString(),
    ui->edit_theta->text().toStdString());
  Display();
}

void ribi::QtTestNewickDialog::on_any_change()
{
  m_dialog.DoAutoCalculate(
    ui->edit_newick->text().toStdString(),
    ui->edit_theta->text().toStdString(),
    ui->edit_max_complexity->text().toStdString());
  Display();
}

void ribi::QtTestNewickDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestNewickDialog::GetAbout());
  d.exec();
}


