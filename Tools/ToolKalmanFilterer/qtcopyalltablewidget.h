#ifndef QTCOPYALLTABLEWIDGET_H
#define QTCOPYALLTABLEWIDGET_H

#include <string>
#include <vector>
#include <QTableWidget>

class QtCopyAllTableWidget : public QTableWidget
{
  public:
  QtCopyAllTableWidget(QWidget *parent = 0);

  protected:
  void keyPressEvent(QKeyEvent *event);

  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};

#endif // QTCOPYALLTABLEWIDGET_H
