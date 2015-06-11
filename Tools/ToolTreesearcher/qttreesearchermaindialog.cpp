#include "qttreesearchermaindialog.h"

#include <cassert>

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QTextStream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "RInside.h"
#pragma GCC diagnostic pop

#include "fileio.h"
#include "ribi_rinside.h"

#include "ui_qttreesearchermaindialog.h"

QtTreesearcherMainDialog::QtTreesearcherMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTreesearcherMainDialog),
  m_tree_image{new QLabel}
{
  ui->setupUi(this);

  {
    assert(!this->ui->widget_center->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->widget_center->setLayout(my_layout);
    my_layout->addWidget(m_tree_image);
    assert(this->ui->widget_center->layout());
  }


  QObject::connect(this->ui->box_birth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_death_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_n_taxa,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));

  //Parse some libraries
  {
    auto& r = ribi::Rinside().Get();
    r.parseEvalQ("library(ape)");
    r.parseEvalQ("library(geiger)");
  }

  OnAnyChange();
}

QtTreesearcherMainDialog::~QtTreesearcherMainDialog()
{
  delete ui;
}

void QtTreesearcherMainDialog::OnAnyChange()
{
  ribi::fileio::FileIo f;
  auto& r = ribi::Rinside().Get();
  const std::string png_filename{f.GetTempFileName(".png")};

  r.parseEvalQ("library(ape)");
  r.parseEvalQ("library(geiger)");
  r["n_taxa"] = ui->box_n_taxa->value();
  r["birth_rate"] = ui->box_birth_rate->value();
  r["death_rate"] = ui->box_death_rate->value();
  r.parseEval("print(n_taxa)");
  r.parseEval("print(birth_rate)");
  r.parseEval("print(death_rate)");

  r.parseEval("tree_full <- sim.bdtree(birth_rate, death_rate, stop=\"taxa\",n=n_taxa)");
  r.parseEval("print(tree_full)");


  const Rcpp::String r_newick = r.parseEval("write.tree(phylogeny)");
  const std::string newick = r_newick;
  std::cout << newick;
  return;
  //r.parseEvalQ("tree_reconstructed <- drop.extinct(tree_full)");
  //r.parseEvalQ("print(tree_reconstructed)");
  r["png_filename"] = png_filename;
  r.parseEvalQ("png(filename=png_filename)");
  r.parseEvalQ("plot(tree_full)");
  r.parseEvalQ("dev.off()");
  m_tree_image->setPixmap(QPixmap(png_filename.c_str()));
  f.DeleteFile(png_filename);

}
