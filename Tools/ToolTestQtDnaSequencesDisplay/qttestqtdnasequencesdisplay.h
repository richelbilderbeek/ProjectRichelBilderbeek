#ifndef QTTESTQTDNADISPLAY_H
#define QTTESTQTDNADISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtDnaSequencesDisplay;
}

struct QtDnaSequencesDisplay;

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

private:
  Ui::QtTestQtDnaSequencesDisplay *ui;

  QtDnaSequencesDisplay * const m_display;
};

#endif // QTTESTQTDNADISPLAY_H
