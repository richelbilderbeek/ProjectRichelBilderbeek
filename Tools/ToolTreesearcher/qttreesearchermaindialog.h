#ifndef QTTREESEARCHERMAINDIALOG_H
#define QTTREESEARCHERMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtTreesearcherMainDialog;
}

struct QSvgWidget;
struct RInside;

class QtTreesearcherMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTreesearcherMainDialog(QWidget *parent = 0);
  QtTreesearcherMainDialog(const QtTreesearcherMainDialog&) = delete;
  QtTreesearcherMainDialog& operator=(const QtTreesearcherMainDialog&) = delete;
  ~QtTreesearcherMainDialog();

private:
  Ui::QtTreesearcherMainDialog *ui;

  QSvgWidget * const m_svg_widget;
};

#endif // QTTREESEARCHERMAINDIALOG_H
