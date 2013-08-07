#include "dialog.h"

#include <cassert>
#include <sstream>
#include <QFileDialog>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_button_1_clicked()
{
  QFileDialog d;

  //enum ViewMode { Detail, List };
  d.setViewMode(QFileDialog::Detail);

  //enum FileMode { AnyFile, ExistingFile, Directory, ExistingFiles, DirectoryOnly };
  d.setFileMode(QFileDialog::ExistingFiles);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d.setAcceptDrops(QFileDialog::AcceptOpen);

  //enum Option { ShowDirsOnly, DontResolveSymlinks, DontConfirmOverwrite, DontUseSheet, DontUseNativeDialog, ReadOnly, HideNameFilterDetails }
  d.setOptions(QFileDialog::ReadOnly);

  d.exec();

  std::stringstream s;
  if (d.result() == QDialog::Accepted)
  {
    s << "Number of files selected: " << d.selectedFiles().size() << '\n';
    const auto v = d.selectedFiles();
    for (auto f: v) s << f.toStdString() << '\n';
  }
  else
  {
    assert(d.result() == QDialog::Rejected);
    s << "Dialog closed with cancel or close\n";
  }
  ui->text_1->setPlainText(s.str().c_str());
}

void Dialog::on_button_2_clicked()
{
  const auto v = QFileDialog::getOpenFileNames();

  std::stringstream s;
  s << "Number of files selected: " << v.size() << '\n';
  for (auto f: v) s << f.toStdString() << '\n';
  ui->text_2->setPlainText(s.str().c_str());
}
