#include "qttestplaneinvestigateaccuracydialog.h"
#include "ui_qttestplaneinvestigateaccuracydialog.h"

QtTestPlaneInvestigateAccuracyDialog::QtTestPlaneInvestigateAccuracyDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestPlaneInvestigateAccuracyDialog)
{
  ui->setupUi(this);
}

QtTestPlaneInvestigateAccuracyDialog::~QtTestPlaneInvestigateAccuracyDialog()
{
  delete ui;
}
