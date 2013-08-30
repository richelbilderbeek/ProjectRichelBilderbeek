#include <cassert>
#include <iostream>

#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QFileDialog d;

  //enum ViewMode { Detail, List };
  d.setViewMode(QFileDialog::Detail);

  //enum FileMode { AnyFile, ExistingFile, Directory, ExistingFiles, DirectoryOnly };
  d.setFileMode(QFileDialog::AnyFile);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d.setAcceptDrops(QFileDialog::AcceptSave);

  //enum Option { ShowDirsOnly, DontResolveSymlinks, DontConfirmOverwrite, DontUseSheet, DontUseNativeDialog, ReadOnly, HideNameFilterDetails }
  //Without QFileDialog::DontUseNativeDialog there will not be an edit box to supply
  //a filename, under Lubuntu 13.04 (raring)
  d.setOptions(QFileDialog::DontUseNativeDialog);

  d.setWindowTitle("Save"); //Otherwise it states 'Open'

  d.exec();

  if (d.result() == QDialog::Accepted)
  {
    std::cout << "Number of files selected: " << d.selectedFiles().size() << '\n';
    const auto v = d.selectedFiles();
    for (auto s: v) std::cout << s.toStdString() << '\n';
  }
  else
  {
    assert(d.result() == QDialog::Rejected);
    std::cout << "Dialog closed with cancel or close\n";
  }
}

/* Example output:

Number of files selected: 1
/home/richel/ProjectRichelBilderbeek/Test/CppQFileDialogExample4/mynewfile.txt

*/
