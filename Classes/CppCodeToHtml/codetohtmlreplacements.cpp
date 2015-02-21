//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "codetohtmlreplacements.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::c2h::Replacements::Replacements(
  const std::vector<std::pair<std::string,std::string>>& replacements) noexcept
  : m_replacements(CreateAllReplacements(replacements))
{
  #ifndef NDEBUG
  {
    ///Warn the user for doublures in the input
    const auto end = replacements.end();
    for (auto i=replacements.begin();i!=end;++i)
    {
      for (auto j=replacements.begin();j!=end;++j)
      {
        if (i==j) continue;
        if ((*i).first == (*j).first)
        {
          std::cerr << "Element occurring twice: " << (*i).first << '\n';
        }
      }
    }
  }


  {
    ///Check against recurring replacements
    for(const std::pair<std::string,std::string>& p: replacements)
    {
      if(!(
        std::search(p.second.begin(),p.second.end(),p.first.begin(),p.first.end())
        == p.second.end()))
      {
        TRACE("Recurring replacement detected:")
        TRACE(p.first);
        TRACE(p.second);
        TRACE("Add $ symbols in the second part, so that the first part is not a subsequence of it")
      }

      assert(
        std::search(p.second.begin(),p.second.end(),p.first.begin(),p.first.end())
        == p.second.end());
    }
  }

  {
    ///Check agains doublures in the processed input
    const auto end = m_replacements.end();
    for (auto i=m_replacements.begin();i!=end;++i)
    {
      for (auto j=m_replacements.begin();j!=end;++j)
      {
        if (i==j) continue;
        if ((*i).first == "$") continue;
        if ((*i).first == (*j).first)
        {
          TRACE("ERROR: duplicate in replacements");
          TRACE("Remove the duplicate from codetohtmlreplacementscpp.cpp or codetohtmlreplacementspro.cpp");
          TRACE((*i).first);
        }
        assert((*i).first != (*j).first);
      }
    }
  }

  {
    ///Check nested processed input
    const std::set<std::string> skip {
      "$",
      "<",
      ">",
      "&",
      "[AMPERSAND]",
      "[DOLLAR]",
      "[GREATER_THAN]",
      "[LESS_THAN]"
    };
    const auto end = m_replacements.end();
    for (auto i=m_replacements.begin();i!=end;++i)
    {
      const std::string s = (*i).second;
      if (skip.count(s) == 1) continue;
      assert(skip.count(s) == 0);
      for (auto j=m_replacements.begin();j!=end;++j)
      {
        if (i==j) continue;
        const std::string t = (*j).first;
        if (skip.count(t) == 1) continue;
        assert(skip.count(t) == 0);
        if (s.find(t) != std::string::npos)
        {
          std::cerr << "Error: "
            << s
            << " is nested by "
            << t
            << '\n';
        }
        assert(s.find(t) == std::string::npos);
      }
    }
  }

  #endif
}

std::vector<std::pair<std::string,std::string>>
  ribi::c2h::Replacements::CreateAllReplacements(
    const std::vector<std::pair<std::string,std::string> >& replacements
) noexcept
{
  std::vector<std::pair<std::string,std::string> > v;
  //Initial
  {
    const std::vector<std::pair<std::string,std::string> > w
      = CreateInitialReplacements();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Main
  {
    std::vector<std::pair<std::string,std::string> > w(replacements);

    //Sort to remove doublures
    std::sort(w.begin(),w.end());
    const auto new_end = std::unique(w.begin(),w.end());
    w.erase(new_end,w.end());

    //Sort from long strings to short, and alphabetically
    std::sort(w.begin(),w.end(),
      [](const std::pair<std::string,std::string>& lhs,const std::pair<std::string,std::string>& rhs)
      {
        if (lhs.first.size() > rhs.first.size()) return true;
        else if (lhs.first.size() < rhs.first.size()) return false;
        else
        {
          assert(lhs.first.size() == rhs.first.size());
          return lhs.first < rhs.first;
        }
      }
    );
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //End
  {
    std::vector<std::pair<std::string,std::string> > w
      = CreateEndReplacements();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::pair<std::string,std::string> > ribi::c2h::Replacements::CreateEndReplacements() noexcept
{
  return
  {
  //2
    { "  ","&nbsp;&nbsp;" },
  //Remove the dollars
    { "$","" }, //IMPORTANT: the $ is used to disrupt replaced words
  //Convert original ampersands and dollars back again
    { "[AMPERSAND]","&amp;" },
    { "[DOLLAR]","$" },
    { "[LESS_THAN]","&lt;" },
    { "[GREATER_THAN]","&gt;" }
  };
}

std::vector<std::pair<std::string,std::string>> ribi::c2h::Replacements::CreateInitialReplacements() noexcept
{
  return
  {
    //symbol replacements that will mess up the markup if placed in bottom
    //First convert ampersands and dollars
    { "&","[AMPERSAND]" },
    { "$","[DOLLAR]" },
    { "<","[LESS_THAN]" },
    { ">","[GREATER_THAN]" }
  };
}
