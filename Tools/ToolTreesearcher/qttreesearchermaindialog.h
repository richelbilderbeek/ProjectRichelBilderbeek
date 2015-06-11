#ifndef QTTREESEARCHERMAINDIALOG_H
#define QTTREESEARCHERMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtTreesearcherMainDialog;
}

struct QLabel;
struct QSvgWidget;
struct RInside;
struct QtBirthDeathModelParametersWidget;

class QtTreesearcherMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTreesearcherMainDialog(QWidget *parent = 0);
  QtTreesearcherMainDialog(const QtTreesearcherMainDialog&) = delete;
  QtTreesearcherMainDialog& operator=(const QtTreesearcherMainDialog&) = delete;
  ~QtTreesearcherMainDialog();

  ///phylogeny must be Newick
  void SetPhylogeny(const std::string& phylogeny);

private:
  Ui::QtTreesearcherMainDialog *ui;

  QtBirthDeathModelParametersWidget * m_bd_parameters_widget;

  QLabel * const m_ltt_image;

  ///The phylogeny created and researched
  std::string m_phylogeny;

  QLabel * const m_tree_image;

private slots:
  void OnBirthDeathParametersChanged();
};

#endif // QTTREESEARCHERMAINDIALOG_H
