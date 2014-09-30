#ifndef SIMTOPPREDATORPREYWIDGET_H
#define SIMTOPPREDATORPREYWIDGET_H

#include <vector>
#include <QWidget>
#include <QImage>

class SimTopPredatorPreyWidget : public QWidget
{
  Q_OBJECT
  public:
  typedef std::vector<std::vector<double>> Grid;
  explicit SimTopPredatorPreyWidget(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);

  static int GetWidth() { return m_width; }
  static int GetHeight() { return m_height; }

  void Set(const Grid& grid);

  signals:

  public slots:


  private:
  static void Test() noexcept;
  static const int m_width{256};
  static const int m_height{256};
  QImage m_image;
};

#endif // SIMTOPPREDATORPREYWIDGET_H
