#ifndef NSANABROSOPTIONS_H
#define NSANABROSOPTIONS_H
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
//#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
///NsanaBrosOptions contains the options
struct NsanaBrosOptions // : public boost::noncopyable
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
//---------------------------------------------------------------------------
#endif // NSANABROSOPTIONS_H
