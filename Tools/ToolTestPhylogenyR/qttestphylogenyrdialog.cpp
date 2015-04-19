#include "qttestphylogenyrdialog.h"

#include <QDesktopWidget>
#include <QPixmap>

#include "fileio.h"
#include "phylogeny_r.h"
#include "ui_qttestphylogenyrdialog.h"

QtTestPhylogenyRdialog::QtTestPhylogenyRdialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestPhylogenyRdialog)
{
  ui->setupUi(this);
  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestPhylogenyRdialog::~QtTestPhylogenyRdialog()
{
  delete ui;
}

void QtTestPhylogenyRdialog::DisplayNewickExtant(const std::string& newick)
{
  const std::string newick_extant{PhylogenyR().DropExtict(newick)};
  ui->edit_extant->setText(newick_extant.c_str());
}

void QtTestPhylogenyRdialog::DisplayNewickToPhylogenyPng(const std::string& newick)
{
  QLabel * const label{ui->image_NewickToPhylogenyPng};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));

    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(e.what());
  }
}

void QtTestPhylogenyRdialog::DisplayNewickToPhylogenyExtantPng(
  const std::string& newick)
{
  QLabel * const label{ui->image_NewickToPhylogenyExtant};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));

    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(e.what());
  }
}

void QtTestPhylogenyRdialog::DisplayNewickToLttPlot(const std::string& newick)
{
  QLabel * const label{ui->image_NewickToLttPlot};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(e.what());
  }
}

void QtTestPhylogenyRdialog::DisplayNewickToLttPlotExtant(const std::string& newick)
{
  QLabel * const label{ui->image_NewickToLttPlotExtant};
  //NewickToLttPlot of extant species
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    try
    {
      PhylogenyR().NewickToLttPlot(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png,false);
      label->setPixmap(QPixmap(temp_png_filename.c_str()));
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      label->setText(e.what());
    }
  }
}

std::string QtTestPhylogenyRdialog::GetNewick() const noexcept
{
  return ui->edit_newick->text().toStdString();
}

void QtTestPhylogenyRdialog::on_button_show_clicked()
{
  const std::string newick{GetNewick()};
  DisplayNewickExtant(newick);
  this->repaint();
  DisplayNewickToPhylogenyPng(newick);
  this->repaint();
  DisplayNewickToPhylogenyExtantPng(newick);
  this->repaint();
  DisplayNewickToLttPlot(newick);
  this->repaint();
  DisplayNewickToLttPlotExtant(newick);
  this->repaint();

}
