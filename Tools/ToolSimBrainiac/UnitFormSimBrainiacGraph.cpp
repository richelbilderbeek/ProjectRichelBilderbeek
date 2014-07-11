/*
  SimBrainiac, a simulation of Brainiacs interacting
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <set>
#include <numeric>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSimBrainiacGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimBrainiacGraph *FormSimBrainiacGraph;
//---------------------------------------------------------------------------
__fastcall TFormSimBrainiacGraph::TFormSimBrainiacGraph(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormSimBrainiacGraph::Plot(const std::vector<Brainiac>& brainiacs)
{
  Chart1->Series[0]->Clear();
  Chart2->Series[0]->Clear();

  std::set<double> setPcorrectAnswers;
  std::set<double> setPhasQuestion;
  const int nBrainiacs = brainiacs.size();
  for (int i=0; i!=nBrainiacs; ++i)
  {
    setPcorrectAnswers.insert(brainiacs[i].pCorrectAnswer);
    setPhasQuestion.insert(brainiacs[i].pHasQuestion);
  }

  {
    //For every pCorrectAnswer
    const std::set<double>::const_iterator b = setPcorrectAnswers.end();
    for (std::set<double>::const_iterator a = setPcorrectAnswers.begin(); a!=b; ++a)
    {
      std::vector<double> relIndex;
      for (int i=0; i!=nBrainiacs; ++i)
      {
        if (brainiacs[i].pCorrectAnswer == *a)
          relIndex.push_back(
            static_cast<double>(i) / static_cast<double>(nBrainiacs ) );
      }
      const double average
        = std::accumulate(relIndex.begin(), relIndex.end(), 0.0)
        / static_cast<double>(relIndex.size());
      Chart1->Series[0]->AddXY(*a,average);
    }
  }

  {
    //For every pHasQuestion
    const std::set<double>::const_iterator b = setPhasQuestion.end();
    for (std::set<double>::const_iterator a = setPhasQuestion.begin(); a!=b; ++a)
    {
      std::vector<double> relIndex;
      for (int i=0; i!=nBrainiacs; ++i)
      {
        if (brainiacs[i].pHasQuestion == *a)
          relIndex.push_back(
            static_cast<double>(i) / static_cast<double>(nBrainiacs ) );
      }
      const double average
        = std::accumulate(relIndex.begin(), relIndex.end(), 0.0)
        / static_cast<double>(relIndex.size());
      Chart2->Series[0]->AddXY(*a,average);
    }
  }

}
//---------------------------------------------------------------------------


void __fastcall TFormSimBrainiacGraph::FormResize(TObject *Sender)
{
  Chart1->Width = ClientWidth / 2;
  Chart2->Width = ClientWidth - Chart1->Width;        
}
//---------------------------------------------------------------------------
