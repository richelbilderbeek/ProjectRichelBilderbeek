#ifndef QTBIRTHDEATHMODELMAXLIKELIHOODWIDGET_H
#define QTBIRTHDEATHMODELMAXLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtBirthDeathModelMaxLikelihoodWidget;
}

class QtBirthDeathModelMaxLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBirthDeathModelMaxLikelihoodWidget(QWidget *parent = 0);
  QtBirthDeathModelMaxLikelihoodWidget(const QtBirthDeathModelMaxLikelihoodWidget&) = delete;
  QtBirthDeathModelMaxLikelihoodWidget operator=(const QtBirthDeathModelMaxLikelihoodWidget&) = delete;
  ~QtBirthDeathModelMaxLikelihoodWidget();
  void SetPhylogeny(const std::string& phylogeny);

private:
  Ui::QtBirthDeathModelMaxLikelihoodWidget *ui;
  std::string m_phylogeny;
};

#endif // QTBIRTHDEATHMODELMAXLIKELIHOODWIDGET_H
