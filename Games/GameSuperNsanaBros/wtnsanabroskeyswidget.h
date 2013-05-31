#ifndef WTNSANABROSKEYSWIDGET_H
#define WTNSANABROSKEYSWIDGET_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
//#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
namespace Wt
{
  struct WPaintedWidget;
  //struct WMouseEvent;
}
//---------------------------------------------------------------------------
struct NsanaBrosKeysWidget;
//---------------------------------------------------------------------------
struct WtNsanaBrosKeysWidget : public Wt::WPaintedWidget
{
  WtNsanaBrosKeysWidget();
  boost::signals2::signal<void ()> m_signal_redraw;

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  boost::scoped_ptr<NsanaBrosKeysWidget> m_widget;
};
//---------------------------------------------------------------------------
#endif // WTNSANABROSGAMEAREAWIDGET_H
