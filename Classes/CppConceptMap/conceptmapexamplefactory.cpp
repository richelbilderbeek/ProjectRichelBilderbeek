#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "conceptmapexamplefactory.h"

#include "conceptmapexample.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Example> ribi::cmap::ExampleFactory::Create(
  const std::string& text,
  const cmap::Competency& competency,
  const bool is_complex,
  const bool is_concrete,
  const bool is_specific)
{
  boost::shared_ptr<cmap::Example> example(
    new Example(
      text,
      competency,
      is_complex,
      is_concrete,
      is_specific
    )
  );
  assert(example);
  return example;
}

const std::vector<boost::shared_ptr<ribi::cmap::Example> > ribi::cmap::ExampleFactory::GetTests()
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
