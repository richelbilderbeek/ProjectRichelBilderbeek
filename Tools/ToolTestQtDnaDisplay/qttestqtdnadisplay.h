#ifndef QTTESTQTDNADISPLAY_H
#define QTTESTQTDNADISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtDnaDisplay;
}

struct QtDnaDisplay;

class QtTestQtDnaDisplay : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQtDnaDisplay(QWidget *parent = 0);
  QtTestQtDnaDisplay(const QtTestQtDnaDisplay&) = delete;
  QtTestQtDnaDisplay& operator=(const QtTestQtDnaDisplay&) = delete;
  ~QtTestQtDnaDisplay();


private slots:

private:
  Ui::QtTestQtDnaDisplay *ui;

  QtDnaDisplay * const m_display;
};

#endif // QTTESTQTDNADISPLAY_H
