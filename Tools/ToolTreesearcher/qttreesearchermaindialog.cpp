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

#include "birthdeathmodelhelper.h"
#include "birthdeathmodelparameters.h"
#include "fileio.h"
#include "ribi_rinside.h"
#include "phylogeny_r.h"
#include "trace.h"
#include "qtbirthdeathmodelparameterswidget.h"
#include "ui_qttreesearchermaindialog.h"

QtTreesearcherMainDialog::QtTreesearcherMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTreesearcherMainDialog),
  m_bd_parameters_widget{new QtBirthDeathModelParametersWidget},
  m_ltt_image{new QLabel},
  m_phylogeny{},
  m_tree_image{new QLabel}
{
  ui->setupUi(this);

  {
    assert(!this->ui->widget_center->layout());
    QHBoxLayout * const my_layout{new QHBoxLayout};
    ui->widget_center->setLayout(my_layout);
    my_layout->addWidget(m_ltt_image);
    my_layout->addWidget(m_tree_image);
    assert(this->ui->widget_center->layout());
  }

  {
    assert(!ui->page_parameters_bd->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_parameters_bd->setLayout(my_layout);
    my_layout->addWidget(m_bd_parameters_widget);
    assert(ui->page_parameters_bd->layout());

  }

  QObject::connect(m_bd_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnBirthDeathParametersChanged()));

  //Parse some libraries
  {
    auto& r = ribi::Rinside().Get();
    r.parseEvalQ("library(ape)");
    r.parseEvalQ("library(geiger)");
  }

  OnBirthDeathParametersChanged();
}

QtTreesearcherMainDialog::~QtTreesearcherMainDialog()
{
  delete ui;
}

void QtTreesearcherMainDialog::OnBirthDeathParametersChanged()
{
  const ribi::bdm::Parameters parameters {
    m_bd_parameters_widget->GetParameters()
  };

  const std::string phylogeny{
    ribi::bdm::Helper().CreateSimulatedPhylogeny(parameters)
  };

  SetPhylogeny(phylogeny);
}

void QtTreesearcherMainDialog::SetPhylogeny(const std::string& phylogeny)
{
  if (phylogeny == m_phylogeny) return;

  m_phylogeny = phylogeny;

  ribi::fileio::FileIo f;

  //LTT
  {
    const std::string png_filename{f.GetTempFileName(".png")};

    PhylogenyR().NewickToLttPlot(
      m_phylogeny,
      png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    if (f.IsRegularFile(png_filename))
    {
      m_ltt_image->setPixmap(QPixmap(png_filename.c_str()));
      f.DeleteFile(png_filename);
    }
  }
  //Phylogeny
  {
    const std::string png_filename{f.GetTempFileName(".png")};

    PhylogenyR().NewickToPhylogeny(
      m_phylogeny,
      png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    if (f.IsRegularFile(png_filename))
    {
      m_tree_image->setPixmap(QPixmap(png_filename.c_str()));
      f.DeleteFile(png_filename);
    }
  }
}
