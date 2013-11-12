#ifndef QTNSANABROSOPTIONSDIALOG_H
#define QTNSANABROSOPTIONSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtNsanaBrosOptionsDialog;
}

namespace ribi {

struct NsanaBrosOptions;
struct NsanaBrosOptionsDialog;

class QtNsanaBrosOptionsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtNsanaBrosOptionsDialog(
    const NsanaBrosOptions * const options = 0,
    QWidget *parent = 0);
  QtNsanaBrosOptionsDialog(const QtNsanaBrosOptionsDialog&) = delete;
  QtNsanaBrosOptionsDialog& operator=(const QtNsanaBrosOptionsDialog&) = delete;
  ~QtNsanaBrosOptionsDialog();

private:
  Ui::QtNsanaBrosOptionsDialog *ui;
  boost::scoped_ptr<NsanaBrosOptionsDialog> m_dialog;
};

} //~namespace ribi

#endif // QTNSANABROSOPTIONSDIALOG_H
