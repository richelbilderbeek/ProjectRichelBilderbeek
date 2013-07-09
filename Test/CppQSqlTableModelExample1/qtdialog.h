#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
  class QtDialog;
}

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private:
  Ui::QtDialog *ui;
  QSqlDatabase m_database;

  static const QSqlDatabase CreateDatabase();
};

#endif // QTDIALOG_H
