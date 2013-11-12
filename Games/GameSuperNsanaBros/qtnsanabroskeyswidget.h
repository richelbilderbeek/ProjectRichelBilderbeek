#ifndef QTNSANABROSKEYSWIDGET_H
#define QTNSANABROSKEYSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct NsanaBrosKeys;

class QtNsanaBrosKeysWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtNsanaBrosKeysWidget(
    const NsanaBrosKeys * const keys = 0,
    QWidget *parent = 0);
  QtNsanaBrosKeysWidget(const QtNsanaBrosKeysWidget&) = delete;
  QtNsanaBrosKeysWidget& operator=(const QtNsanaBrosKeysWidget&) = delete;
  void OnKeysChanged();

protected:
  void paintEvent(QPaintEvent *);

private:
  const NsanaBrosKeys * const m_keys;

signals:

public slots:

};

} //~namespace ribi

#endif // QTNSANABROSKEYSWIDGET_H
