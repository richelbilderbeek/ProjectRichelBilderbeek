#ifndef QTNSANABROSKEYSWIDGET_H
#define QTNSANABROSKEYSWIDGET_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------------------------
struct NsanaBrosKeys;
//---------------------------------------------------------------------------
class QtNsanaBrosKeysWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtNsanaBrosKeysWidget(
    const NsanaBrosKeys * const keys = 0,
    QWidget *parent = 0);
  void OnKeysChanged();

protected:
  void paintEvent(QPaintEvent *);

private:
  const NsanaBrosKeys * const m_keys;

signals:

public slots:

};
//---------------------------------------------------------------------------
#endif // QTNSANABROSKEYSWIDGET_H
