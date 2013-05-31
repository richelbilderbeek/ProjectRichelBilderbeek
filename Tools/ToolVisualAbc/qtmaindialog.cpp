#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>
//---------------------------------------------------------------------------
#include "qtmaindialog.h"
#include "ui_qtmaindialog.h"
#include "maindialog.h"
//---------------------------------------------------------------------------
QtMainDialog::QtMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtMainDialog)
{
  ui->setupUi(this);
  this->setMaximumWidth(1024);
  this->setMaximumHeight(768);

  //Set the example text
  {
    const std::vector<std::string> v = VisualAbcMainDialog::GetAbcFriday();
    std::string t;
    BOOST_FOREACH(const std::string& s,v)
    {
      t+=s;
      t+='\n';
    }
    //Pop trailing '\n'
    t.resize(t.size() - 1);
    ui->edit_text->setPlainText(t.c_str());
  }

  this->on_button_convert_clicked();
}
//---------------------------------------------------------------------------
QtMainDialog::~QtMainDialog()
{
  {
    std::ofstream f("last_text.abc");
    f << ui->edit_text->toPlainText().toStdString();
  }

  delete ui;
}
//---------------------------------------------------------------------------
void QtMainDialog::changeEvent(QEvent *e)
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
void QtMainDialog::on_button_convert_clicked()
{
  VisualAbcMainDialog::ConvertToPng(ui->edit_text->toPlainText().toStdString());
  if (boost::filesystem::exists(VisualAbcMainDialog::m_png_filename))
  {
    ui->label_sheet->setPixmap(QPixmap(VisualAbcMainDialog::m_png_filename.c_str()));
  }
  else
  {
    assert(boost::filesystem::exists(VisualAbcMainDialog::m_pngs_filename));
    ui->label_sheet->setPixmap(QPixmap(VisualAbcMainDialog::m_pngs_filename.c_str()));
  }
}
//---------------------------------------------------------------------------
void QtMainDialog::on_button_play_clicked()
{
  VisualAbcMainDialog::ConvertToMid(ui->edit_text->toPlainText().toStdString());
  VisualAbcMainDialog::PlayMid();
}
//---------------------------------------------------------------------------
void QtMainDialog::resizeEvent(QResizeEvent *)
{

  this->setMaximumWidth(1024);
  //this->setMaximumHeight(768);

  ui->label_sheet->setMaximumWidth(1024 - 32);
  //ui->label_sheet->setMaximumHeight(300);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}
//---------------------------------------------------------------------------
void QtMainDialog::on_label_save_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(this,
     "Save your ABC file","", "ABC notation file (*.abc)").toStdString();
  std::ofstream file(filename.c_str());
  file << ui->edit_text->toPlainText().toStdString();
}
//---------------------------------------------------------------------------
