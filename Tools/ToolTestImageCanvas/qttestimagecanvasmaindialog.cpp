#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestimagecanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "fileio.h"
#include "imagecanvas.h"
#include "trace.h"
#include "ui_qttestimagecanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestImageCanvasMainDialog::QtTestImageCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestImageCanvasMainDialog),
  m_canvas(CreateCanvas())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  m_canvas->m_signal_changed.connect(
    boost::bind(
      &ribi::QtTestImageCanvasMainDialog::ShowCanvas,this,
      boost::lambda::_1)
    );

  ShowCanvas(0);
}

ribi::QtTestImageCanvasMainDialog::~QtTestImageCanvasMainDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::ImageCanvas> ribi::QtTestImageCanvasMainDialog::CreateCanvas()
{
  const int n_cols = 40;
  const std::string filename = "";
  assert(!"TODO");
  boost::shared_ptr<ImageCanvas> canvas(new ImageCanvas(filename,n_cols));
  return canvas;
}


void ribi::QtTestImageCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  const CanvasColorSystem color_system
    = ui->box_color_system->currentIndex() == 0
    ? CanvasColorSystem::normal
    : CanvasColorSystem::invert;
  this->m_canvas->SetColorSystem(color_system);
  //Should redraw automatically
}

void ribi::QtTestImageCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen : CanvasCoordinatSystem::graph;
  this->m_canvas->SetCoordinatSystem(coordinat_system);
  //Should redraw automatically
}

void ribi::QtTestImageCanvasMainDialog::ShowCanvas(const ribi::ImageCanvas * const)
{
  //Display the image
  std::stringstream s;
  s << (*m_canvas);
  ui->text->setPlainText(s.str().c_str());

}

void ribi::QtTestImageCanvasMainDialog::on_button_clear_clicked()
{
  m_canvas->Clear();
  //Should redraw automatically
}


#ifndef NDEBUG
void ribi::QtTestImageCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestImageCanvasMainDialog::Test");
  QtTestImageCanvasMainDialog d;
  d.on_button_image_clicked();
  TRACE("Finished ribi::QtTestImageCanvasMainDialog::Test successfully");
}
#endif

void ribi::QtTestImageCanvasMainDialog::on_button_image_clicked()
{
  QFile qfile(":/ToolTestImageCanvas/images/R.png");
  const std::string filename { fileio::GetTempFileName() };
  qfile.copy(filename.c_str());
  assert(fileio::IsRegularFile(filename));
  m_canvas->Load(filename);
  fileio::DeleteFile(filename);
  assert(!fileio::IsRegularFile(filename));
}
