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
  //AnalyzeCoalescent(sequences,mcmc_chainlength);
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

  //const std::string fasta_output_filename{alignment_base_filename + ".fas"};

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

  /*
  const FastaFile fasta_file(
    sequences
  );
  {
    std::ofstream f(fasta_output_filename);
    f << fasta_file;
  }
  std::cout << fasta_file << std::endl;
  */

  assert(FileIo().IsRegularFile(beast_input_parameters_filename));

  Beast().Run(
    beast_input_parameters_filename,
    beast_output_log_filename,
    beast_output_trees_filename
  );

  assert(FileIo().IsRegularFile(beast_output_log_filename));
  assert(FileIo().IsRegularFile(beast_output_trees_filename));

  Beast().AnalyzeBirthDeath(
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

/*
void QtBeastDisplay::AnalyzeCoalescent(
  const std::vector<ribi::DnaSequence>& sequences,
  const int mcmc_chainlength
) noexcept
{
  const bool verbose{true};
  const BeastParameterFile::TreePrior tree_prior{
    BeastParameterFile::TreePrior::coalescent_constant_population
  };
  {
    const std::string alignment_base_filename{
      tree_prior == BeastParameterFile::TreePrior::birth_death
        ? "birthdeath_birthdeath"
        : "coalescent_coalescent"
    };
    const std::string beast_xml_output_filename{alignment_base_filename + ".xml"};
    const std::string fasta_output_filename{alignment_base_filename + ".fas"};

    if (verbose) { TRACE("3) Create BEAST2 XML parameter file"); }

    const BeastParameterFile beast_parameter_file(
      sequences,
      alignment_base_filename,
      mcmc_chainlength,
      tree_prior

    );
    {
      std::ofstream f(beast_xml_output_filename.c_str());
      f << beast_parameter_file;
    }

    Beast().Run(
      beast_xml_output_filename,
      alignment_base_filename + ".log",
      alignment_base_filename + ".trees"
    );
    assert(ribi::fileio::FileIo().IsRegularFile(beast_xml_output_filename));
  }

  if (verbose) { TRACE("Interpret BEAST2 results"); }
  {
    const std::string s{"Beaster.R"};
    if (!Helper().IsRegularFileStl(s))
    {
      QFile((std::string(":/files/") + s).c_str()).copy(s.c_str());
    }
    assert(Helper().IsRegularFileStl(s));
    std::system("Rscript Beaster.R");
  }

  if (verbose) { TRACE("Check BEAST2 results"); }
  if ( Helper().IsRegularFileStl("coalescent_coalescent.svg")
    && Helper().IsRegularFileStl("birthdeath_birthdeath.svg")
  )
  {
    std::clog << "OK" << std::endl;
  }
  else
  {
    std::clog << "ERROR: final SVGs not created" << std::endl;
  }
}
*/
