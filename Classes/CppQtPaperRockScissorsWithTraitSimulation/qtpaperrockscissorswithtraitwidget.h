#ifndef QTPAPERROCKSCISSORSWITHTRAITWIDGET_H
#define QTPAPERROCKSCISSORSWITHTRAITWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "paperrockscissorswithtraitsimulation.h"

namespace Ui {
  class QtPaperRockScissorsWithTraitWidget;
}

struct QImage;

class QtPaperRockScissorsWithTraitWidget : public QWidget
{
  Q_OBJECT

public:
  using Init = PaperRockScissorsSimulation::Initialization;

  explicit QtPaperRockScissorsWithTraitWidget(
    const int width = 600,
    const int height = 400,
    const Init initialization = Init::random,
    const int rng_seed = 42,
    QWidget *parent = 0
  );
  QtPaperRockScissorsWithTraitWidget(const QtPaperRockScissorsWithTraitWidget&) = delete;
  QtPaperRockScissorsWithTraitWidget& operator=(const QtPaperRockScissorsWithTraitWidget&) = delete;
  ~QtPaperRockScissorsWithTraitWidget();

  std::tuple<int,int,int> GetLastPopSizes() const;
  std::tuple<double,double,double> GetLastMeanTraits() const;

  void SetAll(
    const int width,
    const int height,
    const Init initialization,
    const int rng_seed
  );

  static QRgb ToRgb(const PaperRockScissors prs) noexcept;

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::QtPaperRockScissorsWithTraitWidget *ui;
  QPixmap m_pixmap;
  PaperRockScissorsSimulation m_simulation;

private slots:
  void OnTimer();

signals:
  //Emitted everytime OnTimer is run
  void signal_next();
};


#endif // QTPAPERROCKSCISSORSWITHTRAITWIDGET_H
