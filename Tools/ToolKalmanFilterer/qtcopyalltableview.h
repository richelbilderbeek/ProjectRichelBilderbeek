#ifndef QTCOPYALLTABLEVIEW_H
#define QTCOPYALLTABLEVIEW_H

#include <QTableView>

#include <string>
#include <vector>

class QtCopyAllTableView : public QTableView
{
  public:
  QtCopyAllTableView(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);


  private:
  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);
};

#endif // QTCOPYALLTABLEVIEW_H
