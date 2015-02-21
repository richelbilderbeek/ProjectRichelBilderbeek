#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcanvas.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QPainter>

#include "canvas.h"
#include "dotmatrixtext.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtCanvas::QtCanvas(const boost::shared_ptr<ribi::Canvas> canvas)
  : m_signal_on_destroy{},
    m_canvas{},
    m_image{}
{
  assert(canvas);
  SetCanvas(canvas);
  assert(m_canvas);
}

ribi::QtCanvas::~QtCanvas() noexcept
{
  m_canvas->m_signal_changed.disconnect(
    boost::bind(
      &ribi::QtCanvas::ShowCanvas,this,
      boost::lambda::_1
    )
  );
  m_signal_on_destroy();
}

void ribi::QtCanvas::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    m_signal_on_destroy();
    close();
    return;
  }
  QWidget::keyPressEvent(event);
}

void ribi::QtCanvas::keyReleaseEvent(QKeyEvent* event)
{
  QWidget::keyReleaseEvent(event);
}

void ribi::QtCanvas::paintEvent(QPaintEvent *)
{
  std::vector<std::string> text;
  for (std::string line: m_canvas->ToStrings()) { text.push_back(line); }

  DotMatrixText t(text,1,DotMatrixText::ColorSystem::inverted);
  m_image = t.CreateImage();

  QPainter painter(this);
  painter.drawPixmap(rect(),QPixmap::fromImage(*m_image.get()));
  //painter.drawImage(rect(),*m_image.get());

}

void ribi::QtCanvas::SetCanvas(const boost::shared_ptr<Canvas> canvas)
{
  assert(canvas);

  if (canvas == m_canvas) { return; }

  //Disconnect current Canvas
  if (m_canvas)
  {
    m_canvas->m_signal_changed.disconnect(
      boost::bind(
        &ribi::QtCanvas::ShowCanvas,this,
        boost::lambda::_1
      )
    );
  }

  //Use new Canvas
  m_canvas = canvas;

  //Connect new Canvas
  m_canvas->m_signal_changed.connect(
    boost::bind(
      &ribi::QtCanvas::ShowCanvas,this,
      boost::lambda::_1)
    );

  //Set minimum size
  {
    std::vector<std::string> text;
    for (std::string line: m_canvas->ToStrings()) { text.push_back(line); }
    DotMatrixText t(text,1);
    setMinimumSize(
      t.GetMatrixHeight(),
      t.GetMatrixWidth()
    );
  }

  ShowCanvas(m_canvas.get());
}

void ribi::QtCanvas::ShowCanvas(const Canvas * const)
{
  repaint();
}
