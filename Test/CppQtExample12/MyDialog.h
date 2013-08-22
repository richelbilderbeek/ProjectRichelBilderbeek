#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class MyDialog : public QDialog
{
  Q_OBJECT

  public:
  MyDialog() : m_clicks(0) { }

  public slots:
    void buttonClicked()
    {
      ++m_clicks;
      QString s; s = s.number(m_clicks);
      this->setWindowTitle("Top button is clicked " + s + " times");
    }
  private:
    int m_clicks;
};

#endif // MYDIALOG_H
