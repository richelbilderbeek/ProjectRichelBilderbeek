#ifndef QTKALMANFILTERERPARAMETERSDIALOG
#define QTKALMANFILTERERPARAMETERSDIALOG

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include <vector>

#include <QDialog>
//#include <QTableWidget>

//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>
#include <boost/signals2.hpp>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include "kalmanfilterexample.h"

namespace Ui {
  class QtKalmanFilterExamplesDialog;
}

class QtKalmanFilterExamplesDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFilterExamplesDialog(QWidget *parent = 0);
  ~QtKalmanFilterExamplesDialog();



  ///Click one of the examples
  void EmitExample(const int n) const;

  ///Let the ComboBox display naught
  void SetShowNoExample();

  //Never emit a boost::shared_ptr [1]
  mutable boost::signals2::signal<void(const KalmanFilterExample * const example)> m_signal_example;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFilterExamplesDialog *ui;


  #ifndef NDEBUG
  static void Test();
  #endif

private slots:
  void on_button_clicked();
  void on_box_currentIndexChanged(int index);
};


// [1] Don't put a boost::shared_ptr in a signal as it will be
//     reinterpret_cast-ed by the MOC:
//
// void QtKalmanFilterExperimentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
// {
//     if (_c == QMetaObject::InvokeMetaMethod) {
//         Q_ASSERT(staticMetaObject.cast(_o));
//         QtKalmanFilterExperimentDialog *_t = static_cast<QtKalmanFilterExperimentDialog *>(_o);
//         switch (_id) {
//         case 0: _t->SetExample((*reinterpret_cast< const boost::shared_ptr<KalmanFilterExample>(*)>(_a[1]))); break;
//         //...
//         default: ;
//         }
//     }
// }


#endif // QTKALMANFILTERERPARAMETERSDIALOG
