#include "dialog.h"

#include <cassert>
#include <fstream>
#include <string>

#include "ui_dialog.h"


///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFileStl(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);

  {
    const std::string executable{"/home/richel/bin/GameBeerWanterDesktop"};
    assert(IsRegularFileStl(executable));
  }
  {
    const std::string executable{"/home/richel/bin/GameMaziakDesktop"};
    assert(IsRegularFileStl(executable));
  }
}

Dialog::~Dialog()
{
  delete ui;
}


void Dialog::on_button1_clicked()
{
  const std::string executable{"/home/richel/bin/GameBeerWanterDesktop"};
  assert(IsRegularFileStl(executable));
  std::system(executable.c_str());
}

void Dialog::on_button2_clicked()
{
  const std::string executable{"/home/richel/bin/GameMaziakDesktop"};
  assert(IsRegularFileStl(executable));
  std::system(executable.c_str());
}
