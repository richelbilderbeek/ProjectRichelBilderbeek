#include "qtmaziakcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "maziakmaindialog.h"
#pragma GCC diagnostic pop

ribi::maziak::QtMaziakCanvas::QtMaziakCanvas(
  const int size)
  : QtCanvas(CreateCanvas(size,size)),
    m_widget(CreateWidget(size))
{
  //m_widget->m_signal_changed.connect(
  //  boost::bind(&ribi::maziak::QtMaziakCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::maziak::QtMaziakCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  assert(canvas);
  return canvas;
}

const boost::shared_ptr<ribi::maziak::MainDialog> ribi::maziak::QtMaziakCanvas::CreateWidget(
  const int size) noexcept
{
  const boost::shared_ptr<MainDialog> w {
    new MainDialog(size)
  };
  return w;
}

void ribi::maziak::QtMaziakCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->OnKeyPress(ribi::maziak::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_widget->OnKeyPress(ribi::maziak::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_widget->OnKeyPress(ribi::maziak::Key::right);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::maziak::QtMaziakCanvas::OnChanged()
{
  const int view_width  = 9;
  const int view_height = 9;
  SetCanvas(m_widget->ToTextCanvas(view_width,view_height));
}
