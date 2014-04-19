#ifndef TRAFFICLIGHTDIALOG_H
#define TRAFFICLIGHTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#pragma GCC diagnostic pop

struct Image;

namespace Ui {
  class TrafficLightDialog;
}

class TrafficLightDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TrafficLightDialog(QWidget *parent = 0);
  TrafficLightDialog(const TrafficLightDialog&) = delete;
  TrafficLightDialog& operator=(const TrafficLightDialog&) = delete;
  ~TrafficLightDialog();

private:
  Ui::TrafficLightDialog *ui;
  //Images on the screen
  boost::shared_ptr<Image> m_red;
  boost::shared_ptr<Image> m_orange;
  boost::shared_ptr<Image> m_green;
  //Read-only off-screen images
  boost::shared_ptr<const Image> m_red_on;
  boost::shared_ptr<const Image> m_orange_on;
  boost::shared_ptr<const Image> m_green_on;
  boost::shared_ptr<const Image> m_red_off;
  boost::shared_ptr<const Image> m_orange_off;
  boost::shared_ptr<const Image> m_green_off;
private slots:
  void onRedClicked();
  void onOrangeClicked();
  void onGreenClicked();
};

#endif // TRAFFICLIGHTDIALOG_H
