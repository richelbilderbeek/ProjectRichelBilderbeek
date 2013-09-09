#ifndef QTKALMANFILTERERPARAMETERDIALOG
#define QTKALMANFILTERERPARAMETERDIALOG

#include <vector>

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
  class QtKalmanFiltererParameterDialog;
}

namespace ribi {
namespace kalman {

///Dialog for a parameter, stores a QtKalmanFiltererParameterDialog::ValueType
class QtKalmanFiltererParameterDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFiltererParameterDialog(
    const std::string& parameter_name,
    const std::string& parameter_description,
    QAbstractTableModel * const model,
    QWidget *parent = 0);

  ~QtKalmanFiltererParameterDialog();

  ///Convert the table and its content to HTML
  const std::string ToHtml() const;

signals:
  ///Emitted when table changes from/to a valid to/from an invalid state
  void signal_state_changed();

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFiltererParameterDialog *ui;

private slots:
  void OnModelSizeChanged();
};

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTERERPARAMETERDIALOG
