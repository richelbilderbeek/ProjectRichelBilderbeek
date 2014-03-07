#ifndef CONCEPTMAPCOMPETENCY_H
#define CONCEPTMAPCOMPETENCY_H

#include <string>
#include <vector>

namespace ribi {

namespace cmap {

enum class Competency
{
  uninitialized = 0,   //Not yet set
  profession,          //NL: 'Beroepsdomein'
  organisations,       //NL: 'Organisaties'
  social_surroundings, //NL: 'Sociale omgeving'
  target_audience,     //NL 'Doelgroep'
  ti_knowledge,        //'Technical Instrumental', NL: 'Technische instrumentele kennis'
  prof_growth,         //Professionele groei
  misc                 //NL: 'Overig'
};

std::vector<Competency> GetAllCompetencies() noexcept;

std::string CompetencyToDutchStr(const Competency competency) noexcept;

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPCOMPETENCY_H
