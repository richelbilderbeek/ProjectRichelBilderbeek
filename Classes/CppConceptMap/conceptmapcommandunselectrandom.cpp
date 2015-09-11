#include "conceptmapcommandunselectrandom.h"

#include <cassert>
#include <stdexcept>

#include "conceptmap.h"

#include "conceptmaphelper.h"
#include "trace.h"

ribi::cmap::CommandUnselectRandom::CommandUnselectRandom(
  const boost::shared_ptr<ConceptMap> concept_map
) :
    m_new_selected{concept_map->GetSelected()},
    m_old_selected{concept_map->GetSelected()},
    m_concept_map{concept_map}
{
  if (concept_map->GetSelectedEdges().empty() && concept_map->GetSelectedNodes().empty())
  {
    throw std::logic_error("Unselect needs nodes to unselect on");
  }
  this->setText("unselect random");

  //Unselect a random selected edge or node
  const int n_edges{static_cast<int>(m_new_selected.first.size())};
  const int n_nodes{static_cast<int>(m_new_selected.second.size())};
  assert(n_edges + n_nodes > 0);
  const int i{std::rand() % (n_edges + n_nodes)};
  if (i < n_edges)
  {
    //Unselect edge
    std::swap(m_new_selected.first[i],m_new_selected.first.back());
    m_new_selected.first.pop_back();
  }
  else
  {
    //Unselect node
    std::swap(m_new_selected.second[i - n_edges],m_new_selected.second.back());
    m_new_selected.second.pop_back();
  }
}


void ribi::cmap::CommandUnselectRandom::redo()
{
  m_concept_map->SetSelected(m_new_selected);
}

void ribi::cmap::CommandUnselectRandom::undo()
{
  m_concept_map->SetSelected(m_old_selected);
}
