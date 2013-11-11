#ifndef NSANABROSOPTIONSDIALOG_H
#define NSANABROSOPTIONSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

#include "nsanabrosstlfwdheader.h"
#pragma GCC diagnostic pop

namespace ribi {

struct NsanaBrosOptionsDialog
{
  NsanaBrosOptionsDialog();
  NsanaBrosOptionsDialog(const NsanaBrosOptionsDialog&) = delete;
  NsanaBrosOptionsDialog& operator=(const NsanaBrosOptionsDialog&) = delete;

  const boost::shared_ptr<const NsanaBrosOptions> GetOptions() const;
  //boost::shared_ptr<NsanaBrosOptions> UseOptions();
  void SetOptions(const NsanaBrosOptions& options);

  private:
  ~NsanaBrosOptionsDialog() {}
  friend void boost::checked_delete<>(NsanaBrosOptionsDialog *);

  boost::shared_ptr<NsanaBrosOptions> m_options;
};

} //~namespace ribi

#endif // NSANABROSOPTIONSDIALOG_H
