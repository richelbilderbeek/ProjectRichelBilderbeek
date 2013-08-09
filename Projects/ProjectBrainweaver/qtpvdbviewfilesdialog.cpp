#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbviewfilesdialog.h"

#include <cassert>
#include <iterator>
#include <QFileDialog>
#include <QKeyEvent>
#include "pvdbhelper.h"
#include "qtpvdbfiledialog.h"
#include "ui_qtpvdbviewfilesdialog.h"

QtPvdbViewFilesDialog::QtPvdbViewFilesDialog(QWidget* parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbViewFilesDialog)
{
  ui->setupUi(this);
}

QtPvdbViewFilesDialog::~QtPvdbViewFilesDialog()
{
  delete ui;
}

void QtPvdbViewFilesDialog::OnTimerLeft()
{
}

void QtPvdbViewFilesDialog::OnTimerRight()
{

}

void QtPvdbViewFilesDialog::on_button_left_clicked()
{
  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Select a file to view");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto filenames = d->selectedFiles();
  if (filenames.isEmpty()) return;
  assert(filenames.size() == 1);
  const std::string filename = filenames[0].toStdString();
  assert(QFile::exists(filename.c_str()));
  assert(!pvdb::SafeFileToVector(filename).empty());

  const std::vector<std::string> v = pvdb::XmlToPretty(pvdb::SafeFileToVector(filename)[0]);
  std::string text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text+=s;
      text+=std::string("\n");
    }
  );
  ui->text_left->clear();
  ui->text_left->setPlainText(text.c_str());
}

void QtPvdbViewFilesDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(event);
}

void QtPvdbViewFilesDialog::on_button_right_clicked()
{
  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Select a file to view");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto filenames = d->selectedFiles();
  if (filenames.isEmpty()) return;
  assert(filenames.size() == 1);
  const std::string filename = filenames[0].toStdString();
  assert(QFile::exists(filename.c_str()));
  assert(!pvdb::FileToVector(filename).empty());
  const std::vector<std::string> v = pvdb::XmlToPretty(pvdb::FileToVector(filename)[0]);
  std::string text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text+=s;
      text+=std::string("\n");
    }
  );

  ui->text_right->clear();
  ui->text_right->setPlainText(text.c_str());
}
