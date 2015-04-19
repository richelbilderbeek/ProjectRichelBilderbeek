#ifndef QTFISHERWRIGHTERMAINDIALOG_H
#define QTFISHERWRIGHTERMAINDIALOG_H

#include <QDialog>
#include "parameters.h"

namespace Ui {
  class QtFisherWrighterMainDialog;
}

class QtFisherWrighterMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtFisherWrighterMainDialog(QWidget *parent = 0);
  ~QtFisherWrighterMainDialog();

private slots:
  void on_button_run_clicked();

  void on_button_run_next_clicked();

private:
  Ui::QtFisherWrighterMainDialog *ui;
  int ReadNumberOfGenerations() const noexcept;

  void DisplayNewick(const std::string& newick) noexcept;
  void DisplayNewickExtant(const std::string& newick) noexcept;
  void DisplayNewickToLttPlot(const std::string& newick) noexcept;
  void DisplayNewickToLttPlotExtant(const std::string& newick) noexcept;
  void DisplayPhylogenyNewickUtilsAll(const std::string& newick) noexcept;
  void DisplayPhylogenyNewickUtilsExtant(const std::string& newick) noexcept;
  void DisplayPhylogenyRall(const std::string& newick) noexcept;
  void DisplayPhylogenyRextant(const std::string& newick) noexcept;

};

#endif // QTFISHERWRIGHTERMAINDIALOG_H
