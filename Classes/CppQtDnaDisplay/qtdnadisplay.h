#ifndef QTDNADISPLAY_H
#define QTDNADISPLAY_H

#include <QWidget>

namespace Ui {
  class QtDnaDisplay;
}

class QtDnaDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit QtDnaDisplay(QWidget *parent = 0);
  QtDnaDisplay(const QtDnaDisplay&) = delete;
  QtDnaDisplay& operator=(const QtDnaDisplay&) = delete;
  ~QtDnaDisplay();



private:
  Ui::QtDnaDisplay *ui;

  static const std::string sm_fail;
};

#endif // QTDNADISPLAY_H
