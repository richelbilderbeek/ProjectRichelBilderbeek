#ifndef TOOLMULTIENCRANGERMAINDIALOG_H
#define TOOLMULTIENCRANGERMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/scoped_ptr.hpp>
#include "about.h"
#include "encranger.h"
#pragma GCC diagnostic pop

namespace ribi {

struct ToolMultiEncrangerMainDialog
{
  ToolMultiEncrangerMainDialog();
  void Deencrypt();
  void Encrypt();

  const std::string& GetEncryptedText() const noexcept { return m_encrypted_text; }

  int GetKey() const noexcept { return m_key; }

  const std::string& GetPlainText() const noexcept { return m_plain_text; }

  void SetEncryptedText(const std::string& s);
  void SetKey(const int i);
  void SetPlainText(const std::string& s);

  private:
  boost::scoped_ptr<Encranger> m_encranger;
  std::string m_encrypted_text;
  int m_key;
  std::string m_plain_text;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


};

} //~namespace ribi

#endif // TOOLMULTIENCRANGERMAINDIALOG_H
