//---------------------------------------------------------------------------
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/bounds.hpp>
//---------------------------------------------------------------------------
#include "dialog.h"
#include "hugevector.h"
#include "ui_dialog.h"
//---------------------------------------------------------------------------
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
  {
    std::vector<cln::cl_I> v;
    std::clog << "A regular std::vector has max size: "
      << v.max_size() << '\n';
  }
  //100 million
  cln::cl_I sz("100000000");
  HugeVector<cln::cl_I> v(sz);

  {
    try
    {
      v.reserve_all();
      for (cln::cl_I i=0; i!=sz; ++i)
      {
        v.push_back(i);
        assert(v[i]==i);
      }
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    catch (...)
    {
      std::cerr << "Unknown exception!" << '\n';
    }

  }
}
//---------------------------------------------------------------------------
Dialog::~Dialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void Dialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------

