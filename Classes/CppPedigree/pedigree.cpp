#include "pedigree.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

Pedigree::Pedigree(
  const std::string& name,
  const std::weak_ptr<Pedigree> parent
) : m_name{name}, m_offspring{}, m_parent{parent}, m_verbose{false}
{
  #ifndef NDEBUG
  Test();
  #endif
}

Pedigree::~Pedigree()
{
  if (m_verbose) { std::clog << "Destructor: " << m_name << std::endl; }
}

void Pedigree::CheckOffspring() const
{
  //Erase-remove idiom to remove all nullptr kids
  m_offspring.erase(
    std::remove_if(std::begin(m_offspring),std::end(m_offspring),
      [](auto kid) { return !kid.lock(); }
    ),
    std::end(m_offspring)
  );
}

std::shared_ptr<Pedigree> Pedigree::Create(const std::string& name) noexcept
{
  std::shared_ptr<Pedigree> i = std::make_shared<Pedigree>(name);
  return i;
}

std::shared_ptr<Pedigree> Pedigree::CreateOffspring(const std::string& name) noexcept
{
  std::shared_ptr<Pedigree> kid = Create(name);
  m_offspring.push_back(kid);
  kid->SetParent(this->shared_from_this());
  return kid;
}

std::string Pedigree::ToNewick() const
{
  const std::pair<std::string,int> p{
    CollectNameDepthPair()
  };
  std::stringstream s;
  if (p.second == 0)
  {
    if (p.first.front() == '(' && p.first.back() == ')')
    {
      s << p.first << ";";
    }
    else
    {
      s << "(" << p.first << ");";
    }
  }
  else
  {
    s << "(" << p.first << ":" << p.second << ");";
  }
  //Replace trailing comma by a trailing semicolon
  return s.str();
}

std::pair<std::string,int> Pedigree::CollectNameDepthPair() const noexcept
{
  const bool verbose{false};
  if (m_offspring.empty())
  {
    if (verbose) { std::clog << "No offspring\n"; }
    return std::make_pair(GetName(),0);
  }
  else if (m_offspring.size() == 1)
  {
    if (verbose) { std::clog << "One offspring\n"; }
    std::stringstream s;
    const std::weak_ptr<Pedigree> kid_or_not{m_offspring[0]};
    const std::shared_ptr<Pedigree> kid{kid_or_not.lock()};
    if (!kid)
    {
      m_offspring.pop_back();
      return CollectNameDepthPair();
    }
    assert(kid);
    const std::pair<std::string,int> p{
      kid->CollectNameDepthPair()
    };
    return std::make_pair(p.first,p.second + 1);
  }
  else
  {
    if (verbose) { std::clog << "More offspring\n"; }
    std::stringstream s;
    const auto end = std::end(m_offspring);
    for (auto i = std::begin(m_offspring); i!=end; ++i)
    //for (const std::weak_ptr<Pedigree>& kid_or_not: m_offspring)
    {
      const std::shared_ptr<Pedigree> kid{(*i).lock()};
      if (!kid)
      {
        std::swap(*i,m_offspring.back());
        assert(!m_offspring.back().lock()); //Must remove nullptr kid
        m_offspring.pop_back();
        return CollectNameDepthPair();
      }
      assert(kid);

      const std::pair<std::string,int> p{
        kid->CollectNameDepthPair()
      };
      s << p.first << ":" << (p.second + 1) << ",";
    }
    std::string t{s.str()};
    assert(!t.empty());
    t.pop_back();
    t = "(" + t + ")";
    return std::make_pair(t,0);
  }
  return std::make_pair("",0);
}
