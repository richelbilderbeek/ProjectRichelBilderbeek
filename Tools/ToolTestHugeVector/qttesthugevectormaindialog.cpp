#include <iostream>

#include <boost/numeric/conversion/bounds.hpp>

#include "qttesthugevectormaindialog.h"
#include "hugevector.h"
#include "ui_qttesthugevectormaindialog.h"

ribi::QtTestHugeVectorMainDialog::QtTestHugeVectorMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestHugeVectorMainDialog)
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

ribi::QtTestHugeVectorMainDialog::~QtTestHugeVectorMainDialog()
{
  delete ui;
}
