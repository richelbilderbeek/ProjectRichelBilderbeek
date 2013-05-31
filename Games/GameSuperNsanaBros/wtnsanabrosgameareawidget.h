#ifndef WTNSANABROSGAMEAREAWIDGET_H
#define WTNSANABROSGAMEAREAWIDGET_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
namespace Wt
{
  struct WPaintDevice;
  struct WPaintedWidget;
  struct WMouseEvent;
}
//---------------------------------------------------------------------------
struct NsanaBrosGameAreaWidget;
//---------------------------------------------------------------------------
struct WtNsanaBrosGameAreaWidget : public Wt::WPaintedWidget
{
  WtNsanaBrosGameAreaWidget();
  boost::signals2::signal<void ()> m_signal_redraw;

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);
  private:

  boost::scoped_ptr<NsanaBrosGameAreaWidget> m_widget;
  void OnClicked(const Wt::WMouseEvent& e);
};
//---------------------------------------------------------------------------
#endif // WTNSANABROSGAMEAREAWIDGET_H
