#include "beastparameterfile.h"

#include <cassert>
#include <sstream>

#include "container.h"
#include "dnasequence.h"
//#include "fileio.h"

BeastParameterFile::BeastParameterFile(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& alignment_base_filename,
  const int mcmc_chainlength,
  const TreePrior tree_prior
) :
    m_alignment_base_filename{alignment_base_filename},
    m_mcmc_chainlength{mcmc_chainlength},
    m_sequences{sequences},
    m_tree_prior{tree_prior}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::string> BeastParameterFile::ToBirthDeathXml() const noexcept
{
  // Birth death model
  std::vector<std::string> v;
  v.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><beast beautitemplate='Standard' beautistatus='' namespace=\"beast.core:beast.evolution.alignment:beast.evolution.tree.coalescent:beast.core.util:beast.evolution.nuc:beast.evolution.operators:beast.evolution.sitemodel:beast.evolution.substitutionmodel:beast.evolution.likelihood\" version=\"2.0\">");
  v.push_back("");
  v.push_back("");
  const std::string filename_base{m_alignment_base_filename}; //Probably the alignment filename
  // I use the same (non-)indentation as BEAUti
  v.push_back("    <data");
  v.push_back("id=\"" + filename_base + "\"");
  v.push_back("name=\"alignment\">");
  for (const auto& p: m_sequences)
  {
    std::stringstream nextline;
    nextline
      << "                    <sequence id=\"seq_"
      << p.GetDescription()
      << "\" taxon=\""
      << p.GetDescription()
      << "\" totalcount=\"4\" value=\""
      << p.GetSequence()
      << "\"/>";
    ;
    v.push_back(nextline.str());
  }
  //This is generated if CCATACGCCC is present 10x
  /*
                      <sequence id="seq_CCATACGCCC" taxon="CCATACGCCC" totalcount="4" value="CCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCCCCATACGCCC"/>
  */
  // This works if all alignments are unique
  /*
  for (const std::string& s: m_alignments)
  {
    v.push_back("                    <sequence id=\"seq_" + s + "\" taxon=\"" + s + "\" totalcount=\"4\" value=\"" + s + "\"/>");
  }
  */
  v.push_back("                </data>");
  v.push_back("");
  v.push_back("");
  v.push_back("    ");
  v.push_back("");
  v.push_back("");
  v.push_back("    ");
  v.push_back("");
  v.push_back("");
  v.push_back("    ");
  v.push_back("<map name=\"Beta\">beast.math.distributions.Beta</map>");
  v.push_back("<map name=\"Exponential\">beast.math.distributions.Exponential</map>");
  v.push_back("<map name=\"InverseGamma\">beast.math.distributions.InverseGamma</map>");
  v.push_back("<map name=\"LogNormal\">beast.math.distributions.LogNormalDistributionModel</map>");
  v.push_back("<map name=\"Gamma\">beast.math.distributions.Gamma</map>");
  v.push_back("<map name=\"Uniform\">beast.math.distributions.Uniform</map>");
  v.push_back("<map name=\"prior\">beast.math.distributions.Prior</map>");
  v.push_back("<map name=\"LaplaceDistribution\">beast.math.distributions.LaplaceDistribution</map>");
  v.push_back("<map name=\"OneOnX\">beast.math.distributions.OneOnX</map>");
  v.push_back("<map name=\"Normal\">beast.math.distributions.Normal</map>");
  v.push_back("");
  v.push_back("");
  const std::string mcmc_chainlength_str{std::to_string(m_mcmc_chainlength)};
  assert(std::stoi(mcmc_chainlength_str) == m_mcmc_chainlength);
  v.push_back("<run chainLength=\"" + mcmc_chainlength_str + "\" id=\"mcmc\" spec=\"MCMC\">");
  v.push_back("    <state id=\"state\" storeEvery=\"5000\">");
  v.push_back("        <tree id=\"Tree.t:" + filename_base + "\" name=\"stateNode\">");
  v.push_back("            <taxonset id=\"TaxonSet." + filename_base + "\" spec=\"TaxonSet\">");
  v.push_back("                <data");
  v.push_back("idref=\"" + filename_base + "\"");
  v.push_back("name=\"alignment\"/>");
  v.push_back("            </taxonset>");
  v.push_back("        </tree>");
  v.push_back("        <stateNode id=\"RBcount.s:" + filename_base + "\" lower=\"0\" spec=\"parameter.IntegerParameter\" upper=\"5\">5</stateNode>");
  v.push_back("        <parameter dimension=\"5\" id=\"RBrates.s:" + filename_base + "\" lower=\"0.01\" name=\"stateNode\" upper=\"100.0\">1.0</parameter>");
  if (GetTreePrior() == BeastParameterFile::TreePrior::birth_death)
  {
    v.push_back("        <parameter id=\"birthRate2.t:" + filename_base + "\" lower=\"0.0\" name=\"stateNode\" upper=\"10000.0\">1.0</parameter>");
    v.push_back("        <parameter id=\"relativeDeathRate2.t:" + filename_base + "\" lower=\"0.0\" name=\"stateNode\" upper=\"1.0\">0.5</parameter>");
  }
  else
  {
    assert(GetTreePrior() == BeastParameterFile::TreePrior::coalescent_constant_population);
    v.push_back("        <parameter id=\"popSize.t:" + filename_base + "\" name=\"stateNode\">0.3</parameter>");
  }
  v.push_back("    </state>");
  v.push_back("");
  v.push_back("    <init estimate=\"false\" id=\"RandomTree.t:" + filename_base + "\" initial=\"@Tree.t:" + filename_base + "\" spec=\"beast.evolution.tree.RandomTree\" taxa=\"@" + filename_base + "\">");
  v.push_back("        <populationModel id=\"ConstantPopulation0.t:" + filename_base + "\" spec=\"ConstantPopulation\">");
  v.push_back("            <parameter id=\"randomPopSize.t:" + filename_base + "\" name=\"popSize\">1.0</parameter>");
  v.push_back("        </populationModel>");
  v.push_back("    </init>");
  v.push_back("");
  v.push_back("    <distribution id=\"posterior\" spec=\"util.CompoundDistribution\">");
  v.push_back("        <distribution id=\"prior\" spec=\"util.CompoundDistribution\">");
  if (GetTreePrior() == BeastParameterFile::TreePrior::birth_death)
  {
    v.push_back("            <distribution birthDiffRate=\"@birthRate2.t:" + filename_base + "\" id=\"BirthDeath.t:" + filename_base + "\" relativeDeathRate=\"@relativeDeathRate2.t:" + filename_base + "\" spec=\"beast.evolution.speciation.BirthDeathGernhard08Model\" tree=\"@Tree.t:" + filename_base + "\"/>");
  }
  else
  {
    assert(GetTreePrior() == BeastParameterFile::TreePrior::coalescent_constant_population);
    v.push_back("            <distribution id=\"CoalescentConstant.t:" + filename_base + "\" spec=\"Coalescent\">");
    v.push_back("                <populationModel id=\"ConstantPopulation.t:" + filename_base + "\" popSize=\"@popSize.t:" + filename_base + "\" spec=\"ConstantPopulation\"/>");
    v.push_back("                <treeIntervals id=\"TreeIntervals.t:" + filename_base + "\" spec=\"TreeIntervals\" tree=\"@Tree.t:" + filename_base + "\"/>");
    v.push_back("            </distribution>");
  }
  v.push_back("            <distribution count=\"@RBcount.s:" + filename_base + "\" id=\"RBprior.s:" + filename_base + "\" spec=\"beast.math.distributions.RBPrior\" x=\"@RBrates.s:" + filename_base + "\">");
  v.push_back("                <Gamma id=\"Gamma.0\" name=\"distr\">");
  v.push_back("                    <parameter id=\"RealParameter.0\" lower=\"0.0\" name=\"alpha\" upper=\"0.0\">0.2</parameter>");
  v.push_back("                    <parameter id=\"RealParameter.01\" lower=\"0.0\" name=\"beta\" upper=\"0.0\">5.0</parameter>");
  v.push_back("                </Gamma>");
  v.push_back("            </distribution>");
  if (GetTreePrior() == BeastParameterFile::TreePrior::birth_death)
  {
    v.push_back("            <prior id=\"BirthRatePrior.t:" + filename_base + "\" name=\"distribution\" x=\"@birthRate2.t:" + filename_base + "\">");
    v.push_back("                <Uniform id=\"Uniform.0\" name=\"distr\" upper=\"1000.0\"/>");
    v.push_back("            </prior>");
    v.push_back("            <prior id=\"DeathRatePrior.t:" + filename_base + "\" name=\"distribution\" x=\"@relativeDeathRate2.t:" + filename_base + "\">");
    v.push_back("                <Uniform id=\"Uniform.01\" name=\"distr\"/>");
  }
  else
  {
    assert(GetTreePrior() == BeastParameterFile::TreePrior::coalescent_constant_population);
    v.push_back("            <prior id=\"PopSizePrior.t:" + filename_base + "\" name=\"distribution\" x=\"@popSize.t:" + filename_base + "\">");
    v.push_back("                <OneOnX id=\"OneOnX.0\" name=\"distr\"/>");
  }
  v.push_back("            </prior>");
  v.push_back("        </distribution>");
  v.push_back("        <distribution id=\"likelihood\" spec=\"util.CompoundDistribution\">");
  v.push_back("            <distribution data=\"@" + filename_base + "\" id=\"treeLikelihood." + filename_base + "\" spec=\"TreeLikelihood\" tree=\"@Tree.t:" + filename_base + "\">");
  v.push_back("                <siteModel id=\"SiteModel.s:" + filename_base + "\" spec=\"SiteModel\">");
  v.push_back("                    <parameter estimate=\"false\" id=\"mutationRate.s:" + filename_base + "\" name=\"mutationRate\">1.0</parameter>");
  v.push_back("                    <parameter estimate=\"false\" id=\"gammaShape.s:" + filename_base + "\" name=\"shape\">1.0</parameter>");
  v.push_back("                    <parameter estimate=\"false\" id=\"proportionInvariant.s:" + filename_base + "\" lower=\"0.0\" name=\"proportionInvariant\" upper=\"1.0\">0.0</parameter>");
  v.push_back("                    <substModel count=\"@RBcount.s:" + filename_base + "\" id=\"RB.s:" + filename_base + "\" rates=\"@RBrates.s:" + filename_base + "\" spec=\"RB\">");
  v.push_back("                        <frequencies data=\"@" + filename_base + "\" id=\"freqs.s:" + filename_base + "\" spec=\"Frequencies\"/>");
  v.push_back("                    </substModel>");
  v.push_back("                </siteModel>");
  v.push_back("                <branchRateModel id=\"StrictClock.c:" + filename_base + "\" spec=\"beast.evolution.branchratemodel.StrictClockModel\">");
  v.push_back("                    <parameter estimate=\"false\" id=\"clockRate.c:" + filename_base + "\" name=\"clock.rate\">1.0</parameter>");
  v.push_back("                </branchRateModel>");
  v.push_back("            </distribution>");
  v.push_back("        </distribution>");
  v.push_back("        <distribution id=\"fossilCalibrations\" spec=\"util.CompoundDistribution\"/>");
  v.push_back("    </distribution>");
  v.push_back("");
  v.push_back("    <operator id=\"treeScaler.t:" + filename_base + "\" scaleFactor=\"0.5\" spec=\"ScaleOperator\" tree=\"@Tree.t:" + filename_base + "\" weight=\"3.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"treeRootScaler.t:" + filename_base + "\" rootOnly=\"true\" scaleFactor=\"0.5\" spec=\"ScaleOperator\" tree=\"@Tree.t:" + filename_base + "\" weight=\"3.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"UniformOperator.t:" + filename_base + "\" spec=\"Uniform\" tree=\"@Tree.t:" + filename_base + "\" weight=\"30.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"SubtreeSlide.t:" + filename_base + "\" spec=\"SubtreeSlide\" tree=\"@Tree.t:" + filename_base + "\" weight=\"15.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"narrow.t:" + filename_base + "\" spec=\"Exchange\" tree=\"@Tree.t:" + filename_base + "\" weight=\"15.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"wide.t:" + filename_base + "\" isNarrow=\"false\" spec=\"Exchange\" tree=\"@Tree.t:" + filename_base + "\" weight=\"3.0\"/>");
  v.push_back("");
  v.push_back("    <operator id=\"WilsonBalding.t:" + filename_base + "\" spec=\"WilsonBalding\" tree=\"@Tree.t:" + filename_base + "\" weight=\"3.0\"/>");
  v.push_back("");
  v.push_back("    <operator count=\"@RBcount.s:" + filename_base + "\" id=\"RBOperator.s:" + filename_base + "\" rates=\"@RBrates.s:" + filename_base + "\" spec=\"RBOperator\" weight=\"1.0\"/>");
  v.push_back("");
  v.push_back("    <operator count=\"@RBcount.s:" + filename_base + "\" id=\"RBratescaler.s:" + filename_base + "\" parameter=\"@RBrates.s:" + filename_base + "\" scaleFactor=\"0.5\" spec=\"RBScaleOperator\" weight=\"1.0\"/>");
  v.push_back("");
  if (GetTreePrior() == BeastParameterFile::TreePrior::birth_death)
  {
    v.push_back("    <operator id=\"BirthRateScaler.t:" + filename_base + "\" parameter=\"@birthRate2.t:" + filename_base + "\" scaleFactor=\"0.75\" spec=\"ScaleOperator\" weight=\"3.0\"/>");
    v.push_back("");
    v.push_back("    <operator id=\"DeathRateScaler.t:" + filename_base + "\" parameter=\"@relativeDeathRate2.t:" + filename_base + "\" scaleFactor=\"0.75\" spec=\"ScaleOperator\" weight=\"3.0\"/>");
  }
  else
  {
    assert(GetTreePrior() == BeastParameterFile::TreePrior::coalescent_constant_population);
    v.push_back("    <operator id=\"PopSizeScaler.t:" + filename_base + "\" parameter=\"@popSize.t:" + filename_base + "\" scaleFactor=\"0.75\" spec=\"ScaleOperator\" weight=\"3.0\"/>");
  }
  v.push_back("");
  v.push_back("    <logger fileName=\"" + filename_base + ".log\" id=\"tracelog\" logEvery=\"1000\" model=\"@posterior\" sanitiseHeaders=\"true\" sort=\"smart\">");
  v.push_back("        <log idref=\"posterior\"/>");
  v.push_back("        <log idref=\"likelihood\"/>");
  v.push_back("        <log idref=\"prior\"/>");
  v.push_back("        <log idref=\"treeLikelihood." + filename_base + "\"/>");
  v.push_back("        <log id=\"TreeHeight.t:" + filename_base + "\" spec=\"beast.evolution.tree.TreeHeightLogger\" tree=\"@Tree.t:" + filename_base + "\"/>");
  v.push_back("        <log idref=\"RBcount.s:" + filename_base + "\"/>");
  v.push_back("        <parameter idref=\"RBrates.s:" + filename_base + "\" name=\"log\"/>");
  if (GetTreePrior() == BeastParameterFile::TreePrior::birth_death)
  {
    v.push_back("        <log idref=\"BirthDeath.t:" + filename_base + "\"/>");
  }
  else
  {
    assert(GetTreePrior() == BeastParameterFile::TreePrior::coalescent_constant_population);
    v.push_back("        <parameter idref=\"popSize.t:" + filename_base + "\" name=\"log\"/>");
    v.push_back("        <log idref=\"CoalescentConstant.t:" + filename_base + "\"/>");
  }
  v.push_back("    </logger>");
  v.push_back("");
  v.push_back("    <logger id=\"screenlog\" logEvery=\"1000\">");
  v.push_back("        <log idref=\"posterior\"/>");
  v.push_back("        <log arg=\"@posterior\" id=\"ESS.0\" spec=\"util.ESS\"/>");
  v.push_back("        <log idref=\"likelihood\"/>");
  v.push_back("        <log idref=\"prior\"/>");
  v.push_back("    </logger>");
  v.push_back("");
  v.push_back("    <logger fileName=\"$(tree).trees\" id=\"treelog.t:" + filename_base + "\" logEvery=\"1000\" mode=\"tree\">");
  v.push_back("        <log id=\"TreeWithMetaDataLogger.t:" + filename_base + "\" spec=\"beast.evolution.tree.TreeWithMetaDataLogger\" tree=\"@Tree.t:" + filename_base + "\"/>");
  v.push_back("    </logger>");
  v.push_back("");
  v.push_back("</run>");
  v.push_back("");
  v.push_back("</beast>");
  return v;
}


std::ostream& operator<<(std::ostream& os, const BeastParameterFile file)
{
  const std::vector<std::string> xml{
    file.ToBirthDeathXml()
  };

  const std::string s{
    ribi::Container().ContainerToStr(xml,"\n")
  };
  os << s;
  return os;
}
