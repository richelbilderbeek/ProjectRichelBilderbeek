#ifndef QTCOPYALLTABLEWIDGET_H
#define QTCOPYALLTABLEWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QTableWidget>
#pragma GCC diagnostic pop

namespace ribi {

class QtCopyAllTableWidget : public QTableWidget
{
  public:
  explicit QtCopyAllTableWidget(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);

  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};

} //~namespace ribi

#endif // QTCOPYALLTABLEWIDGET_H
