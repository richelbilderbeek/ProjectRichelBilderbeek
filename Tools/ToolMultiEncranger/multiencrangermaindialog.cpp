#include "multiencrangermaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/algorithm/string/split.hpp>

#include "container.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::ToolMultiEncrangerMainDialog::ToolMultiEncrangerMainDialog()
  : m_encranger(new Encranger(0)), // 0 == m_key
    m_encrypted_text{},
    m_key(0),
    m_plain_text{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::ToolMultiEncrangerMainDialog::Deencrypt()
{
  //Convert encrypted text to vector
  auto v = Container().SeperateString(m_encrypted_text,'\n');

  //Convert encrypted lines to plaintext lines
  for (auto &s: v) { s = m_encranger->Deencrypt(s); }

  //Convert plaintext lines to string
  m_plain_text.clear();
  for (const auto s: v) { m_plain_text += s + '\n'; }
  m_plain_text.resize(m_plain_text.size() - 1); //Pop trailing newline
}

void ribi::ToolMultiEncrangerMainDialog::Encrypt()
{
  //Convert encrypted text to vector
  auto v = Container().SeperateString(m_plain_text,'\n');

  //Convert encrypted lines to plaintext lines
  for (auto &s: v) { s = m_encranger->Encrypt(s); }

  //Convert plaintext lines to string
  m_encrypted_text.clear();
  for (const auto s: v) { m_encrypted_text += s + '\n'; }
  m_encrypted_text.resize(m_plain_text.size() - 1); //Pop trailing newline
}

/*
std::vector<std::string> ribi::ToolMultiEncrangerMainDialog::SeperateString(
  const std::string& input,
  const char seperator) const noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}
*/

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

#ifndef NDEBUG
void ribi::ToolMultiEncrangerMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ToolMultiEncrangerMainDialog::Test");
  TRACE("Finished ribi::ToolMultiEncrangerMainDialog::Test successfully");
}
#endif
