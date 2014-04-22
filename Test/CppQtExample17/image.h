#ifndef IMAGE_H
#define IMAGE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QColor>
#include <QLabel>
#include <QObject>
#pragma GCC diagnostic pop

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
