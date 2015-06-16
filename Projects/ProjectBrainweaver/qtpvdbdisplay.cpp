//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbdisplay.h"

#include <boost/lexical_cast.hpp>

#include <QHeaderView>
#include <QTableWidget>

#include "conceptmapcompetencies.h"
#include "conceptmapcompetency.h"
#include "conceptmapconcept.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "pvdbfile.h"
#include "pvdbhelper.h"
#include "conceptmapnode.h"
#include "qtconceptmapcompetency.h"
#pragma GCC diagnostic pop

void ribi::pvdb::QtDisplay::DisplayRatedConcepts(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  const int sz = static_cast<int>(file->GetConceptMap()->GetNodes().size());
  table->setRowCount(sz - 1); //-1 to skip focus question node at index 0

  for (int i=1; i!=sz; ++i)
  {
    const int row = i-1; //-1 to skip focus question node at index 0
    const boost::shared_ptr<const ribi::cmap::Concept> concept = file->GetConceptMap()->GetNodes().at(i)->GetConcept();
    //Name
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(concept->GetName().c_str());
      table->setVerticalHeaderItem(row,item);
    }
    //Rating complexity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingComplexity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,0,item);
    }
    //Rating concreteness
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingConcreteness()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,1,item);
    }
    //Rating specificity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingSpecificity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,2,item);
    }
  }

  table->verticalHeader()->setMinimumWidth(300);
  table->verticalHeader()->setMaximumWidth(300);
  table->setColumnWidth(0,100);
  table->setColumnWidth(1,100);
  table->setColumnWidth(2,100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
    + table->columnWidth(2)
  );



}

  //Examples' icons
void ribi::pvdb::QtDisplay::DisplayExamples(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  {
    const int n_rows = table->rowCount();
    for(int i=0; i!=n_rows; ++i)
    {
      const cmap::Competency competency = static_cast<cmap::Competency>(i + 1); //Skip 0 == uninitialized
      const std::string text = cmap::Competencies().ToStrDutch(competency);
      const QIcon icon = cmap::QtCompetency().CompetencyToIcon(competency);
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(text.c_str());
      item->setIcon(icon);
      table->setVerticalHeaderItem(i,item);
    }
  }
  //Examples' competencies
  {
    std::map<cmap::Competency,int> cnts;

    for(const boost::shared_ptr<const cmap::Node> node: AddConst(file->GetConceptMap()->GetNodes()))
    {
      for (const boost::shared_ptr<const cmap::Example> example: node->GetConcept()->GetExamples()->Get())
      {
        const auto iter = cnts.find(example->GetCompetency());
        if (iter != cnts.end())
        {
          ++(*iter).second;
        }
        else
        {
          const cmap::Competency competency = example->GetCompetency();
          cnts.insert(std::make_pair(competency,1));
        }
      }
    }
    const int sum = std::accumulate(cnts.begin(),cnts.end(),0,
      [](int& init,const std::pair<cmap::Competency,int>& p)
      {
        init += p.second;
        return init;
      }
    );
    if (sum != 0)
    {
      for (const std::pair<cmap::Competency,int>& p: cnts)
      {
        const int col = 0;
        const int row = static_cast<int>(p.first) - 1;
        if (row == -1) continue; //0 == uninitialized
        assert(row >= 0);
        assert(row < table->rowCount());
        QTableWidgetItem * const item  = new QTableWidgetItem;
        const double f = static_cast<double>(p.second) / static_cast<double>(sum);
        const int percentage = static_cast<int>(std::round(100.0 * f));
        const std::string text = boost::lexical_cast<std::string>(percentage);
        item->setText(text.c_str());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row,col,item);
      }
    }
  }
}

void ribi::pvdb::QtDisplay::DisplayValues(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  std::vector<boost::shared_ptr<const cmap::Node> > all_nodes = AddConst(file->GetConceptMap()->GetNodes());
  #ifndef NDEBUG
  const int all_sz = static_cast<int>(all_nodes.size());
  #endif

  all_nodes.erase(all_nodes.begin());

  #ifndef NDEBUG
  const int sz = static_cast<int>(all_nodes.size());
  assert(sz == all_sz - 1);
  #endif

  const std::vector<boost::shared_ptr<const cmap::Node> > nodes = all_nodes;
  const int n_nodes = static_cast<int>(nodes.size());  //Constant 'c'
  //Concreteness experimental: C_e at row = 1, col = 0
  //50.0 * sum_rated_concreteness / n_nodes
  {
    const int sum_rated_concreteness //Constant 'k_c'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const cmap::Node>& node)
      {
        return init + node->GetConcept()->GetRatingConcreteness();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int c_e
        = static_cast<int>(
          std::round(
           50.0 * static_cast<double>(sum_rated_concreteness)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(c_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,0,item);
  }
  //Concreteness eStimated: C_s at row = 1, col = 1
  //C_s = 100.0 * n_examples / (n_examples + n_nodes + n_relations_not_to_focus)
  {
    const std::vector<boost::shared_ptr<const cmap::Edge> > edges = AddConst(file->GetConceptMap()->GetEdges());
    const int n_nodes_examples = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const cmap::Node>& node)
      {
        return init + static_cast<int>(node->GetConcept()->GetExamples()->Get().size());
      }
    );
    const int n_edges_examples = std::accumulate(edges.begin(),edges.end(),0,
      [](int& init, const boost::shared_ptr<const cmap::Edge>& edge)
      {
        return init + static_cast<int>(edge->GetNode()->GetConcept()->GetExamples()->Get().size());
      }
    );
    const int n_relations_not_to_focus //Constant 'r'
      = std::count_if(edges.begin(),edges.end(),
      [](const boost::shared_ptr<const cmap::Edge>& edge)
      {
        return edge->GetFrom() != 0 && edge->GetTo() != 0; //Not connected to focus question
      }
    );
    const int n_examples //Constant 'v'
      = n_nodes_examples + n_edges_examples;
    std::string text = "N/A";
    if (n_examples + n_nodes + n_relations_not_to_focus != 0)
    {
      const double c_s
        = static_cast<int>(
          std::round(
            100.0 * static_cast<double>(n_examples)
            / static_cast<double>(n_examples + n_nodes + n_relations_not_to_focus)
          )
        );
      text = boost::lexical_cast<std::string>(c_s);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,1,item);
  }
  //Complexity experimental value: X_e at row = 0, col = 0
  //50.0 * sum_rated_complexity / n_nodes
  {
    const int sum_rated_complexity //Constant 'k_i'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const cmap::Node>& node)
      {
        return init + node->GetConcept()->GetRatingComplexity();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int x_e
        = static_cast<int>(
          std::round(
           50.0 * static_cast<double>(sum_rated_complexity)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(x_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,0,item);
  }
  //compleXity eStimated: X_s at row = 0, col = 1
  //x_s = ((2*n_relations_not_to_focus)/(n_nodes*(n_nodes-1))))^0.25*100%
  {
    const std::vector<boost::shared_ptr<const cmap::Edge> > edges = AddConst(file->GetConceptMap()->GetEdges());
    const int n_relations_not_to_focus //Constant 'r'
      = std::count_if(edges.begin(),edges.end(),
      [](const boost::shared_ptr<const cmap::Edge>& edge)
      {
        return edge->GetFrom() != 0 && edge->GetTo() != 0; //Not connected to focus question
      }
    );
    std::string text = "N/A";
    if (n_nodes > 1)
    {
      const int x_s
        = static_cast<int>(
            std::round(
              100.0
              * std::pow(
                  static_cast<double>(n_relations_not_to_focus * 2)
                / static_cast<double>(n_nodes * (n_nodes - 1) ),
                0.25)
            )
          );
       text = boost::lexical_cast<std::string>(x_s);
     }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,1,item);
  }
  //Experimental specificity: s_e at row = 2, col = 0
  //s_e = 50.0 * sum_rated_specificity / n_nodes
  {
    const int sum_rated_specificity //Constant 'k_s'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const cmap::Node>& node)
      {
        return init + node->GetConcept()->GetRatingSpecificity();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int s_e
        = static_cast<int>(
          std::round(
            static_cast<double>(50 * sum_rated_specificity)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(s_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(2,0,item);
  }
  //Richness Experimental: r_e at row = 3, col = 0
  //r_e = ((a + b) / 14) * 100%
  //a = number of different Competencies
  //b = number of Competencies between 1/12th and 1/4th of number of examples
  {
    std::map<cmap::Competency,int> m;
    //Tally the competencies
    for (const boost::shared_ptr<const cmap::Node>& node: nodes)
    {
      for (const boost::shared_ptr<const cmap::Example> example: node->GetConcept()->GetExamples()->Get())
      {
        const cmap::Competency competency = example->GetCompetency();
        const auto iter = m.find(competency);
        if (iter != m.end())
        {
          ++(*iter).second; //Tally the known competency
        }
        else
        {
          m.insert(std::make_pair(competency,1)); //Tally the first of this competency
        }
      }
    }
    //Remove category 'misc'
    #ifndef NDEBUG
    const int debug_m_size_old = static_cast<int>(m.size());
    const bool debug_will_resize = m.count(cmap::Competency::misc);
    #endif
    m.erase(cmap::Competency::misc);
    #ifndef NDEBUG
    const int debug_m_size_new = static_cast<int>(m.size());
    assert( ( debug_will_resize && debug_m_size_old == debug_m_size_new + 1)
         || (!debug_will_resize && debug_m_size_old == debug_m_size_new    )
    );
    #endif


    const int a = static_cast<int>(m.size());
    const int n_examples = std::accumulate(m.begin(),m.end(),0,
      [](int& init,const std::pair<cmap::Competency,int>& p)
      {
        return init + p.second;
      }
    );
    const int my_min = static_cast<int>(std::ceil( static_cast<double>(n_examples) / 12.0));
    const int my_max = static_cast<int>(std::floor(static_cast<double>(n_examples) /  4.0));
    const int b = std::count_if(m.begin(),m.end(),
      [my_min,my_max](const std::pair<cmap::Competency,int>& p)
      {
        return p.second >= my_min && p.second <= my_max;
      }
    );

    const int r_e
      = static_cast<int>(
        std::round(
          100.0 * ( static_cast<double>(a+b) / 12.0)
        )
      );
    std::string text = boost::lexical_cast<std::string>(r_e);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(3,0,item);
  }
  table->verticalHeader()->setMaximumWidth(100);
  table->verticalHeader()->setMinimumWidth(100);
  table->setColumnWidth(0,200);
  table->setColumnWidth(1,200);
  assert(table->verticalHeader()->width() == 100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
  );
}
