#include "qtcanvasdialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QVBoxLayout>

#include "qtcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtCanvasDialog::QtCanvasDialog(QtCanvas * const qtcanvas)
  : m_qtcanvas(qtcanvas)
{
  assert(!layout());
  QLayout * const my_layout = new QVBoxLayout;
  my_layout->setMargin(0);
  my_layout->setSpacing(0);
  my_layout->setContentsMargins(0,0,0,0);
  my_layout->addWidget(m_qtcanvas);
  m_qtcanvas->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
  my_layout->setAlignment(m_qtcanvas,Qt::AlignCenter);
  my_layout->setAlignment(my_layout,Qt::AlignCenter);
  setLayout(my_layout);

  setStyleSheet("QDialog { background-color: rgb(0, 0, 0); }");

  m_qtcanvas->m_signal_on_destroy.connect(boost::bind(
    &ribi::QtCanvasDialog::OnQtCanvasDestroy,this)
  );

}

ribi::QtCanvasDialog::~QtCanvasDialog() noexcept
{

}

void ribi::QtCanvasDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape)
  {
    close();
    close_me();
    return;
  }
  m_qtcanvas->keyPressEvent(event);
}

void ribi::QtCanvasDialog::keyReleaseEvent(QKeyEvent* event)
{
  m_qtcanvas->keyReleaseEvent(event);
}

void ribi::QtCanvasDialog::OnQtCanvasDestroy()
{
  close_me();
  m_show_child = false;
  close();
}

void ribi::QtCanvasDialog::resizeEvent(QResizeEvent *)
{
  m_qtcanvas->setGeometry(rect());
}
