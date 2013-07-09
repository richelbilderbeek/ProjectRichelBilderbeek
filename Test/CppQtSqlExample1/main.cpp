#include <cassert>
#include <iostream>
#include <QtSql>

int main()
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

  //Display content of PEOPLE on screen
  {
    QSqlQuery query("SELECT * FROM PEOPLE");
    std::cout << "#\tID\tNAME\n";
    int index = 0;
    while (query.next())
    {
      const int id = query.value(0).toInt();
      const std::string name = query.value(1).toString().toStdString();
      std::cout << index << '\t' << id << '\t' << name << '\n';
      ++index;
    }
  }
}

/* Screen output:

#       ID      NAME
0       1       Mr. A
1       2       Ms. B
2       3       Mr. C

*/
