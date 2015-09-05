#include "conceptmapcommandunselectrandom.h"

#include <cassert>
#include <sstream>
#include <stdexcept>

#include "conceptmap.h"
#include "conceptmaphelper.h"
#include "trace.h"

ribi::cmap::CommandUnselectRandom::CommandUnselectRandom(
  const boost::shared_ptr<ConceptMap> conceptmap
) :
    m_conceptmap{conceptmap},
    m_new_selected{conceptmap->GetSelected()},
    m_old_selected{conceptmap->GetSelected()}
{
  assert(m_conceptmap);
  if (m_conceptmap->GetSelectedEdges().empty() && m_conceptmap->GetSelectedNodes().empty())
  {
    throw std::logic_error("CommandUnselectRandom needs nodes to unselect on");
  }
  this->setText("unselect random");


  //Already create new selected
  {
    //Get a random selected edge or node
    auto all_selected = m_conceptmap->GetSelected();
    const int n_edges{static_cast<int>(all_selected.first.size())};
    const int n_nodes{static_cast<int>(all_selected.second.size())};
    assert(n_edges + n_nodes > 0);
    const int i{std::rand() % (n_edges + n_nodes)};
    if (i < n_edges)
    {
      //Unselect edge
      std::swap(all_selected.first[i],all_selected.first.back());
      m_new_selected.first.pop_back();
    }
    else
    {
      //Unselect node
      std::swap(all_selected.second[i - n_edges],all_selected.second.back());
      m_new_selected.second.pop_back();
    }
  }
}

void ribi::cmap::CommandUnselectRandom::redo()
{
  m_conceptmap->SetSelected(m_new_selected);
}

void ribi::cmap::CommandUnselectRandom::undo()
{
  m_conceptmap->SetSelected(m_old_selected);
}
