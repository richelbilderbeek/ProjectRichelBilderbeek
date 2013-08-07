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
  d.setFileMode(QFileDialog::ExistingFiles);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d.setAcceptDrops(QFileDialog::AcceptOpen);

  //enum Option { ShowDirsOnly, DontResolveSymlinks, DontConfirmOverwrite, DontUseSheet, DontUseNativeDialog, ReadOnly, HideNameFilterDetails }
  d.setOptions(QFileDialog::ReadOnly);

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

Number of files selected: 3
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample1-Qt_5_0_1_qt5-Debug/CppQFileDialogExample1
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample1-Qt_5_0_1_qt5-Debug/main.o
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample1-Qt_5_0_1_qt5-Debug/Makefile

*/
