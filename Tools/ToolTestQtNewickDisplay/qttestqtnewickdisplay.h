#ifndef QTTESTQTNEWICKDISPLAY_H
#define QTTESTQTNEWICKDISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtNewickDisplay;
}

struct QtNewickDisplay;

class QtTestQtNewickDisplay : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQtNewickDisplay(QWidget *parent = 0);
  QtTestQtNewickDisplay(const QtTestQtNewickDisplay&) = delete;
  QtTestQtNewickDisplay& operator=(const QtTestQtNewickDisplay&) = delete;
  ~QtTestQtNewickDisplay();

private slots:
  void on_edit_newick_returnPressed();

private:
  Ui::QtTestQtNewickDisplay *ui;

  QtNewickDisplay * const m_display;
};

#endif // QTTESTQTNEWICKDISPLAY_H
