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

namespace ribi {

class QtFilterOperationerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtFilterOperationerMainDialog(QWidget *parent = 0);
  QtFilterOperationerMainDialog(const QtFilterOperationerMainDialog&) = delete;
  QtFilterOperationerMainDialog& operator=(const QtFilterOperationerMainDialog&) = delete;
  ~QtFilterOperationerMainDialog();

private:
  Ui::QtFilterOperationerMainDialog *ui;

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
