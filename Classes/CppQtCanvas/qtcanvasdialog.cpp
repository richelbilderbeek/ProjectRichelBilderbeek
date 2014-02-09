#include "qtcanvasdialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QTimer>
#include <QVBoxLayout>

#include "qtcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtCanvasDialog::QtCanvasDialog(QtCanvas * const qtcanvas)
  : m_qtcanvas(qtcanvas),
    m_resize_timer(new QTimer)
{
  assert(!layout());
  QLayout * const my_layout = new QVBoxLayout;
  my_layout->setMargin(0);
  my_layout->setSpacing(0);
  my_layout->setContentsMargins(0,0,0,0);
  my_layout->addWidget(m_qtcanvas);
  my_layout->setAlignment(m_qtcanvas,Qt::AlignCenter);
  my_layout->setAlignment(my_layout,Qt::AlignCenter);
  setLayout(my_layout);

  //setStyleSheet("QDialog { background-color: rgb(0, 0, 0); font: 14px \"Courier New\"/Courier/monospace; }");
  setStyleSheet("QDialog { background-color: rgb(0, 0, 0); }");
  //QPalette p = palette();
  //p.setColor(QPalette::Base, Qt::black);
  //p.setColor(QPalette::Text, Qt::white);
  //setPalette(p);

  m_qtcanvas->m_signal_on_destroy.connect(boost::bind(
    &ribi::QtCanvasDialog::OnQtCanvasDestroy,this)
  );

  QObject::connect(m_resize_timer,SIGNAL(timeout()),this,SLOT(OnResizeTimer()));
  m_resize_timer->setInterval(10);
  m_resize_timer->start();
}

ribi::QtCanvasDialog::~QtCanvasDialog() noexcept
{
  TRACE_FUNC();
  m_resize_timer->stop();
  delete m_resize_timer;
}

void ribi::QtCanvasDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    TRACE_FUNC();
    close();
    close_me();
    return;
  }
  m_qtcanvas->keyPressEvent(event);
}

void ribi::QtCanvasDialog::OnQtCanvasDestroy()
{
  TRACE_FUNC();
  close_me();
  m_show_child = false;
  close();
}

void ribi::QtCanvasDialog::OnResizeTimer()
{
  if (!isVisible() || !isActiveWindow()) return;

  const int dx = width() - (m_qtcanvas->width() + 2);
  if (dx < 0)
  //if(horizontalScrollBar()->isVisible())
  {
    this->setGeometry(
      geometry().x() + (dx / 2),
      geometry().y(),
      geometry().width() - dx,
      geometry().height()
    );
  }

  //assert(verticalScrollBar());
  const int dy = height() - (m_qtcanvas->height() + 2);
  if (dy < 0)
  //if (this->height() < this->m_qtcanvas->height())
  //if(verticalScrollBar()->isVisible())
  {
    this->setGeometry(
      geometry().x(),
      geometry().y() + (dy / 2),
      geometry().width(),
      geometry().height() - dy
    );
  }
}
