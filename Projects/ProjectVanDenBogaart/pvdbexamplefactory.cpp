#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbexamplefactory.h"

#include "pvdbexample.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const boost::shared_ptr<pvdb::Example> pvdb::ExampleFactory::Create(const std::string& text, const pvdb::Competency& competency)
{
  boost::shared_ptr<pvdb::Example> example(new Example(text,competency));
  assert(example);
  return example;
}

const std::vector<boost::shared_ptr<pvdb::Example> > pvdb::ExampleFactory::GetTests()
{
  return
  {
    Create("Test example 0",Competency::profession),
    Create("Test example 1",Competency::organisations),
    Create("Test example 2",Competency::social_surroundings),
    Create("Test example 3",Competency::target_audience),
    Create("Test example 4",Competency::ti_knowledge),
    Create("Test example 5",Competency::prof_growth),
    Create("Test example 6",Competency::misc),
    Create("",Competency::uninitialized),
  };
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
