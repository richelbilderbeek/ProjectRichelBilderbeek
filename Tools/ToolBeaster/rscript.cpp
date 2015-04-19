#include "rscript.h"
/*

Rscript::Rscript(const std::string& log_filename)
{

}

std::ostream& operator<<(std::ostream& os, const Rscript& script)
{
  os
    << "# Load raw data" << '\n'
    << "data_raw <- read.table(\"" + script.GetLogFilename() + "\",header = TRUE)" << '\n'
    << "" << '\n'
    << "# Remove burn-in" << '\n'
    << "data <- tail(data_raw,n = nrow(data_raw) * 0.9)" << '\n'
    << "" << '\n'
    << "# Coalescent recovered" << '\n'
    << "svg(filename=\"coalescent_coalescent.svg\")" << '\n'
    << "par(mfrow=c(2,1))" << '\n'
    << "hist(data$popSize," << '\n'
    << "  main=paste(\"Recovery of coalescent (#taxa: \",n_taxa,\")\",sep=\"\")" << '\n'
    << ")" << '\n'
    << "hist(data$CoalescentConstant," << '\n'
    << "  main=paste(\"Recovery of coalescent (#taxa: \",n_taxa,\")\",sep=\"\")" << '\n'
    << ")" << '\n'
    << "par(mfrow=c(1,1))" << '\n'
    << "dev.off()" << '\n'
    << "" << '\n'
    << "# Compare Birth-Death and Coalescent their posterior" << '\n'
    << "svg(filename=\"birthdeath_coalescent.svg\")" << '\n'
    << "par(mfrow=c(2,1))" << '\n'
    << "hist(data_birthdeath_birthdeath$posterior," << '\n'
    << "  breaks=100," << '\n'
    << "  xlab=\"Posterior\"," << '\n'
    << "  ylab=\"Frequency\"," << '\n'
    << "  main=paste(\"Posterior recovery of birth-death\n(#taxa: \",n_taxa,\", birth rate: \",birth_rate,\", death rate: \",death_rate,\")\",sep=\"\")" << '\n'
    << ")" << '\n'
    << "hist(data_birthdeath_coalescent$posterior," << '\n'
    << "  breaks=100," << '\n'
    << "  xlab=\"Posterior\"," << '\n'
    << "  ylab=\"Frequency\"," << '\n'
    << "  main=paste(\"Posterior estimation of birth-death\nby coalescent model (#taxa: \",n_taxa,\")\",sep=\"\")" << '\n'
    << ")" << '\n'
    << "par(mfrow=c(1,1))" << '\n'
    << "dev.off()" << '\n'
  ;
  return os;
}
*/
