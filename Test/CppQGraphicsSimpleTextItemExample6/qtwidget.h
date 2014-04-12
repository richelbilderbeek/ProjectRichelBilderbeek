#ifndef QTWIDGET_H
#define QTWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/shared_ptr.hpp>
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct Text;

///The widget holding the items
///Must be a Q_OBJECT for slots to work
class QtWidget : public QGraphicsView
{
  Q_OBJECT

  public:
  QtWidget(QWidget *parent = 0);

  private slots:
  void OnTimer();

  private:
  std::vector<boost::shared_ptr<Text> > m_texts;
};

#endif // QTWIDGET_H
