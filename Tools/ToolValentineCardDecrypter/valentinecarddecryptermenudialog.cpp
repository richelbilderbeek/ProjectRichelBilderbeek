#include "valentinecarddecryptermenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QFile>

#include "fileio.h"
//#include "imagecanvas.h"
#include "valentinecarddecryptermaindialog.h"
#include "valentinecardsymbols.h"
#include "valentinecardsymbol.h"
#include "textcanvas.h"

#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ValentineCardDecrypterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1 && argc != 3 && argc != 5)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  if (argc == 1)
  {

    for (auto s: ValentineCardSymbols().CreateAlphabet().left)
    {
      std::cout << s.first << "\n" << (*s.second.ToTextCanvas()) << std::endl;
    }
    return 0;
  }
  std::string text = "abcdefghijklmnopqrstuvwxyz";
  for (int i=0; i!=argc-1; ++i)
  {
    if (argv[i] == "-t" || argv[i] == "--text")
    {
      text = argv[i+1];
    }
  }
  std::string filename;
  for (int i=0; i!=argc-1; ++i)
  {
    if (argv[i] == "-f" || argv[i] == "--file" || argv[i] == "--filename")
    {
      filename = argv[i+1];
    }
  }

  const std::vector<ValentineCardSymbol> v {
    ValentineCardSymbols().TextToSymbols(text)
  };
  if (filename.empty())
  {
    //To std::cout
    for (const ValentineCardSymbol s: v)
    {
      std::cout << (*s.ToTextCanvas()) << '\n';
    }
    return 0;
  }
  else
  {
    //To pixmap
    const int sz = static_cast<int>(v.size());
    QImage image(sz * 7, 7,QImage::Format::Format_RGB32);
    for (int i=0; i!=sz; ++i)
    {
      const ValentineCardSymbol s { v[i] };
      const boost::shared_ptr<QImage> image_char { s.ToImage() };
      for (int row = 0; row!=7; ++row)
      {
        for (int col = 0; col!=7; ++col)
        {
          image.setPixel((7*i) + col,row,image_char->pixel(col,row));
        }
      }
    }
    image.save(filename.c_str());
    return 0;
  }
}

const ribi::About ribi::ValentineCardDecrypterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ValentineCardDecrypter",
    "tool to decrypt a valentine card",
    "the 18th of February 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolValentineCardDecrypter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  return a;
}

const ribi::Help ribi::ValentineCardDecrypterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","save the text as a picture to filename"),
      Help::Option('t',"text","the text to convert")
    },
    {
      GetAbout().GetFileTitle(),
      GetAbout().GetFileTitle() + " -t \"Hello world\"",
      GetAbout().GetFileTitle() + " --text \"Hello world\" --filename result.png",
    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::ValentineCardDecrypterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramValentineCardDecrypter
  };
  assert(p);
  return p;
}

const std::string ribi::ValentineCardDecrypterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ValentineCardDecrypterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-02-18: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::ValentineCardDecrypterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ValentineCardDecrypterMenuDialog::Test");
  ValentineCardDecrypterMenuDialog d;
  d.Execute( {"ValentineCardDecrypter"} );
  d.Execute( {"ValentineCardDecrypter", "--text", "Hello world"} );
  {
    const std::string filename { fileio::GetTempFileName(".png") };
    assert(!fileio::IsRegularFile(filename));
    d.Execute( {"ValentineCardDecrypter", "-t", "Test", "-f", filename} );
    assert(fileio::IsRegularFile(filename));
    fileio::DeleteFile(filename);
    assert(!fileio::IsRegularFile(filename));
  }
  {
    const std::string filename { fileio::GetTempFileName(".png") };
    assert(!fileio::IsRegularFile(filename));
    d.Execute( {"ValentineCardDecrypter", "--file", filename} );
    assert(fileio::IsRegularFile(filename));
    fileio::DeleteFile(filename);
    assert(!fileio::IsRegularFile(filename));
  }
  TRACE("Finished ribi::ValentineCardDecrypterMenuDialog::Test successfully");
}
#endif
