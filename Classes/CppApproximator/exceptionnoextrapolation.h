#ifndef EXCEPTIONNOEXTRAPOLATION_H
#define EXCEPTIONNOEXTRAPOLATION_H

#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace ribi {

template <class T>
struct ExceptionNoExtrapolation : public std::exception
{
  ExceptionNoExtrapolation(
    const T& value)
    : m_is_above_max(false),
      m_is_below_min(false),
      m_what(
        std::string("Value of ")
      + boost::lexical_cast<std::string>(value)
      + " out of range [unknown]"
    )
  {

  }

  ExceptionNoExtrapolation(
    const T& value, const T& lowest, const T& highest)
    : m_is_above_max(value > highest),
      m_is_below_min(value < lowest),
      m_what(
        std::string("Value of ")
      + boost::lexical_cast<std::string>(value)
      + " out of range ["
      + boost::lexical_cast<std::string>(lowest)
      + " , "
      + boost::lexical_cast<std::string>(highest)
      + "]"
    )
  {

  }
  bool IsAboveMax() const { return m_is_above_max; }
  bool IsBelowMin() const { return m_is_below_min; }
  const char * what() const throw() { return m_what.c_str(); }
  private:

  const bool m_is_above_max;
  const bool m_is_below_min;
  ///The error message
  const std::string m_what;
};

} //~namespace ribi


#endif // EXCEPTIONNOEXTRAPOLATION_H
