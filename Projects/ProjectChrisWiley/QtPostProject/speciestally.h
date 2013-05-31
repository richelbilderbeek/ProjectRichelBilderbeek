#ifndef SPECIESTALLY_H
#define SPECIESTALLY_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "bird.h"
//---------------------------------------------------------------------------
class SpeciesTally
{
  public:
  SpeciesTally() { reset(); }
  SpeciesTally(const std::vector<Female>& females, const std::vector<Male>& males)
  {
    reset();
    tallySpecies(females,males);
  }
  void reset();
  bool isNull() const;
  void tallySpecies(const std::vector<Female>& females, const std::vector<Male>& males);
  void operator+=(const SpeciesTally& speciesTally);
  void operator/=(const unsigned int& intValue);

  //Plain retrieval
  unsigned int getNmalesA()         const { return nMalesA;         }
  unsigned int getNmalesB()         const { return nMalesB;         }
  unsigned int getNfemalesA()       const { return nFemalesA;       }
  unsigned int getNfemalesB()       const { return nFemalesB;       }
  //Some group retrieval
  unsigned int getNallMalesA()   const { return nMalesA; }
  unsigned int getNallMalesB()   const { return nMalesB; }
  unsigned int getNallMales()    const { return nMalesA + nMalesB; }
  unsigned int getNallFemalesA() const { return nFemalesA; }
  unsigned int getNallFemalesB() const { return nFemalesB; }
  unsigned int getNallFemales()  const { return nFemalesA + nFemalesB; }
  unsigned int getNall()         const { return getNallFemales() + getNallMales(); }

  private:
  //The private variables it is all about
  unsigned int nMalesA;         //SpeciesValue < -0.5
  unsigned int nMalesB;         //SpeciesValue > 0.5
  unsigned int nFemalesA;       //SpeciesValue < -0.5
  unsigned int nFemalesB;       //SpeciesValue > 0.5
};
//---------------------------------------------------------------------------


#endif // SPECIESTALLY_H
