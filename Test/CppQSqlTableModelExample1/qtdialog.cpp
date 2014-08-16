#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtdialog.h"

#include <cassert>

#include <QtSql>
#include <QSqlDatabase>
#include "ui_qtdialog.h"
#pragma GCC diagnostic pop

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_database(CreateDatabase())
{
  ui->setupUi(this);

  QSqlTableModel * const model = new QSqlTableModel(this, m_database);
  model->setTable("PEOPLE");

  const bool can_load_data = model->select();
  assert(can_load_data);

  ui->tableView->setModel(model);
}

QtDialog::~QtDialog()
{
  delete ui;
}

const QSqlDatabase QtDialog::CreateDatabase()
{
  //Create a database
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //Choose from QSQLITE QODBC3 QODBC
  db.setDatabaseName("MY_DATABASE");
  const bool ok = db.open();
  assert(ok);

  //Delete the table 'PEOPLE' from a possible previous session
  QSqlQuery("DROP TABLE PEOPLE");
  assert(db.tables().empty() && "There must be zero tables at startup");

  //Creata a 'PEOPLE' table
  QSqlQuery("CREATE TABLE PEOPLE (ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL)");
  assert(db.tables().size() == 1 && "Table PEOPLE must have been created");

  //Check that table is empty
  {
    QSqlQuery query("SELECT * FROM PEOPLE");
    //Using QSqlQuery::size is not supported by all drivers, so count the number of rows manually
    int size = 0;
    while (query.next()) { ++size; }
    assert(size == 0 && "Table PEOPLE must be empty directly after its creation");
  }

  //Insert people
  QSqlQuery("INSERT INTO PEOPLE VALUES (1,\"Mr. A\")");
  QSqlQuery("INSERT INTO PEOPLE VALUES (2,\"Ms. B\")");
  QSqlQuery("INSERT INTO PEOPLE VALUES (3,\"Mr. C\")");

  //Check that table is not empty anymore
  {
    QSqlQuery query("SELECT * FROM PEOPLE");
    //Using QSqlQuery::size is not supported by all drivers, so count the number of rows manually
    int size = 0;
    while (query.next()) { ++size; }
    assert(size == 3 && "Table PEOPLE must contain three persons");
  }

  return db;
}
