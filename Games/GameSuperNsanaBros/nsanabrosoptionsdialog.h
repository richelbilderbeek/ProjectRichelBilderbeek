#ifndef NSANABROSOPTIONSDIALOG_H
#define NSANABROSOPTIONSDIALOG_H
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "nsanabrosstlfwdheader.h"
//---------------------------------------------------------------------------
struct NsanaBrosOptionsDialog : public boost::noncopyable
{
  NsanaBrosOptionsDialog();

  const NsanaBrosOptions * GetOptions() const;
  //boost::shared_ptr<NsanaBrosOptions> UseOptions();
  void SetOptions(const NsanaBrosOptions& options);

  private:
  ~NsanaBrosOptionsDialog() {}
  friend void boost::checked_delete<>(NsanaBrosOptionsDialog *);

  boost::shared_ptr<NsanaBrosOptions> m_options;
};
//---------------------------------------------------------------------------
#endif // NSANABROSOPTIONSDIALOG_H
