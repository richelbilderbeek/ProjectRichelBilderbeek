#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestimagecanvasmaindialog.h"

#include <cassert>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "dotmatrixstring.h"
#include "fileio.h"
#include "imagecanvas.h"
#include "qtcanvas.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestimagecanvasmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestImageCanvasMainDialog::QtTestImageCanvasMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestImageCanvasMainDialog),
  m_canvas(CreateCanvas()),
  m_qtcanvas{new QtCanvas}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    assert(ui->verticalLayout);
    m_qtcanvas->SetImageCanvas(m_canvas);
    ui->verticalLayout->addWidget(m_qtcanvas);
  }
}

ribi::QtTestImageCanvasMainDialog::~QtTestImageCanvasMainDialog() noexcept
{
  delete ui;
}

ribi::ImageCanvas ribi::QtTestImageCanvasMainDialog::CreateCanvas()
{
  const int n_cols = 40;
  const std::string filename { fileio::FileIo().GetTempFileName() };
  QFile file(":/ToolTestImageCanvas/images/R.png");
  file.copy(filename.c_str());
  assert(fileio::FileIo().IsRegularFile(filename));
  ImageCanvas canvas(filename,n_cols);
  fileio::FileIo().DeleteFile(filename);
  assert(!fileio::FileIo().IsRegularFile(filename));
  return canvas;
}

ribi::CanvasColorSystem ribi::QtTestImageCanvasMainDialog::GetColorSystem() const noexcept
{
  const CanvasColorSystem color_system
    = ui->box_color_system->currentIndex() == 0
    ? CanvasColorSystem::normal
    : CanvasColorSystem::invert;
  return color_system;
}

ribi::CanvasCoordinatSystem ribi::QtTestImageCanvasMainDialog::GetCoordinatSystem() const noexcept
{
  const CanvasCoordinatSystem coordinat_system
    = ui->box_coordinat_system->currentIndex() == 0
    ? CanvasCoordinatSystem::screen
    : CanvasCoordinatSystem::graph;
  return coordinat_system;
}

int ribi::QtTestImageCanvasMainDialog::GetNcols() const noexcept
{
  return ui->box_n_cols->value();
}

void ribi::QtTestImageCanvasMainDialog::on_box_color_system_currentIndexChanged(int )
{
  this->m_canvas.SetColorSystem(GetColorSystem());
  //Should redraw automatically
}

void ribi::QtTestImageCanvasMainDialog::on_box_coordinat_system_currentIndexChanged(int )
{
  this->m_canvas.SetCoordinatSystem(GetCoordinatSystem());
  //Should redraw automatically
}

#ifndef NDEBUG
void ribi::QtTestImageCanvasMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    DotMatrixString();
    ImageCanvas();
    TextCanvas();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestImageCanvasMainDialog d;
  d.on_button_image_clicked();
}
#endif

void ribi::QtTestImageCanvasMainDialog::on_button_image_clicked()
{
  QFile qfile(":/ToolTestImageCanvas/images/R.png");
  const std::string filename { fileio::FileIo().GetTempFileName() };
  qfile.copy(filename.c_str());
  assert(fileio::FileIo().IsRegularFile(filename));
  m_canvas = ImageCanvas(
    filename,
    GetNcols(),
    GetColorSystem(),
    GetCoordinatSystem()
  );
  delete m_qtcanvas;
  m_qtcanvas = new QtCanvas;
  m_qtcanvas->SetImageCanvas(m_canvas);
  ui->verticalLayout->addWidget(m_qtcanvas);

  fileio::FileIo().DeleteFile(filename);
  assert(!fileio::FileIo().IsRegularFile(filename));
}

void ribi::QtTestImageCanvasMainDialog::on_box_n_cols_valueChanged(int)
{
  on_button_image_clicked();
}
