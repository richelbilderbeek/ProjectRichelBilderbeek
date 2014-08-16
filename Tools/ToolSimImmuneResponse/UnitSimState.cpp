//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
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
#include <cassert>
#include <stdexcept>

#pragma hdrstop

#include "UnitSimState.h"

//---------------------------------------------------------------------------
const std::string SimState::GetFeedback() const
{
  if (IsPresent(cellHealthy) == false
    && ( mInBloodStream.empty() == false
      || mInBoneMarrow.empty() == false
      || mInCellTissue.empty() == false
      || mInLymphNode.empty() == false
       )
    )
  {
    return
      #ifndef NDEBUG
      "[-1] "
      #endif
      "The organism has died. GAME OVER.";
  }

  if ( IsPresent(virus) == false
    && IsPresent(antibody) == false
    && IsPresent(cellHealthy) == true)
  {
    return
      #ifndef NDEBUG
      "[0] "
      #endif
    "The organism is healthy yet...";
  }


  if ( IsPresent(macrophageWithoutVirusParticles) == false
    && IsPresent(macrophageWithVirusParticles) == false)
  {
    return
      #ifndef NDEBUG
      "[1] "
      #endif
      "Viruses in bloodstream and in cell tissue!"
      " Create macrophages to ingest viruses.";
  }
  if ( IsPresent(macrophageWithoutVirusParticles) == true
    && IsPresent(bloodStream,macrophageWithoutVirusParticles) == false
    && IsPresent(bloodStream,macrophageWithVirusParticles) == false)
  {
    return
      #ifndef NDEBUG
      "[2] "
      #endif

      "Viruses in bloodstream and in cell tissue!"
      " Send your macrophages to the blood stream"
      " to ingest viruses.";
  }
  if ( IsPresent(macrophageWithoutVirusParticles) == true
    && IsPresent(bloodStream,macrophageWithoutVirusParticles) == true
    && IsPresent(bloodStream,macrophageWithVirusParticles) == false)
  {
    return
      #ifndef NDEBUG
      "[3] "
      #endif

      "Viruses in bloodstream and in cell tissue!"
      " Send your macrophages in the blood stream near"
      " viruses to ingest them.";
  }

  if ( IsPresent(macrophageWithVirusParticles) == true
    && IsPresent(antibody) == false
    && IsPresent(bloodStream,macrophageWithVirusParticles) == true
    && IsPresent(lymphNode,macrophageWithVirusParticles) == false)
  {
    return
      #ifndef NDEBUG
      "[4] "
      #endif
      "Macrophage has ingested virus. Send it to the lymph node to"
      " alert the T helper cells.";
  }
  if ( IsPresent(lymphNode,macrophageWithVirusParticles) == true
    && IsPresent(tHelperCell) == false
    && IsPresent(activatedThelperCell) == false)
  {
    return
      #ifndef NDEBUG
      "[5] "
      #endif
      "Macrophage with ingested virus must alert T helper cells in lymp"
      " node. Produce T helper cell to respond.";
  }
  if ( IsPresent(lymphNode,macrophageWithVirusParticles) == true
    && IsPresent(tHelperCell) == true
    && IsPresent(lymphNode,tHelperCell) == false
    && IsPresent(lymphNode,activatedThelperCell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[6] "
      #endif
      "Macrophage with ingested virus must alert T helper cells in lymp"
      " node. Send T helper cells to lymph node.";
  }
  if ( IsPresent(lymphNode,macrophageWithVirusParticles) == true
    && IsPresent(tHelperCell) == true
    && IsPresent(lymphNode,tHelperCell) == true
    && IsPresent(lymphNode,activatedThelperCell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[7] "
      #endif
      "Macrophage with ingested virus must alert T helper cells in lymp"
      " node. Send T helper cell near macrophage in lymph node.";
  }

  if ( IsPresent(lymphNode,cytokine) == true
    && IsPresent(bCell) == false
    && IsPresent(activatedBcell) == false)
  {
    return
      #ifndef NDEBUG
      "[8] "
      #endif
      "T helper cells are active and producing cytokines. Produce"
      " a B cell to start the humoral response.";
  }
  if ( IsPresent(lymphNode, cytokine) == true
    && IsPresent(bCell) == true
    && IsPresent(lymphNode, bCell) == false
    && IsPresent(lymphNode, activatedBcell) == false)
  {
    return
      #ifndef NDEBUG
      "[9] "
      #endif
      "T helper cells are active and producing cytokines. Send"
      " B cell to lymph node to start the humoral response.";
  }

  if ( IsPresent(lymphNode, cytokine) == true
    && IsPresent(bCell) == true
    && IsPresent(lymphNode, bCell) == true
    && IsPresent(lymphNode, activatedBcell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[10] "
      #endif
      "Let B cell in lymph node start the humoral response"
      " by activating them with cytokine.";
  }


  if ( IsPresent(lymphNode, activatedBcell) == true
    && IsPresent(lymphNode, antibody) == true
    && IsPresent(bloodStream, antibody) == false
    )
  {
    return
      #ifndef NDEBUG
      "[11] "
      #endif
      "B cells in lymph node produce antibodies."
      " Wait until they reach the blood stream before"
      " viruses in blood stream can be destroyed.";
  }

  if ( IsPresent(bloodStream,antibody) == true
    && IsPresent(bloodStream,macrophageWithVirusParticles) == false
    && IsPresent(bloodStream,macrophageWithoutVirusParticles) == false
    )
  {
    return
      #ifndef NDEBUG
      "[12] "
      #endif
      "Antibodies present in blood stream."
      " Send macrophages to blood stream to ingest viruses."
      " Due to the antibodies, they can effectively remove all viruses now.";
  }
  if ( IsPresent(cellTissue,cytokine) == true
    && IsPresent(cytotoxicTcell) == false
    && IsPresent(activatedCytotoxicTcell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[13] "
      #endif
      "Macrophages in blood stream effectively remove"
      " viruses in blood stream, due to antibodies."
      " Produce cytotoxic T cells to disinfect cell tissue.";
  }

  if ( IsPresent(cellTissue,cytokine) == true
    && IsPresent(cytotoxicTcell) == true
    && IsPresent(activatedCytotoxicTcell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[14] "
      #endif
      "Activate cytotoxic T cells with cytokine "
      " to disinfect cell tissue.";
  }


  if ( IsPresent(cellTissue,cytokine) == true
    && IsPresent(activatedCytotoxicTcell) == true
    && IsPresent(cellTissue,activatedCytotoxicTcell) == false
    )
  {
    return
      #ifndef NDEBUG
      "[15] "
      #endif
      "Macrophages in blood stream effectively remove"
      " viruses in blood stream, due to antibodies."
      " Send cytotoxic T cells to cell tissue to disinfect cell tissue.";
  }

  if ( IsPresent(cellTissue,cytokine) == true
    && IsPresent(activatedCytotoxicTcell) == true
    && IsPresent(cellTissue,activatedCytotoxicTcell) == true
    && IsPresent(virus) == true
    )
  {
    return
      #ifndef NDEBUG
      "[16] "
      #endif
    "Macrophages in blood stream effectively remove"
           " viruses in blood stream, due to antibodies."
           " Cytotoxic T cells actively destroy infected cells,"
           " due to cytokines.";
  }



  return
    #ifndef NDEBUG
    "[99] "
    #endif
    "The organism has acquired immunity.";
}
//---------------------------------------------------------------------------
const bool SimState::IsPresent(const EnumLocation location, const EnumCellType cellType) const
{
  return (GetLocation(location).count(cellType) == 1);
}
//---------------------------------------------------------------------------
const bool SimState::IsPresent(const EnumCellType cellType) const
{
  if ( IsPresent(bloodStream,cellType) == false
    && IsPresent(boneMarrow ,cellType) == false
    && IsPresent(cellTissue ,cellType) == false
    && IsPresent(lymphNode  ,cellType) == false)
    return false;
  else
    return true;

}
//---------------------------------------------------------------------------
std::set<EnumCellType>& SimState::GetLocation(const EnumLocation location)
{
  switch (location)
  {
    case bloodStream: return mInBloodStream;
    case boneMarrow: return mInBoneMarrow;
    case cellTissue: return mInCellTissue;
    case lymphNode: return mInLymphNode;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown location");
}
//---------------------------------------------------------------------------
const std::set<EnumCellType>& SimState::GetLocation(const EnumLocation location) const
{
  switch (location)
  {
    case bloodStream: return mInBloodStream;
    case boneMarrow: return mInBoneMarrow;
    case cellTissue: return mInCellTissue;
    case lymphNode: return mInLymphNode;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown location");
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
