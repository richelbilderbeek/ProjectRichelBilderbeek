#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcanvas.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QScrollBar>
#include <QTimer>

#include "canvas.h"
#pragma GCC diagnostic pop

ribi::QtCanvas::QtCanvas(const boost::shared_ptr<ribi::Canvas> canvas)
  : m_canvas{},
    m_resize_timer(new QTimer)
{
  assert(canvas);

  SetCanvas(canvas);
  assert(m_canvas);

  setStyleSheet("QPlainTextEdit { font: 14px \"Courier New\"/Courier/monospace; }");

  QPalette p = palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  setPalette(p);

  setReadOnly(true);
  ShowCanvas(m_canvas.get());

  QObject::connect(m_resize_timer,SIGNAL(timeout()),this,SLOT(OnResizeTimer()));
  m_resize_timer->setInterval(10);
  m_resize_timer->start();
}

ribi::QtCanvas::~QtCanvas() noexcept
{
  m_resize_timer->stop();
  delete m_resize_timer;

  m_canvas->m_signal_changed.disconnect(
    boost::bind(
      &ribi::QtCanvas::ShowCanvas,this,
      boost::lambda::_1
    )
  );
  //m_signal_on_destroy();
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

  QFontMetrics m(font());

  setMinimumSize(
    m_canvas->GetWidth()  * m.averageCharWidth(),
    m_canvas->GetHeight() * m.height()
  );

  ShowCanvas(m_canvas.get());
}

void ribi::QtCanvas::OnResizeTimer()
{
  assert(horizontalScrollBar());
  if(horizontalScrollBar()->isVisible())
  {
    //this->setMinimumWidth(width() + 2);
    this->setGeometry(
      geometry().x() - 16,
      geometry().y(),
      geometry().width() + 32,
      geometry().height()
    );
  }

  assert(verticalScrollBar());
  if(verticalScrollBar()->isVisible())
  {
    //this->setMinimumHeight(height() + 2);
    this->setGeometry(
      geometry().x(),
      geometry().y() - 16,
      geometry().width(),
      geometry().height() + 32
    );
  }
}

void ribi::QtCanvas::ShowCanvas(const Canvas * const)
{
  std::string text;
  for (std::string line: m_canvas->ToStrings()) { text += (line + '\n'); }
  if (!text.empty()) text.pop_back();
  setPlainText(text.c_str());
}
