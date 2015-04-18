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
  const std::string newick{"(L:1,(((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):1,(GD:1,ID:1):1,BD:1):3,(AC:1,EC:1):1,(((TC:1,FD:2):1,QC:1,RC:1):1,((((AE:1,BE:1):1,(WD:1,YD:1):1):1,HD:1):2,MC:1):1):1):3);"};
  //NewickToPhylogenyPng
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    try
    {
      PhylogenyR().NewickToPhylogeny(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png);
      ui->image_NewickToPhylogenyPng->setPixmap(QPixmap(temp_png_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToPhylogenyPng->setText(e.what());
    }
  }
  //NewickToPhylogenyExtant
  {
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
      ui->image_NewickToPhylogenyExtant->setPixmap(QPixmap(temp_png_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToPhylogenyExtant->setText(e.what());
    }
  }
  //NewickToLttPlot
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
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
  //NewickToLttPlot of extant species
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    try
    {
      PhylogenyR().NewickToLttPlot(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png,false);
      ui->image_NewickToLttPlotExtant->setPixmap(QPixmap(temp_png_filename.c_str()));

      //Delete the temporary file
      ribi::fileio::FileIo().DeleteFile(temp_png_filename);
    }
    catch (std::runtime_error& e)
    {
      ui->image_NewickToLttPlotExtant->setText(e.what());
    }
  }
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
