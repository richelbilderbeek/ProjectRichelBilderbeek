#include "qtmysterymachinecanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "mysterymachinewidget.h"
#include "qtmysterymachinewidget.h"
#pragma GCC diagnostic pop

ribi::QtMysteryMachineCanvas::QtMysteryMachineCanvas()
  : QtCanvas(CreateCanvas(58,20)),
    m_widget(CreateWidget())
{
  m_widget->m_signal_changed.connect(
    boost::bind(&ribi::QtMysteryMachineCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::QtMysteryMachineCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  return canvas;
}

const boost::shared_ptr<ribi::MysteryMachineWidget> ribi::QtMysteryMachineCanvas::CreateWidget() noexcept
{
  const boost::shared_ptr<MysteryMachineWidget> w {
    new MysteryMachineWidget
  };
  return w;
}

void ribi::QtMysteryMachineCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_widget->PressKey(ribi::MysteryMachineKey::front_clockwise);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->PressKey(ribi::MysteryMachineKey::front_counter_clockwise);
      break;
    case Qt::Key_U: case Qt::Key_I: case Qt::Key_O:
      m_widget->PressKey(ribi::MysteryMachineKey::back_clockwise);
      break;
    case Qt::Key_J: case Qt::Key_K: case Qt::Key_L:
      m_widget->PressKey(ribi::MysteryMachineKey::back_counter_clockwise);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_widget->PressKey(ribi::MysteryMachineKey::toggle);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::QtMysteryMachineCanvas::OnChanged()
{
  SetCanvas(m_widget->ToTextCanvas());
}
