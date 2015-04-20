#ifndef QTTESTQTDNADISPLAY_H
#define QTTESTQTDNADISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtDnaSequencesDisplay;
}

struct QtDnaSequencesDialog;
struct QtDnaSequencesDisplay;

namespace ribi { struct DnaSequence; }

class QtTestQtDnaSequencesDisplay : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQtDnaSequencesDisplay(QWidget *parent = 0);
  QtTestQtDnaSequencesDisplay(const QtTestQtDnaSequencesDisplay&) = delete;
  QtTestQtDnaSequencesDisplay& operator=(const QtTestQtDnaSequencesDisplay&) = delete;
  ~QtTestQtDnaSequencesDisplay();


private slots:

  void on_button_display_clicked();

  void on_button_fasta_clicked();

private:
  Ui::QtTestQtDnaSequencesDisplay *ui;

  ///Input of DNA sequences
  QtDnaSequencesDialog * const m_dialog;

  ///Analysis of DNA sequences
  QtDnaSequencesDisplay * const m_display;

  std::vector<ribi::DnaSequence> GetSequences() const noexcept;
};

#endif // QTTESTQTDNADISPLAY_H
