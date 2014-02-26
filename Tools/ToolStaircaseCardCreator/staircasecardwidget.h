#ifndef STAIRCASECARDWIDGET_H
#define STAIRCASECARDWIDGET_H

#include <QWidget>

#include "staircasecard.h"

class StaircaseCardWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StaircaseCardWidget(
    QWidget *parent = 0,
    const int n_cols = 16,
    const int n_rows = 20);

signals:

public slots:

private:
  StaircaseCard m_card;
};

#endif // STAIRCASECARDWIDGET_H
