#ifndef QTCOPYALLTABLEVIEW_H
#define QTCOPYALLTABLEVIEW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QTableView>
#pragma GCC diagnostic pop

#include <string>
#include <vector>

namespace ribi {

class QtCopyAllTableView : public QTableView
{
  public:
  explicit QtCopyAllTableView(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);


  private:
  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);
};

} //~namespace ribi

#endif // QTCOPYALLTABLEVIEW_H
