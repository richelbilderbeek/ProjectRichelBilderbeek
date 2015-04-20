#ifndef QTTESTQTBEASTDISPLAY_H
#define QTTESTQTBEASTDISPLAY_H

#include <QDialog>

namespace Ui {
class QtTestQtBeastDisplay;
}

struct QtBeastDisplay;

class QtTestQtBeastDisplay : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestQtBeastDisplay(QWidget *parent = 0);
  QtTestQtBeastDisplay(const QtTestQtBeastDisplay&) = delete;
  QtTestQtBeastDisplay& operator=(const QtTestQtBeastDisplay&) = delete;
  ~QtTestQtBeastDisplay();

private slots:
  void on_edit_newick_returnPressed();

private:
  Ui::QtTestQtBeastDisplay *ui;

  QtBeastDisplay * const m_display;
};

#endif // QTTESTQTBEASTDISPLAY_H
