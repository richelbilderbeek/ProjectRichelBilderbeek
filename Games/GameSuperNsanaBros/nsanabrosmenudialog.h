#ifndef NSANABROSMENUDIALOG_H
#define NSANABROSMENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
#include "nsanabrosstlfwdheader.h"
//---------------------------------------------------------------------------
struct NsanaBrosMenuDialog : public boost::noncopyable
{
  NsanaBrosMenuDialog();
  const NsanaBrosOptionsDialog * GetOptionsDialog() const;
  boost::shared_ptr<NsanaBrosOptionsDialog> UseOptionsDialog();

  private:
  ~NsanaBrosMenuDialog() {}
  friend void boost::checked_delete<>(NsanaBrosMenuDialog *);

  boost::scoped_ptr<NsanaBrosGameDialog> m_game;
  boost::shared_ptr<NsanaBrosOptionsDialog> m_options;

  public:

  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
#endif // NSANABROSMENUDIALOG_H
