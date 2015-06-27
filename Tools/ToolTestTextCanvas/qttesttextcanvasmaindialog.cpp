#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttesttextcanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "qtcanvas.h"
#include "qtcanvasdialog.h"
#include "textcanvas.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttesttextcanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTextCanvasMainDialog::QtTestTextCanvasMainDialog(QWidget *parent)
 :  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestTextCanvasMainDialog),
  m_canvas(CreateCanvas()),
  m_qtcanvas{new QtCanvas}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    assert(ui->verticalLayout);
    //m_qtcanvas.reset(new QtCanvas(m_canvas));
    m_qtcanvas->SetTextCanvas(m_canvas);
    ui->verticalLayout->addWidget(m_qtcanvas);
  }

  {
    const double w = m_canvas.GetWidth();
    const double h = m_canvas.GetHeight();
    ui->box_char_x->setValue(0.5 * w);
    ui->box_char_y->setValue(0.5 * h);
    ui->box_text_x->setValue(0.5 * w);
    ui->box_text_y->setValue(0.5 * h);
  }
}

ribi::QtTestTextCanvasMainDialog::~QtTestTextCanvasMainDialog() noexcept
{
  delete ui;
}

ribi::TextCanvas ribi::QtTestTextCanvasMainDialog::CreateCanvas()
{
  const int maxx = 79;
  const int maxy = 23;
  TextCanvas canvas(maxx,maxy);
  canvas.PutText(1,1,"Hello");
  canvas.PutText(2,2,"World");
  return canvas;
}

void ribi::QtTestTextCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas.SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}

void ribi::QtTestTextCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas.Clear();
  //Should redraw automatically
}

#ifndef NDEBUG
void ribi::QtTestTextCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TextCanvas();
    QtCanvas();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::QtTestTextCanvasMainDialog::on_button_char_clicked()
{
  const int x = ui->box_char_x->value();
  const int y = ui->box_char_y->value();
  const std::string s = ui->edit_char->text().toStdString();
  if (s.empty()) return;
  m_canvas.PutChar(x,y,s[0]);
}

void ribi::QtTestTextCanvasMainDialog::on_button_text_clicked()
{
  const int x = ui->box_text_x->value();
  const int y = ui->box_text_y->value();
  const std::string s = ui->edit_text->text().toStdString();
  m_canvas.PutText(x,y,s);
}

void ribi::QtTestTextCanvasMainDialog::on_button_as_dialog_clicked()
{
  QtCanvas * const qtcanvas {
    new QtCanvas
  };
  qtcanvas->SetTextCanvas(m_canvas);

  const boost::scoped_ptr<QtCanvasDialog> d {
    new QtCanvasDialog(qtcanvas)
  };
  this->ShowChild(d.get());
  //qtcanvas will be deleted by QtCanvasDialog

}
