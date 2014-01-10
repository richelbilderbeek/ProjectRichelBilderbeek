#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttesttextcanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "textcanvas.h"
#include "trace.h"
#include "ui_qttesttextcanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTextCanvasMainDialog::QtTestTextCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestTextCanvasMainDialog),
  m_canvas(CreateCanvas())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  m_canvas->m_signal_changed.connect(
    boost::bind(
      &ribi::QtTestTextCanvasMainDialog::ShowCanvas,this,
      boost::lambda::_1)
    );

  {
    const double w = m_canvas->GetWidth();
    const double h = m_canvas->GetHeight();
    ui->box_char_x->setValue(0.5 * w);
    ui->box_char_y->setValue(0.5 * h);
    ui->box_text_x->setValue(0.5 * w);
    ui->box_text_y->setValue(0.5 * h);
  }

  ShowCanvas(0);
}

ribi::QtTestTextCanvasMainDialog::~QtTestTextCanvasMainDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::TextCanvas> ribi::QtTestTextCanvasMainDialog::CreateCanvas()
{
  const int maxx = 79;
  const int maxy = 23;
  boost::shared_ptr<TextCanvas> canvas(new TextCanvas(maxx,maxy));
  canvas->PutText(1,1,"Hello");
  canvas->PutText(2,2,"World");
  return canvas;
}

void ribi::QtTestTextCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas->SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}

void ribi::QtTestTextCanvasMainDialog::ShowCanvas(const ribi::TextCanvas * const)
{
  //Display the image
  std::stringstream s;
  s << (*m_canvas);
  ui->text->setPlainText(s.str().c_str());

}

void ribi::QtTestTextCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas->Clear();
  //Should redraw automatically
}

#ifndef NDEBUG
void ribi::QtTestTextCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTextCanvasMainDialog::Test");
  TRACE("Finished ribi::QtTestTextCanvasMainDialog::Test successfully");
}
#endif

void ribi::QtTestTextCanvasMainDialog::on_button_char_clicked()
{
  const int x = ui->box_char_x->value();
  const int y = ui->box_char_y->value();
  const std::string s = ui->edit_char->text().toStdString();
  if (s.empty()) return;
  m_canvas->PutChar(x,y,s[0]);
}

void ribi::QtTestTextCanvasMainDialog::on_button_text_clicked()
{
  const int x = ui->box_text_x->value();
  const int y = ui->box_text_y->value();
  const std::string s = ui->edit_text->text().toStdString();
  m_canvas->PutText(x,y,s);
}
