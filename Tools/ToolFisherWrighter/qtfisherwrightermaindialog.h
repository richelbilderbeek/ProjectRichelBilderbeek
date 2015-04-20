#ifndef QTFISHERWRIGHTERMAINDIALOG_H
#define QTFISHERWRIGHTERMAINDIALOG_H

#include <vector>
#include <QDialog>
#include "parameters.h"

namespace Ui {
  class QtFisherWrighterMainDialog;
}

struct QtNewickDisplay;
struct QtDnaSequencesDisplay;
struct QtBeastDisplay;

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

  ///Displays the result of the BEAST analysis
  QtBeastDisplay * const m_beast_display;

  ///Displays the resulting DnaSequences
  QtDnaSequencesDisplay * const m_dna_sequences_display;

  ///Displays the resulting Newick
  QtNewickDisplay * const m_newick_display;

  int ReadNumberOfGenerations() const noexcept;
};

#endif // QTFISHERWRIGHTERMAINDIALOG_H
