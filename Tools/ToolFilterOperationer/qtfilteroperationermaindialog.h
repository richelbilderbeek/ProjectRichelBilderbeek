#ifndef QTFILTEROPERATIONERMAINDIALOG_H
#define QTFILTEROPERATIONERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtFilterOperationerMainDialog;
}

struct QPixmap;
struct QLabel;

namespace ribi {

struct QtUblasMatrixDoubleModel;

class QtFilterOperationerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtFilterOperationerMainDialog(QWidget *parent = 0);
  QtFilterOperationerMainDialog(const QtFilterOperationerMainDialog&) = delete;
  QtFilterOperationerMainDialog& operator=(const QtFilterOperationerMainDialog&) = delete;
  ~QtFilterOperationerMainDialog();

private slots:
  void on_button_load_clicked();

  void on_box_filter_rows_valueChanged(const QString &arg1);

  void on_box_filter_cols_valueChanged(const QString &arg1);

private:
  Ui::QtFilterOperationerMainDialog *ui;

  QtUblasMatrixDoubleModel * const m_model;
  QLabel * m_source;

  void OnAnyChange();
/*

//VCL dependent
export template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid);

export template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid);

//VCL dependent
void DoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGrid,
  TImage * const target);

const bool CanDoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget);

void EnhanceContrast(const TImage * const image);

const double GetAverageGreyness(const TImage * const image);


//Creates a 2D-std::vector (y-x-ordered) from a TImage
const std::vector<std::vector<int> > ImageToVector(const TImage * const image);

//Fills a TImage from a 2D-std::vector (y-x-ordered)
void VectorToImage(const std::vector<std::vector<int> >& v, const TImage * const image);

//From http://www.richelbilderbeek.nl/CppDoHistogramEqualization.htm
void DoHistogramEqualization(const TImage * const source, TImage * const target);

//From htpp://www.richelbilderbeek.nl/CppGetImageHistogram.htm
const std::vector<int> GetImageHistogram(const TImage * const image);

*/


};

} //~namespace ribi

#endif // QTFILTEROPERATIONERMAINDIALOG_H
