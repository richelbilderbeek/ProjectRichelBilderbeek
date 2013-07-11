#include "qtdialog.h"
#include "ui_qtdialog.h"

#include <cassert>
#include <cmath>
#include <string>
#include <string>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/version.hpp>

#include <QLabel>
#include <QVBoxLayout>

#include "fparser.hh"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_point_data.h"
#include "qwt_text.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_curve(new QwtPlotCurve("Sine")),
  m_plot(new QwtPlot(QwtText("CppQwtExample1")))
{
  ui->setupUi(this);

  assert(!this->layout());
  QLayout * const my_layout = new QVBoxLayout;
  this->setLayout(my_layout);

  #ifndef NDEBUG
  my_layout->addWidget(new QLabel("DEBUG"));
  #else
  my_layout->addWidget(new QLabel("RELEASE"));
  #endif

  my_layout->addWidget(new QLabel( ("GCC version: " + GetGccVersion()).c_str()));
  //my_layout->addWidget(new QLabel( ("Qt Creator version: " + GetQtCreatorVersion()).c_str()));
  my_layout->addWidget(new QLabel( ("STL version: " + GetStlVersion()).c_str()));
  my_layout->addWidget(new QLabel( ("Boost version: " + GetBoostVersion()).c_str()));


  {
    FunctionParser f;
    f.Parse("x * x","x");
    assert(f.GetParseErrorType()== FunctionParser::FP_NO_ERROR);
    const double xs[1] = { M_PI };
    const double y = f.Eval(xs);
    assert(f.EvalError()==0);
    my_layout->addWidget(new QLabel("Warp's function parser version: 4.5.1"));
  }
  {
    m_plot->setGeometry(0,0,640,400);
    m_plot->setAxisScale(QwtPlot::xBottom, 0.0,2.0 * M_PI);
    m_plot->setAxisScale(QwtPlot::yLeft,-1.0,1.0);
    std::vector<double> xs;
    std::vector<double> ys;
    for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
    {
      xs.push_back(x);
      ys.push_back(std::sin(x));
    }
    QwtPointArrayData * const data = new QwtPointArrayData(&xs[0],&ys[0],xs.size());
    m_curve->setData(data);
    m_curve->attach(m_plot);
    m_plot->replot();
    my_layout->addWidget(m_plot);
  }
}

QtDialog::~QtDialog()
{
  delete ui;
}

const std::vector<std::string> QtDialog::FileToVector(const std::string& filename)
{

  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

const std::string QtDialog::GetBoostVersion()
{
  std::string s = BOOST_LIB_VERSION;
  std::replace(s.begin(),s.end(),'_','.');
  return s;
}

const std::string QtDialog::GetGccVersion()
{
  return
      boost::lexical_cast<std::string>(__GNUC__)
    + std::string(".")
    + boost::lexical_cast<std::string>(__GNUC_MINOR__)
    + std::string(".")
    + boost::lexical_cast<std::string>(__GNUC_PATCHLEVEL__);
}

const std::string QtDialog::GetQtCreatorVersion()
{
  //'2>' denotes -AFAIK- 'Write to file only, no screen output'
  std::system("qtcreator -version 2> tmp.txt");
  const std::vector<std::string> v = FileToVector("tmp.txt");
  const std::size_t sz = v.size();
  assert(sz > 1);
  for (std::size_t i=0; i!=sz; ++i)
  {
    const std::string& s = v[i];
    if (s.substr(0,11) == std::string("Qt Creator "))
    {
      return s.substr(11,5);
    }
  }
  return "";
}

const std::string QtDialog::GetStlVersion()
{
  return boost::lexical_cast<std::string>(__VERSION__);
}
