#ifndef QTOCRWIDGET_H
#define QTOCRWIDGET_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "qtsketchwidget.h"

struct Ocr;

class QtOcrWidget : public QtSketchWidget
{
  Q_OBJECT
public:
  explicit QtOcrWidget(
    const std::string& path,
    const std::string& whitelist,
    QWidget *parent = 0);

  const std::string Read() const;

protected:

private:
  boost::shared_ptr<Ocr> m_ocr;
};

#endif // QTOCRWIDGET_H
