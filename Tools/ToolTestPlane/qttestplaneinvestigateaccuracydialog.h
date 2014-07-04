#ifndef QTTESTPLANEINVESTIGATEACCURACYDIALOG_H
#define QTTESTPLANEINVESTIGATEACCURACYDIALOG_H

#include <QDialog>

namespace Ui {
  class QtTestPlaneInvestigateAccuracyDialog;
}

class QtTestPlaneInvestigateAccuracyDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestPlaneInvestigateAccuracyDialog(QWidget *parent = 0);
  ~QtTestPlaneInvestigateAccuracyDialog();

private:
  Ui::QtTestPlaneInvestigateAccuracyDialog *ui;
};

#endif // QTTESTPLANEINVESTIGATEACCURACYDIALOG_H
