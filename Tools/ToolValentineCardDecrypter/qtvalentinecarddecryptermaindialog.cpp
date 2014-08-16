#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtvalentinecarddecryptermaindialog.h"

#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QFileDialog>
#include <QLabel>

#include "textcanvas.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtvalentinecarddecryptermaindialog.h"
#include "valentinecarddecryptermaindialog.h"
#include "valentinecardsymbol.h"
#include "valentinecardsymbols.h"
#pragma GCC diagnostic pop

ribi::QtValentineCardDecrypterMainDialog::QtValentineCardDecrypterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtValentineCardDecrypterMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->edit->setText("Hello world");
}

ribi::QtValentineCardDecrypterMainDialog::~QtValentineCardDecrypterMainDialog() noexcept
{
  delete ui;
}

void ribi::QtValentineCardDecrypterMainDialog::on_edit_textChanged(const QString &arg1)
{
  const std::string text = arg1.toStdString();
  if (text.empty())
  {
    ui->text->setPlainText("");
    ui->label->setPixmap(QPixmap());
  }
  else
  {
    {
      std::stringstream s;
      s << (*ValentineCardDecrypterMainDialog().ToSymbolsAsString(text));
      ui->text->setPlainText(s.str().c_str());
    }
    {
      const boost::shared_ptr<QImage> image {
        ValentineCardDecrypterMainDialog().ToSymbolsAsImage(text)
      };
      ui->label->setPixmap(QPixmap::fromImage(*image));
    }
  }
}

#ifndef NDEBUG
void ribi::QtValentineCardDecrypterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

