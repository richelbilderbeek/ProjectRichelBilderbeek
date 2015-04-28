#ifndef WTTESTENCRANGERDIALOG_H
#define WTTESTENCRANGERDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>

namespace ribi {

struct CaesarCipherMainDialog;

struct WtCaesarCipherMainDialog : public Wt::WContainerWidget
{
  WtCaesarCipherMainDialog();
  WtCaesarCipherMainDialog(const WtCaesarCipherMainDialog&) = delete;
  WtCaesarCipherMainDialog& operator=(const WtCaesarCipherMainDialog&) = delete;

  private:
  boost::scoped_ptr<CaesarCipherMainDialog> m_dialog;
  Wt::WLineEdit * m_edit_encrypted_text;
  Wt::WLineEdit * m_edit_key;
  Wt::WLineEdit * m_edit_plain_text;

  void OnDeencryptClick();
  void OnEncryptClick();
  void ShowMain();
};

} //~namespace ribi

#endif // WTTESTENCRANGERDIALOG_H
