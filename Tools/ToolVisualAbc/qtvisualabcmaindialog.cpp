#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>

#include "fileio.h"
#include "qtvisualabcmaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtvisualabcmaindialog.h"
#include "visualabcmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtVisualAbcMainDialog::QtVisualAbcMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtVisualAbcMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  this->setMaximumWidth(1024);
  this->setMaximumHeight(768);

  //Set the example text
  {
    const std::vector<std::string> v = VisualAbcMainDialog::GetAbcFriday();
    std::string t;
    for(const std::string& s: v)
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

ribi::QtVisualAbcMainDialog::~QtVisualAbcMainDialog() noexcept
{
  {
    std::ofstream f("last_text.abc");
    f << ui->edit_text->toPlainText().toStdString();
  }

  delete ui;
}

void ribi::QtVisualAbcMainDialog::on_button_convert_clicked()
{
  VisualAbcMainDialog::ConvertToPng(ui->edit_text->toPlainText().toStdString());
  if (ribi::fileio::FileIo().IsRegularFile(VisualAbcMainDialog::m_png_filename))
  {
    ui->label_sheet->setPixmap(QPixmap(VisualAbcMainDialog::m_png_filename.c_str()));
  }
  else
  {
    assert(ribi::fileio::FileIo().IsRegularFile(VisualAbcMainDialog::m_pngs_filename));
    ui->label_sheet->setPixmap(QPixmap(VisualAbcMainDialog::m_pngs_filename.c_str()));
  }
}

void ribi::QtVisualAbcMainDialog::on_button_play_clicked()
{
  VisualAbcMainDialog::ConvertToMid(ui->edit_text->toPlainText().toStdString());
  VisualAbcMainDialog::PlayMid();
}

void ribi::QtVisualAbcMainDialog::resizeEvent(QResizeEvent *)
{

  this->setMaximumWidth(1024);
  //this->setMaximumHeight(768);

  ui->label_sheet->setMaximumWidth(1024 - 32);
  //ui->label_sheet->setMaximumHeight(300);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

void ribi::QtVisualAbcMainDialog::on_label_save_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(this,
     "Save your ABC file","", "ABC notation file (*.abc)").toStdString();
  std::ofstream file(filename.c_str());
  file << ui->edit_text->toPlainText().toStdString();
}


#ifndef NDEBUG
void ribi::QtVisualAbcMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
