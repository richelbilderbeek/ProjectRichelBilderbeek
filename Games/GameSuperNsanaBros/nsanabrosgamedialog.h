#ifndef NSANABROSGAMEDIALOG_H
#define NSANABROSGAMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

#include "nsanabrosstlfwdheader.h"
#pragma GCC diagnostic pop

namespace ribi {

///NsanaBrosGameDialog manages all NsanaBrosGameWidgets
struct NsanaBrosGameDialog
{
  NsanaBrosGameDialog(const boost::shared_ptr<const NsanaBrosOptions> options);
  NsanaBrosGameDialog(const NsanaBrosGameDialog&) = delete;
  NsanaBrosGameDialog& operator=(const NsanaBrosGameDialog&) = delete;

  private:
  ~NsanaBrosGameDialog() noexcept;
  friend void boost::checked_delete<>(NsanaBrosGameDialog *);


  boost::shared_ptr<NsanaBrosGameArea2dWidget> m_area;
  boost::shared_ptr<NsanaBrosKeysWidget> m_keys;
  const boost::shared_ptr<const NsanaBrosOptions> m_options;

};

} //~namespace ribi

#endif // NSANABROSGAMEDIALOG_H
