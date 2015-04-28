#include <boost/lexical_cast.hpp>

#include <Wt/WBreak>
#include <Wt/WFileUpload>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WPushButton>

#include "caesarciphermaindialog.h"
#include "wtcaesarciphermaindialog.h"

ribi::WtCaesarCipherMainDialog::WtCaesarCipherMainDialog()
  : m_dialog(new CaesarCipherMainDialog),
    m_edit_encrypted_text(0),
    m_edit_key(0),
    m_edit_plain_text(0)

{
  this->setContentAlignment(Wt::AlignCenter);
  ShowMain();
}

void ribi::WtCaesarCipherMainDialog::OnDeencryptClick()
{
  m_dialog->SetEncryptedText(m_edit_encrypted_text->text().toUTF8());
  try
  {
    boost::lexical_cast<int>(this->m_edit_key->text().toUTF8());
  }
  catch(boost::bad_lexical_cast&)
  {
    return;
  }
  m_dialog->SetKey(boost::lexical_cast<int>(m_edit_key->text().toUTF8()));
  m_dialog->Deencrypt();
  m_edit_plain_text->setText(m_dialog->GetPlainText().c_str());
}

void ribi::WtCaesarCipherMainDialog::OnEncryptClick()
{
  m_dialog->SetPlainText(m_edit_plain_text->text().toUTF8());
  try
  {
    boost::lexical_cast<int>(this->m_edit_key->text().toUTF8());
  }
  catch(boost::bad_lexical_cast&)
  {
    return;
  }
  m_dialog->SetKey(boost::lexical_cast<int>(m_edit_key->text().toUTF8()));
  m_dialog->Encrypt();
  m_edit_encrypted_text->setText(m_dialog->GetEncryptedText().c_str());
}

void ribi::WtCaesarCipherMainDialog::ShowMain()
{
  this->clear();
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  //Plain text
  {
    m_edit_plain_text = new Wt::WLineEdit("This is plaintext");
    m_edit_plain_text->setMinimumSize(400,Wt::Vertical);
    this->addWidget(m_edit_plain_text);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  //Arrow down
  this->addWidget(new Wt::WImage("CaesarCipherArrowDown16x16.png"));
  //Encrypt button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Encrypt");
    button->clicked().connect(
      this, &ribi::WtCaesarCipherMainDialog::OnEncryptClick);
    this->addWidget(button);
  }
  //Arrow down
  this->addWidget(new Wt::WImage("CaesarCipherArrowDown16x16.png"));
  this->addWidget(new Wt::WLabel("Key: "));
  {
    m_edit_key = new Wt::WLineEdit("12345");
    this->addWidget(m_edit_key);
  }
  //Arrow up
  this->addWidget(new Wt::WImage("CaesarCipherArrowUp16x16.png"));
  //Deencrypt button
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Deencrypt");
    button->clicked().connect(
      this, &ribi::WtCaesarCipherMainDialog::OnDeencryptClick);
    this->addWidget(button);
  }
  //Arrow up
  this->addWidget(new Wt::WImage("CaesarCipherArrowUp16x16.png"));
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  //Encrypted text
  {
    m_edit_encrypted_text = new Wt::WLineEdit;
    m_edit_encrypted_text->setMinimumSize(400,Wt::Vertical);
    this->addWidget(m_edit_encrypted_text);
  }
  OnEncryptClick();

}

