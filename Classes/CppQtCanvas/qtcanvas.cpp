#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtcanvas.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "canvas.h"
#pragma GCC diagnostic pop

ribi::QtCanvas::QtCanvas(const boost::shared_ptr<ribi::Canvas> canvas)
  : m_canvas(canvas)
{
  assert(m_canvas);

  m_canvas->m_signal_changed.connect(
    boost::bind(
      &ribi::QtCanvas::ShowCanvas,this,
      boost::lambda::_1)
    );

  this->setStyleSheet("QPlainTextEdit { font: 14px \"Courier New\"/Courier/monospace; }");

  QPalette p = palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  setPalette(p);

  this->setReadOnly(true);

  ShowCanvas(m_canvas.get());
}

ribi::QtCanvas::~QtCanvas() noexcept
{
  m_canvas->m_signal_changed.disconnect(
    boost::bind(
      &ribi::QtCanvas::ShowCanvas,this,
      boost::lambda::_1
    )
  );
}
void ribi::QtCanvas::ShowCanvas(const Canvas * const)
{
  std::string text;
  for (std::string line: m_canvas->ToStrings()) { text += (line + '\n'); }
  if (!text.empty()) text.pop_back();
  this->setPlainText(text.c_str());
}
