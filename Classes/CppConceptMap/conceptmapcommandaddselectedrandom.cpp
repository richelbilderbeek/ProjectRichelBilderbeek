#include "conceptmapcommandaddselectedrandom.h"

#include <cassert>

#include "conceptmap.h"

#include "conceptmaphelper.h"
#include "trace.h"

ribi::cmap::CommandAddSelectedRandom::CommandAddSelectedRandom(const boost::shared_ptr<ConceptMap> concept_map)
  :
    m_concept_map{concept_map},
    m_new_selected{concept_map->GetSelected()},
    m_old_selected{concept_map->GetSelected()}
{
  this->setText("add selected random");

  assert(concept_map);
  if (concept_map->GetNodes().empty())
  {
    throw std::logic_error("AddSelected needs nodes to focus on");
  }
  const auto to_add = m_concept_map->GetRandomNodes(AddConst(concept_map->GetSelectedNodes()));
  if (to_add.empty())
  {
    std::stringstream s;
    s << "AddSelected needs non-focused nodes to focus on,"
      << "currently has " << concept_map->GetSelectedNodes().size()
      << " selected"
    ;
    throw std::logic_error(s.str());
  }
  std::copy(
    std::begin(to_add),
    std::end(to_add),
    std::back_inserter(m_new_selected.second)
  );
  assert(m_new_selected.second.size() > m_old_selected.second.size());
}

void ribi::cmap::CommandAddSelectedRandom::redo()
{
  m_concept_map->SetSelected(m_new_selected);
}

void ribi::cmap::CommandAddSelectedRandom::undo()
{
  m_concept_map->SetSelected(m_old_selected);
}
