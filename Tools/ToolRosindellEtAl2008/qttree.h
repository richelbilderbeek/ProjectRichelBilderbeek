#ifndef QTTREE_H
#define QTTREE_H

#include <QWidget>
#include "tree.h"
#include "rng.h"

namespace Ui {
  class QtTree;
}

class QtTree : public QWidget
{
  Q_OBJECT

public:
  explicit QtTree(QWidget *parent = 0);
  ~QtTree();

  int GetDispersalDistance() const noexcept;
  DispersalKernel GetDispersalKernel() const noexcept;
  int GetLength() const noexcept;
  double GetMinSpeciationRate() const noexcept;
  double GetTolerance() const noexcept;
  Rng GetRng() const noexcept;
  int GetRngSeed() const noexcept;
  Rng::Type GetRngType() const noexcept;
  int GetWidth() const noexcept;

private slots:
  void on_button_start_clicked();

  void on_button_next_clicked();

private:
  Ui::QtTree *ui;

  Rng * m_rng;
  Tree * m_tree;
  std::string m_log;

  void DisplayTree();
};

#endif // QTTREE_H
