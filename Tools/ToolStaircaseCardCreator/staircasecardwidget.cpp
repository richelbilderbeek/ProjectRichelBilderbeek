#include "staircasecardwidget.h"

StaircaseCardWidget::StaircaseCardWidget(
  QWidget *parent,
  const int n_cols,
  const int n_rows)
 : QWidget(parent),
   m_card(n_cols,n_rows)


{
}

