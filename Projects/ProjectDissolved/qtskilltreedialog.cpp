#include "qtskilltreedialog.h"
#include "ui_qtskilltreedialog.h"

QtSkillTreeDialog::QtSkillTreeDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtSkillTreeDialog)
{
  ui->setupUi(this);
}

QtSkillTreeDialog::~QtSkillTreeDialog()
{
  delete ui;
}
