#include "qtdaswahreschlagerfestcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "daswahreschlagerfestwidget.h"
#include "qtdaswahreschlagerfestwidget.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestCanvas::QtDasWahreSchlagerfestCanvas(
  const int width, const int height)
  : QtCanvas(CreateCanvas(width,height)),
    m_widget(CreateWidget(width,height))
{
  m_widget->m_signal_changed.connect(
    boost::bind(&ribi::QtDasWahreSchlagerfestCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::QtDasWahreSchlagerfestCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  return canvas;
}

const boost::shared_ptr<ribi::DasWahreSchlagerfestWidget> ribi::QtDasWahreSchlagerfestCanvas::CreateWidget(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<DasWahreSchlagerfestWidget> w {
    new DasWahreSchlagerfestWidget(width,height)
  };
  return w;
}

void ribi::QtDasWahreSchlagerfestCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->PressKey(ribi::DasWahreSchlagerfestWidget::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_widget->PressKey(ribi::DasWahreSchlagerfestWidget::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_widget->PressKey(ribi::DasWahreSchlagerfestWidget::Key::right);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::QtDasWahreSchlagerfestCanvas::OnChanged()
{
  SetCanvas(m_widget->ToTextCanvas());
}
