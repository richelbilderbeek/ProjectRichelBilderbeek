#ifndef QTTESTQTBEASTDISPLAY_H
#define QTTESTQTBEASTDISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtBeastDisplay;
}

struct QtBeastDisplay;
struct QtDnaSequencesDialog;

class QtTestQtBeastDisplay : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQtBeastDisplay(QWidget *parent = 0);
  QtTestQtBeastDisplay(const QtTestQtBeastDisplay&) = delete;
  QtTestQtBeastDisplay& operator=(const QtTestQtBeastDisplay&) = delete;
  ~QtTestQtBeastDisplay();

private slots:

  void on_button_run_clicked();

private:
  Ui::QtTestQtBeastDisplay *ui;

  QtBeastDisplay * const m_beast_output;
  QtDnaSequencesDialog * const m_dna_sequences_input;
};

#endif // QTTESTQTBEASTDISPLAY_H
