#ifndef NSANABROSOPTIONS_H
#define NSANABROSOPTIONS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
//
#pragma GCC diagnostic pop

namespace ribi {

///NsanaBrosOptions contains the options
struct NsanaBrosOptions
{
  NsanaBrosOptions();

  bool GetShowOneDimension() const { return m_show_one_dimensional; }
  bool GetShowTwoDimension() const { return m_show_two_dimensional; }
  bool GetShowKeys() const { return m_show_keys; }

  private:
  ~NsanaBrosOptions() {}
  friend void boost::checked_delete<>(NsanaBrosOptions *);

  bool m_show_one_dimensional;
  bool m_show_two_dimensional;
  bool m_show_keys;

};

} //~namespace ribi

#endif // NSANABROSOPTIONS_H
