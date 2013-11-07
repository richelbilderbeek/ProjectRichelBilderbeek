#ifndef NSANABROSGAMEDIALOG_H
#define NSANABROSGAMEDIALOG_H

#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>

#include "nsanabrosstlfwdheader.h"

namespace ribi {

///NsanaBrosGameDialog manages all NsanaBrosGameWidgets
struct NsanaBrosGameDialog
{
  NsanaBrosGameDialog(const NsanaBrosOptions * const options);
  NsanaBrosGameDialog(const NsanaBrosGameDialog&) = delete;
  NsanaBrosGameDialog& operator=(const NsanaBrosGameDialog&) = delete;

  private:
  ~NsanaBrosGameDialog() noexcept;
  friend void boost::checked_delete<>(NsanaBrosGameDialog *);


  boost::scoped_ptr<NsanaBrosGameArea2dWidget> m_area;
  boost::scoped_ptr<NsanaBrosKeysWidget> m_keys;
  const NsanaBrosOptions * const m_options;

};

} //~namespace ribi

#endif // NSANABROSGAMEDIALOG_H
