#ifndef QTBIRTHDEATHMODELLIKELIHOODWIDGET_H
#define QTBIRTHDEATHMODELLIKELIHOODWIDGET_H

#include <QWidget>

namespace Ui {
class QtBirthDeathModelLikelihoodWidget;
}

class QtBirthDeathModelLikelihoodWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBirthDeathModelLikelihoodWidget(QWidget *parent = 0);
  QtBirthDeathModelLikelihoodWidget(const QtBirthDeathModelLikelihoodWidget&) = delete;
  QtBirthDeathModelLikelihoodWidget operator=(const QtBirthDeathModelLikelihoodWidget&) = delete;
  ~QtBirthDeathModelLikelihoodWidget();
  void SetPhylogeny(const std::string& phylogeny);

private:
  Ui::QtBirthDeathModelLikelihoodWidget *ui;
  std::string m_phylogeny;

private slots:
  void OnParameterChanged();
};

#endif // QTBIRTHDEATHMODELLIKELIHOODWIDGET_H
