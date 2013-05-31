//---------------------------------------------------------------------------
#include "speciestally.h"
//---------------------------------------------------------------------------
void SpeciesTally::tallySpecies(const std::vector<Female>& females, const std::vector<Male>& males)
{
  //Females first
  const unsigned int nFemales = females.size();
  for (unsigned i=0; i<nFemales; ++i)
  {
    const enumSpecies species = females[i].species;
    if (species==piedFlycatcher) ++(nFemalesA);
    else                         ++(nFemalesB);
  }
  //Tally the men
  const unsigned int nMales = males.size();
  for (unsigned i=0; i<nMales; ++i)
  {
    const enumSpecies species = males[i].species;
    if (species==piedFlycatcher) ++(nMalesA);
    else                         ++(nMalesB);
  }

  /*
  //Females first
  const unsigned int nFemales = females.size();
  for (unsigned i=0; i<nFemales; ++i)
  {
    const double descent = females[i].descent;
    if (descent < -0.5)     ++(nFemalesA);
    else if (descent < 0.0) ++(nFemaleHybridsA);
    else if (descent < 0.5) ++(nFemaleHybridsB);
    else                         ++(nFemalesB);
  }
  //Tally the men
  const unsigned int nMales = males.size();
  for (unsigned i=0; i<nMales; ++i)
  {
    const double descent = males[i].descent;
    if (descent < -0.5)     ++(nMalesA);
    else if (descent < 0.0) ++(nMaleHybridsA);
    else if (descent < 0.5) ++(nMaleHybridsB);
    else                         ++(nMalesB);
  }
  */
}
//---------------------------------------------------------------------------
void SpeciesTally::reset()
{
  nMalesA = 0;
  nMalesB = 0;
  nFemalesA = 0;
  nFemalesB = 0;
}
//---------------------------------------------------------------------------
bool SpeciesTally::isNull() const
{
  if (nMalesA>0) return false;
  if (nMalesB>0) return false;
  if (nFemalesA>0) return false;
  if (nFemalesB>0) return false;
  return true;
}
//---------------------------------------------------------------------------
void SpeciesTally::operator+=(const SpeciesTally& speciesTally)
{
  nMalesA+=speciesTally.nMalesA;
  nMalesB+=speciesTally.nMalesB;
  nFemalesA+=speciesTally.nFemalesA;
  nFemalesB+=speciesTally.nFemalesB;
}
//---------------------------------------------------------------------------
void SpeciesTally::operator/=(const unsigned int& intValue)
{
  nMalesA/=intValue;
  nMalesB/=intValue;
  nFemalesA/=intValue;
  nFemalesB/=intValue;
}
//---------------------------------------------------------------------------
