#ifndef IMAGE_H
#define IMAGE_H

#include <QColor>
#include <QLabel>
#include <QObject>

struct QColor;
struct QMouseEvent;

class Image : public QLabel
{
  Q_OBJECT

public:
    Image(const QString& filename);
    void mousePressEvent( QMouseEvent * e);
 signals:
    void onClick();
};

#endif // IMAGE_H
