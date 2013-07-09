#include "qtdialog.h"

#include <cassert>

#include <QtSql>
#include <QSqlDatabase>
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_database(CreateDatabase())
{
  ui->setupUi(this);

  QSqlTableModel * const model = new QSqlTableModel(this, m_database);
  model->setTable("Animals");

  const bool can_load_data = model->select();
  assert(can_load_data);

  ui->tableView->setModel(model);
  ui->tableView->setSortingEnabled(true);
  ui->tableView->setAlternatingRowColors(true);
  ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
}

QtDialog::~QtDialog()
{
  delete ui;
}

const QSqlDatabase QtDialog::CreateDatabase()
{
  //Create a database
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //Choose from QSQLITE QODBC3 QODBC
  db.setDatabaseName("zoo_database.sqlite");
  const bool ok = db.open();
  assert(ok);

  //Delete the table 'Animals' from a possible previous session
  QSqlQuery("DROP TABLE animals");
  assert(db.tables().empty() && "There must be zero tables at startup");

  //Creata a 'Animals' table
  QSqlQuery("CREATE TABLE Animals (Name TEXT NOT NULL, \"Number of paws\" INT, \"Can fly?\")");
  assert(db.tables().size() == 1 && "Table Animals must have been created");

  //Check that table is empty
  {
    QSqlQuery query("SELECT * FROM Animals");
    //Using QSqlQuery::size is not supported by all drivers, so count the number of rows manually
    int size = 0;
    while (query.next()) { ++size; }
    assert(size == 0 && "Table Animals must be empty directly after its creation");
  }

  //Insert animals
  QSqlQuery("INSERT INTO Animals VALUES (\"Starfish\",5,0)");
  QSqlQuery("INSERT INTO Animals VALUES (\"Duck\",2,1)");
  QSqlQuery("INSERT INTO Animals VALUES (\"Horse\",4,0)");
  QSqlQuery("INSERT INTO Animals VALUES (\"Sponge\",1,0)");

  //Check that table is not empty anymore
  {
    QSqlQuery query("SELECT * FROM Animals");
    //Using QSqlQuery::size is not supported by all drivers, so count the number of rows manually
    int size = 0;
    while (query.next()) { ++size; }
    assert(size == 4 && "Table Animals must contain four animals");
  }

  return db;
}
