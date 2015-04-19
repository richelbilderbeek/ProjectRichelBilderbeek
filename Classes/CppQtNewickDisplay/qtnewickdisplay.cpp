#include "qtnewickdisplay.h"

#include <cassert>
#include <functional>
#include <QLabel>

#include "fileio.h"
#include "ui_qtnewickdisplay.h"
#include "phylogeny_r.h"
#include "newickutils.h"

const std::string QtNewickDisplay::sm_fail{":-("};

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

/*
void QtNewickDisplay::DisplayBranchLengthsAll(const std::string& newick) noexcept
{
  QLabel * const label{ui->image_branch_lengths_all};
  const std::string temp_png_filename{
    ribi::fileio::FileIo().GetTempFileName(".png")
  };
  try
  {
    PhylogenyR().NewickToBranchLengths(newick,temp_png_filename,PhylogenyR::GraphicsFormat::png);
    label->setPixmap(QPixmap(temp_png_filename.c_str()));
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //label->setText(e.what());
    label->setText(sm_fail.c_str());
  }
}
*/

void QtNewickDisplay::DisplayNewickAll(const std::string& newick) noexcept
{
  ui->line_newick->setText(newick.c_str());
}

void QtNewickDisplay::DisplayNewickExtant(const std::string& newick_all) noexcept
{
  try
  {
    const std::string newick_extant{PhylogenyR().DropExtinct(newick_all)};
    ui->line_newick_extant->setText(newick_extant.c_str());
  }
  catch (std::runtime_error& e)
  {
    ui->line_newick_extant->setText(sm_fail.c_str());
  }
}

void QtNewickDisplay::DisplayNewickToLttPlotAll(const std::string& newick) noexcept
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
    label->setText(sm_fail.c_str());
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
    label->setText(sm_fail.c_str());
    //label->setText(e.what());
  }
}

void QtNewickDisplay::DisplayPhylogeny(
  const std::string& newick,
  const Lineages lineages,
  const Tool tool
) noexcept
{
  QLabel * label{nullptr};
  std::function<void(const std::string&, const std::string&)> f;
  if (lineages == Lineages::all && tool == Tool::NewickUtils)
  {
    label = ui->image_phylogeny_newickutils_all;
    f = [](const std::string& newick, const std::string& filename)
    {
      NewickUtils().NewickToPhylogeny(
      newick,
      filename,
      NewickUtils::GraphicsFormat::svg,
      true //plot_fossils
      );
    };
  }
  if (lineages == Lineages::extant && tool == Tool::NewickUtils)
  {
    label = ui->image_phylogeny_newickutils_extant;
    f = [](const std::string& newick, const std::string& filename)
    {
      NewickUtils().NewickToPhylogeny(
      newick,
      filename,
      NewickUtils::GraphicsFormat::svg,
      false //plot_fossils
      );
    };
  }
  if (lineages == Lineages::all && tool == Tool::PhylogenyR)
  {
    label = ui->image_phylogeny_phylogenyr_all;
    f = [](const std::string& newick, const std::string& filename)
    {
      PhylogenyR().NewickToPhylogeny(
      newick,
      filename,
      PhylogenyR::GraphicsFormat::png,
      true //plot_fossils
      );
    };
  }
  if (lineages == Lineages::extant && tool == Tool::PhylogenyR)
  {
    label = ui->image_phylogeny_phylogenyr_extant;
    f = [](const std::string& newick, const std::string& filename)
    {
      PhylogenyR().NewickToPhylogeny(
      newick,
      filename,
      PhylogenyR::GraphicsFormat::png,
      false //plot_fossils
      );
    };
  }
  assert(label);
  try
  {
    const std::string temp_filename{
      ribi::fileio::FileIo().GetTempFileName("") //Cannot put .svg or .png here, as images won't display then
    };
    assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename));
    f(newick,temp_filename);
    label->setPixmap(QPixmap(temp_filename.c_str()));
    //Delete the temporary file
    ribi::fileio::FileIo().DeleteFile(temp_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(sm_fail.c_str());
  }
}

/*
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
    label->setText(sm_fail.c_str());
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
    label->setText(sm_fail.c_str());
  }
  catch (std::logic_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(sm_fail.c_str());
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
    ribi::fileio::FileIo().DeleteFile(temp_png_filename);
  }
  catch (std::runtime_error& e)
  {
    //std::clog << e.what() << '\n';
    label->setText(sm_fail.c_str());
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
    label->setText(sm_fail.c_str());
    //std::clog << e.what() << '\n';
  }

}
*/
void QtNewickDisplay::SetNewick(const std::string& newick) noexcept
{
  DisplayNewickAll(newick);
  this->repaint();
  //DisplayPhylogenyNewickUtilsAll(newick);
  DisplayPhylogeny(newick,Lineages::all,Tool::NewickUtils);
  this->repaint();
  DisplayNewickExtant(newick);
  this->repaint();
  if (ui->line_newick_extant->text().toStdString() == sm_fail)
  {
    ui->image_lttPlot->setText(sm_fail.c_str());
    ui->image_lttPlot_extant->setText(sm_fail.c_str());
    ui->image_phylogeny_newickutils_extant->setText(sm_fail.c_str());
    ui->image_phylogeny_phylogenyr_all->setText(sm_fail.c_str());
    ui->image_phylogeny_phylogenyr_extant->setText(sm_fail.c_str());
    return;
  }
  //DisplayPhylogenyNewickUtilsExtant(newick);
  DisplayPhylogeny(newick,Lineages::extant,Tool::NewickUtils);
  this->repaint();
  //DisplayPhylogenyRall(newick);
  DisplayPhylogeny(newick,Lineages::all,Tool::PhylogenyR);
  this->repaint();
  //DisplayPhylogenyRextant(newick);
  DisplayPhylogeny(newick,Lineages::extant,Tool::PhylogenyR);
  this->repaint();
  DisplayNewickToLttPlotAll(newick);
  this->repaint();
  DisplayNewickToLttPlotExtant(newick);
  this->repaint();
}
