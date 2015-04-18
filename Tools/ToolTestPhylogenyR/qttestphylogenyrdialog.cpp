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
  //NewickToPhylogenyPng
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    try
    {
      PhylogenyR().NewickToPhylogenyPng(newick,temp_png_filename);
      ui->image_NewickToPhylogenyPng->setPixmap(QPixmap(temp_png_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToPhylogenyPng->setText(e.what());
    }
  }
  //NewickToPhylogenySvg
  {
    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    try
    {
      PhylogenyR().NewickToPhylogenySvg(newick,temp_svg_filename);
      ui->image_NewickToPhylogenySvg->setPixmap(QPixmap(temp_svg_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_svg_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToPhylogenySvg->setText(e.what());
    }
  }
  //NewickToLttPlot
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    try
    {
      PhylogenyR().NewickToLttPlot(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png);
      ui->image_NewickToLttPlot->setPixmap(QPixmap(temp_png_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToLttPlot->setText(e.what());
    }
  }
  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
  this->move( screen.center() - this->rect().center() );
}

QtTestPhylogenyRdialog::~QtTestPhylogenyRdialog()
{
  delete ui;
}
