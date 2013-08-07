#include <iostream>

#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const auto v = QFileDialog::getOpenFileNames();

  std::cout << "Number of files selected: " << v.size() << '\n';
  for (auto s: v) std::cout << s.toStdString() << '\n';

}

/* Example output:

Number of files selected: 0

*/

/* Example output:

Number of files selected: 3
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample2-Qt_5_0_1_qt5-Debug/CppQFileDialogExample2
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample2-Qt_5_0_1_qt5-Debug/main.o
/home/richel/ProjectRichelBilderbeek/Test/build-CppQFileDialogExample2-Qt_5_0_1_qt5-Debug/Makefile
*/
