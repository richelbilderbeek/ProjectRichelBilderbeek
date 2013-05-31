#ifndef NSANABROSGAMEDIALOG_H
#define NSANABROSGAMEDIALOG_H
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include "nsanabrosstlfwdheader.h"
//---------------------------------------------------------------------------
///NsanaBrosGameDialog manages all NsanaBrosGameWidgets
struct NsanaBrosGameDialog : public boost::noncopyable
{
  NsanaBrosGameDialog(const NsanaBrosOptions * const options);

  private:
  ~NsanaBrosGameDialog() {}
  friend void boost::checked_delete<>(NsanaBrosGameDialog *);


  boost::scoped_ptr<NsanaBrosGameArea2dWidget> m_area;
  boost::scoped_ptr<NsanaBrosKeysWidget> m_keys;
  const NsanaBrosOptions * const m_options;

};
//---------------------------------------------------------------------------
#endif // NSANABROSGAMEDIALOG_H
