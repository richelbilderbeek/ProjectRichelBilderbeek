.libPaths(c(.libPaths(),"/home/p230198/.rkward/library"))

library(ape)
library(geiger)
library(phangorn)

#
# Analyze results
#

data_birthdeath_birthdeath_raw <- read.table("birthdeath_birthdeath.log",header = TRUE)
data_coalescent_coalescent_raw <- read.table("coalescent_coalescent.log",header = TRUE)

# Remove burn-in
data_birthdeath_birthdeath <- tail(data_birthdeath_birthdeath_raw,n = nrow(data_birthdeath_birthdeath_raw) * 0.9)
data_coalescent_coalescent <- tail(data_coalescent_coalescent_raw,n = nrow(data_coalescent_coalescent_raw) * 0.9)

names(data_birthdeath_birthdeath)

# Birth-Death recovered
svg(filename="birthdeath_birthdeath.svg")
hist(data_birthdeath_birthdeath$BirthDeath,
  main="Recovery of birth-death"
)
#par(mfrow=c(2,1))
#hist(data_birthdeath_birthdeath$birthRate2,
#  main=paste("Recovery of birth-death (#taxa: ",n_taxa,", birth rate: ",birth_rate,", death rate: ",death_rate,")",sep="")
#)
#hist(data_birthdeath_birthdeath$relativeDeathRate2,
#  main=paste("Recovery of birth-death (#taxa: ",n_taxa,", birth rate: ",birth_rate,", death rate: ",death_rate,")",sep="")
#)
par(mfrow=c(1,1))
dev.off()

# Coalescent recovered

svg(filename="coalescent_coalescent.svg")
par(mfrow=c(2,1))
hist(data_coalescent_coalescent$popSize,
  main="Recovery of coalescent its popSize"
)
hist(data_coalescent_coalescent$CoalescentConstant,
  main="Recovery of coalescent its CoalescentConstant"
)
par(mfrow=c(1,1))
dev.off()
