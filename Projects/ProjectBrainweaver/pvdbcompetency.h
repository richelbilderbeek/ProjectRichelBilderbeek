#ifndef PVDBCOMPETENCY_H
#define PVDBCOMPETENCY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>

namespace pvdb {

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

const std::vector<Competency> GetAllCompetencies();

const std::string CompetencyToDutchStr(const Competency competency);

} //~namespace pvdb

#endif // PVDBCOMPETENCY_H
