#include "qtbeastdisplay.h"

#include <cassert>
#include <fstream>
#include <functional>
#include <QLabel>

#include "beast.h"
#include "beastparameterfile.h"
#include "dnasequence.h"
#include "fileio.h"
#include "ui_qtbeastdisplay.h"
#include "dna_r.h"
#include "trace.h"

const std::string QtBeastDisplay::sm_fail{":-("};

QtBeastDisplay::QtBeastDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBeastDisplay)
{
  ui->setupUi(this);
}

QtBeastDisplay::~QtBeastDisplay()
{
  delete ui;
}

void QtBeastDisplay::Analyze(
  const std::vector<ribi::DnaSequence>& sequences,
  const int mcmc_chainlength
) noexcept
{
  AnalyzeBirthDeath(sequences,mcmc_chainlength);
  AnalyzeCoalescent(sequences,mcmc_chainlength);
}

void QtBeastDisplay::AnalyzeBirthDeath(
  const std::vector<ribi::DnaSequence>& sequences,
  const int mcmc_chainlength
) noexcept
{
  using ribi::fileio::FileIo;
  const BeastParameterFile::TreePrior tree_prior{
    BeastParameterFile::TreePrior::birth_death
  };
  const std::string alignment_base_filename{
    "birthdeath_birthdeath"
  };
  const std::string beast_input_parameters_filename{alignment_base_filename + ".xml"};
  const std::string beast_output_log_filename{alignment_base_filename + ".log"};
  const std::string beast_output_trees_filename{alignment_base_filename + ".trees"};
  const std::string output_png_filename{alignment_base_filename + ".png"};

  const BeastParameterFile beast_parameter_file(
    sequences,
    alignment_base_filename,
    mcmc_chainlength,
    tree_prior

  );
  {
    std::ofstream f(beast_input_parameters_filename.c_str());
    f << beast_parameter_file;
  }

  assert(FileIo().IsRegularFile(beast_input_parameters_filename));

  ribi::Beast().Run(
    beast_input_parameters_filename,
    beast_output_log_filename,
    beast_output_trees_filename
  );

  assert(FileIo().IsRegularFile(beast_output_log_filename));
  assert(FileIo().IsRegularFile(beast_output_trees_filename));
  ribi::Beast().AnalyzeBirthDeath(
    beast_output_log_filename,
    output_png_filename
  );

  if (!FileIo().IsRegularFile(output_png_filename))
  {
    this->ui->image_birth_death->setText(sm_fail.c_str());
  }
  this->ui->image_birth_death->setPixmap(
    QPixmap(output_png_filename.c_str())
  );
}


void QtBeastDisplay::AnalyzeCoalescent(
  const std::vector<ribi::DnaSequence>& sequences,
  const int mcmc_chainlength
) noexcept
{
  using ribi::fileio::FileIo;
  const BeastParameterFile::TreePrior tree_prior{
    BeastParameterFile::TreePrior::coalescent_constant_population
  };
  const std::string alignment_base_filename{
    "coalescent_coalescent"
  };
  const std::string beast_input_parameters_filename{alignment_base_filename + ".xml"};
  const std::string beast_output_log_filename{alignment_base_filename + ".log"};
  const std::string beast_output_trees_filename{alignment_base_filename + ".trees"};
  const std::string output_png_coalescent_constant_filename{alignment_base_filename + "_coalescent_constant.png"};
  const std::string output_png_popsize_filename{alignment_base_filename + "_popsize.png"};

  const BeastParameterFile beast_parameter_file(
    sequences,
    alignment_base_filename,
    mcmc_chainlength,
    tree_prior

  );
  {
    std::ofstream f(beast_input_parameters_filename.c_str());
    f << beast_parameter_file;
  }

  assert(FileIo().IsRegularFile(beast_input_parameters_filename));

  ribi::Beast().Run(
    beast_input_parameters_filename,
    beast_output_log_filename,
    beast_output_trees_filename
  );

  assert(FileIo().IsRegularFile(beast_output_log_filename));
  assert(FileIo().IsRegularFile(beast_output_trees_filename));

  ribi::Beast().AnalyzeCoalescent(
    beast_output_log_filename,
    output_png_coalescent_constant_filename,
    output_png_popsize_filename
  );

  if (!FileIo().IsRegularFile(output_png_coalescent_constant_filename))
  {
    ui->image_coalescent_coalescent_constant->setText(sm_fail.c_str());
  }
  else
  {
    ui->image_coalescent_coalescent_constant->setPixmap(
      QPixmap(output_png_coalescent_constant_filename.c_str())
    );
  }
  if (!FileIo().IsRegularFile(output_png_popsize_filename))
  {
    ui->image_coalescent_popsize->setText(sm_fail.c_str());
  }
  else
  {
    ui->image_coalescent_popsize->setPixmap(
      QPixmap(output_png_popsize_filename.c_str())
    );
  }
}
