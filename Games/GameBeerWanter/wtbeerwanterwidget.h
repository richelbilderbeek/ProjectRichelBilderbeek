#ifndef BEERWANTERWT_H
#define BEERWANTERWT_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
//---------------------------------------------------------------------------
namespace Wt
{
  struct WPaintDevice;
  struct WPaintedWidget;
  struct WPainter;
};
//---------------------------------------------------------------------------
struct BeerWanter;
//---------------------------------------------------------------------------
struct BeerWanterWtWidget : public Wt::WPaintedWidget
{
public:
  BeerWanterWtWidget(
    Wt::WContainerWidget *parent = 0);
  ~BeerWanterWtWidget() {}

protected:
   void paintEvent(Wt::WPaintDevice *paintDevice);

private:
  Wt::WPainter::Image * m_image;
  boost::shared_ptr<BeerWanter> m_beerwanter;

  std::string m_debug_text;

  void OnClick(const Wt::WMouseEvent& e);
  void OnMouseMove(const Wt::WMouseEvent& e);
};
//---------------------------------------------------------------------------
#endif // BEERWANTERWT_H
