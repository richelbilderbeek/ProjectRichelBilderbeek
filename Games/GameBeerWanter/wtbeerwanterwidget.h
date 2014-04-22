#ifndef WTBEERWANTERWIDGET_H
#define WTBEERWANTERWIDGET_H

#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>

namespace Wt
{
  struct WPaintDevice;
  struct WPaintedWidget;
  struct WPainter;
};

namespace ribi {

struct BeerWanterMainDialog;

struct WtBeerWanterWidget : public Wt::WPaintedWidget
{
public:
  WtBeerWanterWidget(
    Wt::WContainerWidget *parent = 0);
  WtBeerWanterWidget(const WtBeerWanterWidget&) = delete;
  WtBeerWanterWidget& operator=(const WtBeerWanterWidget&) = delete;
  ~WtBeerWanterWidget() {}

protected:
   void paintEvent(Wt::WPaintDevice *paintDevice);

private:
  std::string m_debug_text;
  boost::shared_ptr<BeerWanterMainDialog> m_dialog;
  Wt::WPainter::Image * m_image;


  void OnClick(const Wt::WMouseEvent& e);
  void OnMouseMove(const Wt::WMouseEvent& e);
};

} //~namespace ribi

#endif // WTBEERWANTERWIDGET_H
