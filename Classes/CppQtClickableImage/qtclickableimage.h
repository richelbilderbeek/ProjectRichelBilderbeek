#ifndef QTIMAGE_H
#define QTIMAGE_H

#include <vector>
#include <utility>
#include <QRect>
#include <QLabel>

struct QMouseEvent;

class QtImage : public QLabel
{
    Q_OBJECT
public:
    explicit QtImage(QWidget *parent = 0);
    void AddClickableRegion(const QRect& region,const std::function<void()>& function_to_do);
    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);

protected:

private:
  std::vector<std::pair<QRect,std::function<void()>>> m_v;

signals:

public slots:



};

#endif // QTIMAGE_H
