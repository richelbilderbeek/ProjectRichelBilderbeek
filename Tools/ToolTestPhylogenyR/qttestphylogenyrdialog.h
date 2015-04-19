#ifndef QTTESTPHYLOGENYRDIALOG_H
#define QTTESTPHYLOGENYRDIALOG_H

#include <QDialog>

namespace Ui {
class QtTestPhylogenyRdialog;
}

class QtTestPhylogenyRdialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestPhylogenyRdialog(QWidget *parent = 0);
  QtTestPhylogenyRdialog(const QtTestPhylogenyRdialog&) = delete;
  QtTestPhylogenyRdialog& operator=(const QtTestPhylogenyRdialog&) = delete;
  ~QtTestPhylogenyRdialog();
  std::string GetNewick() const noexcept;

private slots:
  void on_button_show_clicked();

private:
  Ui::QtTestPhylogenyRdialog *ui;

  void DisplayNewick(const std::string& newick);
  void DisplayNewickExtant(const std::string& newick);
  void DisplayNewickToPhylogenyPng(const std::string& newick);
  void DisplayNewickToPhylogenyExtantPng(const std::string& newick);
  void DisplayNewickToLttPlot(const std::string& newick);
  void DisplayNewickToLttPlotExtant(const std::string& newick);
};

#endif // QTTESTPHYLOGENYRDIALOG_H
