#include "qtmaziakcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "maziakmaindialog.h"
//#include "qtmaziakwidget.h"
#pragma GCC diagnostic pop

ribi::maziak::QtMaziakCanvas::QtMaziakCanvas(
  const int width, const int height)
  : QtCanvas(CreateCanvas(width,height)),
    m_widget(CreateWidget(width,height))
{
  m_widget->m_signal_changed.connect(
    boost::bind(&ribi::maziak::QtMaziakCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::maziak::QtMaziakCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  return canvas;
}

const boost::shared_ptr<ribi::MaziakMainDialog> ribi::maziak::QtMaziakCanvas::CreateWidget(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<MaziakWidget> w {
    new MaziakWidget(width,height)
  };
  return w;
}

void ribi::maziak::QtMaziakCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->PressKey(ribi::MaziakWidget::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_widget->PressKey(ribi::MaziakWidget::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_widget->PressKey(ribi::MaziakWidget::Key::right);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::maziak::QtMaziakCanvas::OnChanged()
{
  SetCanvas(m_widget->ToTextCanvas());
}
