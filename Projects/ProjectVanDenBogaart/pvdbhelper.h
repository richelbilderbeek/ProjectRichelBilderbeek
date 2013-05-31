#ifndef PVDBHELPER_H
#define PVDBHELPER_H

#include <array>
#include <vector>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
struct QRegExp;
#else
#include <QRegExp>
#endif



///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T> > AddConst(
  const std::vector<boost::shared_ptr<T> > v)
{
  return std::vector<boost::shared_ptr<const T> >(v.begin(),v.end());
}

namespace pvdb {

///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& filename);


///Obtain all possible selections of a std::vector, preserving the ordering of its elements
///Examples:
/// {     } -> { {}                                              }
/// {1    } -> { {}, {1}                                         }
/// {1,2  } -> { {}, {1}, {2},      {1,2}                        }
/// {1,2,3} -> { {}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3} }
//From http://www.richelbilderbeek.nl/CppGetCombinations.htm
template <class T>
const std::vector<std::vector<T> > GetCombinations(const std::vector<T>& v)
{
  std::vector<std::vector<T> > result;
  const int sz = static_cast<int>(v.size());
  const int n_combinations = (1 << sz);

  for (int i=0; i!=n_combinations; ++i)
  {
    std::vector<T> w;
    for (int j=0; j!=sz; ++j)
    {
      if ((1 << j) & i)
      {
        w.push_back(v[j]);
      }
    }
    result.push_back(w);
  }
  return result;
}

///Obtain the Pythagorian distance from two delta's
//From www.richelbilderbeek.nl/CppGetDistance.htm
double GetDistance(const double delta_x, const double delta_y);

///Obtain the Pythagorian distance from two coordinats
//From www.richelbilderbeek.nl/CppGetDistance.htm
double GetDistance(const double x1, const double y1, const double x2, const double y2);

///From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
const std::vector<std::string> GetRegexMatches(
  const std::string& s,
  const QRegExp& r);

///Split an XML std::string into its parts
//From http://www.richelbilderbeek.nl/CppSplitXml.htm
const std::vector<std::string> SplitXml(const std::string& s);

///Strip the XML tags of an XML item
///For example '<tag>text</tag>' becomes 'text'
///Note that also '<any_tag>text</other_tag>' fails
///From http://www.richelbilderbeek.nl/CppStripXmlTag.htm
const std::string StripXmlTag(const std::string& s);

///Test the helper functions
void TestHelperFunctions();

///Pretty-print an XML std::string by indenting its elements
//From http://www.richelbilderbeek.nl/CppXmlToPretty.htm
const std::vector<std::string> XmlToPretty(const std::string& s);

} //~namespace pvdb

#endif // PVDBHELPER_H
