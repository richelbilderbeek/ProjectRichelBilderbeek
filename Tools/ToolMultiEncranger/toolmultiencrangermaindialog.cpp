#include "toolmultiencrangermaindialog.h"

ribi::ToolMultiEncrangerMainDialog::ToolMultiEncrangerMainDialog()
  : m_encranger(new Encranger(0)), // 0 == m_key
    m_encrypted_text{},
    m_key(0),
    m_plain_text{}
{

}

void ribi::ToolMultiEncrangerMainDialog::Deencrypt()
{
  m_plain_text = m_encranger->Deencrypt(m_encrypted_text);
}

void ribi::ToolMultiEncrangerMainDialog::Encrypt()
{
  m_encrypted_text = m_encranger->Encrypt(m_plain_text);
}

void ribi::ToolMultiEncrangerMainDialog::SetEncryptedText(const std::string& s)
{
  m_encrypted_text = s;
}

void ribi::ToolMultiEncrangerMainDialog::SetKey(const int i)
{
  m_encranger.reset(new Encranger(i));
}

void ribi::ToolMultiEncrangerMainDialog::SetPlainText(const std::string& s)
{
  m_plain_text = s;
}
