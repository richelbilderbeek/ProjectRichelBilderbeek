#include "aafaminoacids.h"

#include <cassert>

#include "testtimer.h"
#include "trace.h"

boost::bimap<ribi::aaf::AminoAcid,std::string> ribi::aaf::AminoAcids::m_map;

ribi::aaf::AminoAcids::AminoAcids()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::bimap<ribi::aaf::AminoAcid,std::string> ribi::aaf::AminoAcids::CreateMap()
{
  boost::bimap<AminoAcid,std::string> m;
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::alanine,"alanine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::arginine,"arginine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::asparagine,"asparagine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::aspartic_acid,"aspartic_acid"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::cysteine,"cysteine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::glutamic_acid,"glutamic_acid"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::glutamine,"glutamine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::glycine,"glycine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::histidine,"histidine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::isoleucine,"isoleucine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::leucine,"leucine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::lysine,"lysine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::methionine,"methionine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::ornithine,"ornithine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::phenylalanine,"phenylalanine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::proline,"proline"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::selenocysteine,"selenocysteine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::serine,"serine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::threonine,"threonine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::tryptophan,"tryptophan"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::tyrosine,"tyrosine"));
  m.insert(boost::bimap<AminoAcid,std::string>::value_type(AminoAcid::valine,"valine"));
  return m;
}

std::vector<ribi::aaf::AminoAcid> ribi::aaf::AminoAcids::GetAll() const noexcept
{
  const std::vector<AminoAcid> v {
    AminoAcid::alanine,
    AminoAcid::arginine,
    AminoAcid::asparagine,
    AminoAcid::aspartic_acid,
    AminoAcid::cysteine,
    AminoAcid::glutamic_acid,
    AminoAcid::glutamine,
    AminoAcid::glycine,
    AminoAcid::histidine,
    AminoAcid::isoleucine,
    AminoAcid::leucine,
    AminoAcid::lysine,
    AminoAcid::methionine,
    AminoAcid::ornithine,
    AminoAcid::phenylalanine,
    AminoAcid::proline,
    AminoAcid::selenocysteine,
    AminoAcid::serine,
    AminoAcid::threonine,
    AminoAcid::tryptophan,
    AminoAcid::tyrosine,
    AminoAcid::valine
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(AminoAcid::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::aaf::AminoAcids::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::vector<AminoAcid> v = AminoAcids().GetAll();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const AminoAcid t = v[i];
    const std::string s = AminoAcids().ToStr(t);
    assert(!s.empty());
    const AminoAcid u = AminoAcids().ToType(s);
    assert(u == t);
  }
}
#endif

std::string ribi::aaf::AminoAcids::ToStr(const AminoAcid type) const noexcept
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type));
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::aaf::AminoAcid ribi::aaf::AminoAcids::ToType(const std::string& s) const
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const AminoAcid t = m_map.right.find(s)->second;
  return t;
}
