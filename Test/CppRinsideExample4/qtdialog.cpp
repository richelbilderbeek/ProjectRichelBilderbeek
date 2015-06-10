#include "qtdialog.h"
#include <cassert>

#include <QFile>
#include <QGridLayout>
#include <QSvgWidget>
#include <QTextStream>

#include "RInside.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_r_inside{new RInside},
  m_svg_widget{new QSvgWidget}
{
  ui->setupUi(this);

  {
    assert(this->layout());
    this->layout()->addWidget(m_svg_widget);
  }
  on_doubleSpinBox_valueChanged(6.28);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_doubleSpinBox_valueChanged(double arg1)
{
  const auto m_tempfile = QString::fromStdString(Rcpp::as<std::string>(m_r_inside->parseEval("tfile <- tempfile()")));
  const auto m_svgfile  = QString::fromStdString(Rcpp::as<std::string>(m_r_inside->parseEval("sfile <- tempfile()")));

  (*m_r_inside)["a"] = arg1;
  std::string cmd0 = "svg(width=6,height=6,pointsize=10,filename=tfile); ";
  std::string cmd1 = "x <- seq(0,2*pi,0.01);";
  std::string cmd2 = "y <- sin(x * a);";
  std::string cmd3 = "plot(x,y,t='line',main=\"CppRinsideExample4\");";
  std::string cmd4 = "dev.off();";
  std::string cmd = cmd0 + cmd1 + cmd2 + cmd3 + cmd4;
  m_r_inside->parseEvalQ(cmd);

  {
    // cairoDevice creates richer SVG than Qt can display
    // but per Michaele Lawrence, a simple trick is to s/symbol/g/ which we do here
    QFile infile(m_tempfile);
    infile.open(QFile::ReadOnly);
    QFile outfile(m_svgfile);
    outfile.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream in(&infile);
    QTextStream out(&outfile);
    QRegExp rx1("<symbol");
    QRegExp rx2("</symbol");
    while (!in.atEnd()) {
      QString line = in.readLine();
      line.replace(rx1, "<g"); // so '<symbol' becomes '<g ...'
      line.replace(rx2, "</g");// and '</symbol becomes '</g'
      out << line << "\n";
    }
    infile.close();
    outfile.close();
  }
  m_svg_widget->load(m_svgfile);
}
