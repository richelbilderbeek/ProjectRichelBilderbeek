#ifndef QTSKILLTREEDIALOG_H
#define QTSKILLTREEDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSkillTreeDialog;
}

class QtSkillTreeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtSkillTreeDialog(QWidget *parent = 0);
  ~QtSkillTreeDialog();

private:
  Ui::QtSkillTreeDialog *ui;
};

#endif // QTSKILLTREEDIALOG_H
