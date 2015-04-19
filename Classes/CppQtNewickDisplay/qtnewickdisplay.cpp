#include "qtnewickdisplay.h"

#include <cassert>
#include <QLabel>

#include "fileio.h"
#include "ui_qtnewickdisplay.h"
#include "phylogeny_r.h"
#include "newickutils.h"

QtNewickDisplay::QtNewickDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtNewickDisplay)
{
  ui->setupUi(this);
}

QtNewickDisplay::~QtNewickDisplay()
{
  delete ui;
}

void QtNewickDisplay::DisplayNewick(const std::string& newick) noexcept
{
  ui->line_newick->setText(newick.c_str());
}

void QtNewickDisplay::DisplayNewickExtant(const std::string& newick_all) noexcept
{
  try
  {
    const std::string newick_extant{PhylogenyR().DropExtict(newick_all)};
    ui->line_newick_extant->setText(newick_extant.c_str());
  }
  catch (std::runtime_error& e)
  {
    ui->line_newick_extant->setText(":-(");
  }
}

void QtNewickDisplay::DisplayNewickToLttPlot(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_lttPlot};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png);
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //label->setText(e.what());
    label->setText(":-(");
  }
}

void QtNewickDisplay::DisplayNewickToLttPlotExtant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_lttPlot_extant};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToLttPlot(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false //show_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(":-(");
    //label->setText(e.what());
  }
}

void QtNewickDisplay::DisplayPhylogenyNewickUtilsAll(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_newickutils};
  try
  {
    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_svg_filename));
    NewickUtils().NewickToPhylogeny(
      newick,
      temp_svg_filename,
      NewickUtils::GraphicsFormat::svg
    );
    label->setPixmap(QPixmap(temp_svg_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }

}

void QtNewickDisplay::DisplayPhylogenyNewickUtilsExtant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_extant_newickutils};
  try
  {
    const std::string temp_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename));
    NewickUtils().NewickToPhylogeny(
      newick,
      temp_filename,
      NewickUtils::GraphicsFormat::svg,
      false //plot_fossils
    );
    label->setPixmap(QPixmap(temp_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }
  catch (std::logic_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }

}

void QtNewickDisplay::DisplayPhylogenyRall(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny};
  try
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
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
    //std::clog << e.what() << '\n';
    label->setText(":-(");
  }
}

void QtNewickDisplay::DisplayPhylogenyRextant(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_phylogeny_extant};
  try
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      false //plot_fossils
    );
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    label->setText(":-(");
    //std::clog << e.what() << '\n';
  }

}

void QtNewickDisplay::SetNewick(const std::string& newick) noexcept
{
  DisplayNewick(newick);
  DisplayNewickExtant(newick);
  DisplayPhylogenyRall(newick);
  DisplayPhylogenyRextant(newick);
  DisplayPhylogenyNewickUtilsAll(newick);
  DisplayPhylogenyNewickUtilsExtant(newick);
  DisplayNewickToLttPlot(newick);
  DisplayNewickToLttPlotExtant(newick);
}
