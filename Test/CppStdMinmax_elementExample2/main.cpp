#include <algorithm>
#include <cassert>
#include <map>

struct Id
{
  Id(const int id) : m_id(id) {}
  int m_id;
};

bool operator<(const Id& lhs, const Id& rhs) { return lhs.m_id < rhs.m_id; }

const std::pair<Id,Id> GetBestAndWorstIdStl(const std::map<Id,double>& m)
{
  const std::map<Id,double>::const_iterator end = m.end();
  std::map<Id,double>::const_iterator min = m.begin();
  std::map<Id,double>::const_iterator max = m.begin();
  for (std::map<Id,double>::const_iterator i = m.begin(); i!=end; ++i)
  {
    if (i->second < min->second) min = i;
    if (i->second >= max->second) max = i;
  }
  return std::make_pair(min->first,max->first);
}

const std::pair<Id,Id> GetBestAndWorstIdCpp11(const std::map<Id,double>& m)
{
  const auto p = std::minmax_element(m.begin(),m.end(),
    [](const std::pair<const Id,double>& lhs,const std::pair<const Id,double>& rhs)
    {
      return rhs.second > lhs.second;
    }
  );
  return std::make_pair((*p.first).first,(*p.second).first);
}

int main()
{
  const std::map<Id,double> m
    =
    {
      std::make_pair(Id(0), 0.0),
      std::make_pair(Id(1), 1.0),
      std::make_pair(Id(2), 0.0),
      std::make_pair(Id(3),-1.0),
      std::make_pair(Id(4), 0.0)
    };

  const auto p1 = GetBestAndWorstIdStl(m);
  assert(p1.first.m_id == 3);
  assert(p1.second.m_id == 1);

  const auto p2 = GetBestAndWorstIdCpp0x(m);
  assert(p2.first.m_id == 3);
  assert(p2.second.m_id == 1);

}
