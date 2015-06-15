//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <fstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
//#include <boost/filesystem.hpp>

#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WComboBox>
#include <Wt/WFileResource>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "codetohtml.h"
#include "codetohtmldialog.h"
#include "fileio.h"
#include "wtcodetohtmldialog.h"
#pragma GCC diagnostic pop

ribi::c2h::WtDialog::Ui::Ui()
  : m_anchor(new Wt::WAnchor),
    m_area_result(new Wt::WTextArea),
    m_area_snippet(new Wt::WTextArea),
    m_box_page_type(new Wt::WComboBox),
    m_box_tech_info(new Wt::WComboBox),
    m_box_content_type(new Wt::WComboBox),
    m_button_convert(new Wt::WPushButton),
    m_edit_source(new Wt::WLineEdit),
    m_menu{},
    m_stack(new Wt::WStackedWidget)
{
  m_area_result->setMinimumSize(800,400);
  m_area_snippet->setMinimumSize(400,200);
  m_area_snippet->setText(
    "#include <iostream>\n"
    "\n"
    "int main()\n"
    "{\n"
    "  std::cout << \"Hello World\\n\"\n"
    "}\n"
    );
  /*
  {
    const std::vector<c2h::PageType> v = c2h::GetAllPageTypes();
    std::for_each(v.begin(),v.end(),
      [this](const c2h::PageType t)
      {
        m_box_page_type->addItem(c2h::PageTypeToStr(t));
      }
    );
    m_box_page_type->setCurrentIndex(0);
  }
  {
    const std::vector<c2h::ContentType> v = c2h::GetAllContentTypes();
    std::for_each(v.begin(),v.end(),
      [this](const c2h::ContentType t)
      {
        m_box_content_type->addItem(c2h::ContentTypeToStr(t));
      }
    );
    m_box_content_type->setCurrentIndex(0);
  }
  {
    const std::vector<c2h::TechInfoType> v = c2h::GetAllTechInfoTypes();
    std::for_each(v.begin(),v.end(),
      [this](const c2h::TechInfoType t)
      {
        m_box_tech_info->addItem(c2h::TechInfoTypeToStr(t));
      }
    );
    m_box_tech_info->setCurrentIndex(0);
  }
  */
  m_button_convert->setText("Convert");
  m_button_convert->setMinimumSize(400,Wt::WLength::Auto);
  m_edit_source->setText("/home/richel/Projects/Tools/ToolCodeToHtml");
  m_edit_source->setMinimumSize(400,Wt::WLength::Auto);
  m_menu = new Wt::WMenu(m_stack,Wt::Horizontal);
  m_menu->setStyleClass("menu");
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
      "1. Text snippet",m_area_snippet);
    m_menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
      "2. File or folder",m_edit_source);
    m_menu->addItem(item);
  }

}

ribi::c2h::WtDialog::WtDialog()
  : ui{}
{
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(new Wt::WBreak);
  Wt::WTable * const table = new Wt::WTable(this);
  table->elementAt(0,0)->addWidget(new Wt::WText("<b>Header and footer type</b>"));
  table->elementAt(0,1)->addWidget(ui.m_box_page_type);
  table->elementAt(1,0)->addWidget(new Wt::WText("<b>Technical information</b>"));
  table->elementAt(1,1)->addWidget(ui.m_box_tech_info);
  table->elementAt(2,0)->addWidget(new Wt::WText("<b>Source type</b>"));
  table->elementAt(2,1)->addWidget(ui.m_box_content_type);
  this->addWidget(new Wt::WBreak);
  Wt::WGroupBox * const box = new Wt::WGroupBox(this);
  box->setContentAlignment(Wt::AlignCenter);
  //Menu
  {
    //Display menu on top
    box->addWidget(new Wt::WBreak);
    box->addWidget(ui.m_menu);
    box->addWidget(new Wt::WBreak);
    //Display contents below menu
    box->addWidget(ui.m_stack);
    box->addWidget(new Wt::WBreak);
  }
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_button_convert);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_anchor);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_area_result);


  ui.m_button_convert->clicked().connect(
    this,&WtDialog::on_button_convert_clicked);

  ui.m_edit_source->changed().connect(
    this,&WtDialog::on_edit_source_textChanged);
}

std::vector<std::string> ribi::c2h::WtDialog::AreaToVector(const Wt::WTextArea * const area)
{
  assert(area);
  const std::string input = area->text().toUTF8();
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),'\n'),
    boost::algorithm::token_compress_on);
  return v;
}

/*
c2h::PageType ribi::c2h::WtDialog::GetPageType() const
{
  const std::string s = ui.m_box_page_type->currentText().toUTF8();
  return c2h::StrToPageType(s);
}

c2h::ContentType ribi::c2h::WtDialog::GetContentType() const
{
  const std::string s = ui.m_box_content_type->currentText().toUTF8();
  return c2h::StrToContentType(s);
}

c2h::TechInfoType ribi::c2h::WtDialog::GetTechInfo() const
{
  const std::string s = ui.m_box_tech_info->currentText().toUTF8();
  return c2h::StrToTechInfoType(s);
}
*/

void ribi::c2h::WtDialog::on_button_convert_clicked()
{
  /*
  if (ui.m_stack->currentIndex() == 0)
  {
    const std::string source
      = std::string(std::tmpnam(0))
      + (GetContentType() == c2h::ContentType::cpp ? ".cpp" : ".txt");

    {
      const std::vector<std::string> v = AreaToVector(ui.m_area_snippet);
      std::ofstream f(source.c_str());
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }

    boost::scoped_ptr<c2h::Dialog> d {
      new c2h::Dialog(
        GetPageType(),
        source,
        GetContentType(),
        GetTechInfo()
      )
    };
    const std::vector<std::string> v = Dialog::FileToHtml(source);
    Display(v);
    boost::filesystem::remove(source);
  }
  else
  {
    //assert(ui->tab_source->currentWidget() == ui->tab_source_snippet);
    const std::string source = ui.m_edit_source->text().toUTF8();
    if (!boost::filesystem::exists(source))
    {
      ui.m_button_convert->setText("Source (file or folder) does not exist");
      return;
    }
    boost::scoped_ptr<c2h::Dialog> d {
      new c2h::Dialog(
        GetPageType(),
        source,
        GetContentType(),
        GetTechInfo()
      )
    };
    const std::vector<std::string> v = Dialog::FolderToHtml(source);
    Display(v);
  }
  */

  const std::string source = ui.m_edit_source->text().toUTF8();
  if (
       !fileio::FileIo().IsRegularFile(source)
    && !fileio::FileIo().IsFolder(source)
  )
  {
    ui.m_button_convert->setText("Source (file or folder) does not exist");
    return;
  }

  const std::vector<std::string> v
    = fileio::FileIo().IsRegularFile(source)
    ? Dialog().FileToHtml(source)
    : Dialog().FolderToHtml(source)
  ;
  Display(v);
}

void ribi::c2h::WtDialog::Display(const std::vector<std::string>& v)
{
  std::string text;
  std::for_each(v.begin(),v.end(),
    [&text](std::string s)
    {
      text += (s + '\n');
    }
  );
  ui.m_area_result->setText(text.c_str());

  {

    const std::string filename = fileio::FileIo().GetTempFileName(".htm");
    std::ofstream f(filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    ui.m_anchor->setText((std::string("Download ") + filename).c_str() );
    ui.m_anchor->setResource(new Wt::WFileResource(filename,filename));
  }

}

void ribi::c2h::WtDialog::on_tab_source_currentChanged()
{
  if (ui.m_stack->currentIndex() == 0)
  {
    ui.m_button_convert->setText("&Convert");
    ui.m_button_convert->setEnabled(true);
  }
  else
  {
    //assert(ui->tab_source->currentWidget() == ui->tab_source_snippet);
    const std::string source = ui.m_edit_source->text().toUTF8();

    if (!fileio::FileIo().IsRegularFile(source))
    {
      ui.m_button_convert->setText("Source (file or folder) does not exist");
      ui.m_button_convert->setEnabled(false);
    }
    else
    {
      ui.m_button_convert->setText("&Convert");
      ui.m_button_convert->setEnabled(true);
    }
  }
}

void ribi::c2h::WtDialog::on_edit_source_textChanged()
{
  const std::string source = ui.m_edit_source->text().toUTF8();

  if (!fileio::FileIo().IsRegularFile(source))
  {
    ui.m_button_convert->setText("Source does not exist");
    ui.m_button_convert->setEnabled(false);
    return;
  }

  if (fileio::FileIo().IsFolder(source))
  {
    const std::vector<std::string> v
      = SortFiles(
          FilterFiles(
            fileio::FileIo().GetFilesInFolder(source)
          )
        );
    const std::string s
      = std::string("&Convert (source type: folder, ")
      + std::to_string(v.size())
      + std::string(" files)");

    ui.m_button_convert->setText(s.c_str());
    ui.m_button_convert->setEnabled(true);
  }
  else
  {
    assert(fileio::FileIo().IsFolder(source));
    ui.m_button_convert->setText("&Convert (source type: file)");
    ui.m_button_convert->setEnabled(true);
  }
}
