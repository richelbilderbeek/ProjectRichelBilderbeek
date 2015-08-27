//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#include "pictocodemenudialog.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <QFile>
#include <QImage>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#include "pictocodemaindialog.h"

int ribi::p2c::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  bool verbose{true};
  if (std::count(std::begin(argv),std::end(argv),"-s")
    + std::count(std::begin(argv),std::end(argv),"--silent") >= 1
  )
  {
    verbose = false;
  }

  //Image file
  std::string image_file;
  if (std::count(std::begin(argv),std::end(argv),"-f")
    + std::count(std::begin(argv),std::end(argv),"--image_file") == 0
  )
  {
    std::cout << "Please add the name of an input image file" << '\n';
    return 1;
  }
  if (std::count(std::begin(argv),std::end(argv),"-f")
    + std::count(std::begin(argv),std::end(argv),"--image_file") == 2
  )
  {
    std::cout << "Please give the name of one input image file" << '\n';
    return 1;
  }
  for (int i=1; i!=argc-1; ++i)
  {
    if (argv[i] == "-f" || argv[i] == "--image_file") { image_file = argv[i + 1]; break; }
  }
  if (!fileio::FileIo().IsRegularFile(image_file))
  {
    std::cout << "Please give the name of an existing input image file" << '\n';
    return 1;
  }

  assert(fileio::FileIo().IsRegularFile(image_file));
  if (verbose) { std::cout << "Input image file: " << image_file << '\n'; }

  //GraphicsLibrary
  GraphicsLibrary graphics_library;
  if (std::count(std::begin(argv),std::end(argv),"-t")
    + std::count(std::begin(argv),std::end(argv),"--type") == 0
  )
  {
    std::cout << "Please add the name of a graphics library" << '\n';
    return 1;
  }
  if (std::count(std::begin(argv),std::end(argv),"-t")
    + std::count(std::begin(argv),std::end(argv),"--type") == 2
  )
  {
    std::cout << "Please give the name of a graphics library once" << '\n';
    return 1;
  }
  for (int i=1; i!=argc-1; ++i)
  {
    if (argv[i] == "-t" || argv[i] == "--type")
    {
      std::string s = argv[i + 1];
      if (s == "nds") graphics_library = GraphicsLibrary::nds;
      else if (s == "qt") graphics_library = GraphicsLibrary::qt;
      else
      {
        std::cout << "Please give the correct name of graphics library, 'nds' or 'qt'" << '\n';
      }
    }
  }
  if (verbose)
  {
    std::cout << "Graphics library: "
      << (graphics_library == GraphicsLibrary::nds ? "NDS" : "Qt")
      << '\n'
    ;
  }

  //Implementation file
  std::string cpp_file;
  if (std::count(std::begin(argv),std::end(argv),"-c")
    + std::count(std::begin(argv),std::end(argv),"--cpp_file") == 0
  )
  {
    std::cout << "Please add the name of an implementation (.cpp) file" << '\n';
    return 1;
  }
  if (std::count(std::begin(argv),std::end(argv),"-c")
    + std::count(std::begin(argv),std::end(argv),"--cpp_file") == 2
  )
  {
    std::cout << "Please add the name of an implementation (.cpp) file just once" << '\n';
    return 1;
  }
  for (int i=1; i!=argc-1; ++i)
  {
    if (argv[i] == "-c" || argv[i] == "--cpp_file")
    {
      cpp_file = argv[i + 1];
      break;
    }
  }
  if (verbose)
  {
    std::cout << "Implementation (.cpp) filename: " << cpp_file << '\n';
  }

  //Header file
  std::string h_file;
  if (std::count(std::begin(argv),std::end(argv),"-e")
    + std::count(std::begin(argv),std::end(argv),"--h_file") == 0
  )
  {
    std::cout << "Please add the name of a header (.h) file" << '\n';
    return 1;
  }
  if (std::count(std::begin(argv),std::end(argv),"-e")
    + std::count(std::begin(argv),std::end(argv),"--h_file") == 2
  )
  {
    std::cout << "Please add the name of a header (.h) file just once" << '\n';
    return 1;
  }
  for (int i=1; i!=argc-1; ++i)
  {
    if (argv[i] == "-e" || argv[i] == "--h_file")
    {
      h_file = argv[i + 1];
      break;
    }
  }
  if (verbose)
  {
    std::cout << "Header (.h) filename: " << h_file << '\n';
  }

  //Header file
  std::string class_name = "Pic";
  if (std::count(std::begin(argv),std::end(argv),"-n")
    + std::count(std::begin(argv),std::end(argv),"--class_name") > 1
  )
  {
    std::cout << "Please add the class name just once" << '\n';
    return 1;
  }
  for (int i=1; i!=argc-1; ++i)
  {
    if (argv[i] == "-n" || argv[i] == "--class_name")
    {
      class_name = argv[i + 1];
      break;
    }
  }
  if (verbose)
  {
    std::cout << "Class name: " << class_name << '\n';
  }



  MainDialog d;
  d.SetInputFile(image_file);
  d.SetGraphicsLibrary(graphics_library);
  d.SetClassName(class_name);
  d.SetHeaderFileName(h_file);

  //Create header file
  {
    std::ofstream f(h_file);
    const auto text = d.ToHeaderFile();
    std::copy(std::begin(text),std::end(text),std::ostream_iterator<std::string>(f,"\n"));
  }

  //Create implementation file
  {
    std::ofstream f(cpp_file);
    const auto text = d.ToImplementationFile();
    std::copy(std::begin(text),std::end(text),std::ostream_iterator<std::string>(f,"\n"));
  }

  if (verbose)
  {
    std::cout << "Creating header file: " << (fileio::FileIo().IsRegularFile(h_file) ? "OK" : "FAIL") << '\n';
    std::cout << "Creating implementation file: " << (fileio::FileIo().IsRegularFile(cpp_file) ? "OK" : "FAIL") << '\n';
  }

  return 0;
}

ribi::About ribi::p2c::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PicToCode",
    "tool to convert a picture to C++ code",
    "the 20th of August 2015",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolPicToCode.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::p2c::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('c',"cpp_file","C++ implementation file name"),
      Help::Option('e',"h_file","C++ header file name"),
      Help::Option('f',"image_file","input image filename"),
      Help::Option('n',"class_name","class name ('Pic' by default)"),
      Help::Option('s',"silent","show no output on screen"),
      Help::Option('t',"type","NDS or Qt"),
    },
    {
      GetAbout().GetFileTitle() + " -f pic.png -t nds -c pic.cpp -h pic.h -s",
      GetAbout().GetFileTitle() + " -f pic.png -t nds -c pic.cpp -h pic.h -l MyPictureClass",
      GetAbout().GetFileTitle() + " --image_file pic.png --type qt --cpp_file pic.cpp --h_file pic.h",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::p2c::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPicToCode
  };
  assert(p);
  return p;
}

std::string ribi::p2c::MenuDialog::GetVersion() const noexcept
{
  return "1.7";
}

std::vector<std::string> ribi::p2c::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-10-10: version 1.0: initial version",
    "2010-10-11: version 1.1: added tranparency support",
    "2011-04-18: version 1.2: added support for QPixmap",
    "2011-04-18: version 1.3: added menu, added web application",
    "2013-11-04: version 1.4: conformized to ProjectRichelBilderbeekConsole",
    "2015-08-20: version 1.5: NDS code has seperate header and implementation file",
    "2015-08-26: version 1.6: created command-line version",
    "2015-08-27: version 1.7: added --class_name flag to command-line version, creates correct NDS images",
  };
}

#ifndef NDEBUG
void ribi::p2c::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    MainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    MenuDialog d;
    const std::string temp_png{"temp.png"};
    const std::string temp_h{"temp.h"};
    const std::string temp_cpp{"temp.cpp"};
    QImage image(":/p2c/images/R.png");
    image.save(temp_png.c_str());
    assert(QFile::exists(temp_png.c_str()));
    d.Execute(
      { "PicToCode",
        "-f", temp_png,
        "-t", "nds",
        "-c", temp_cpp,
        "-e", temp_h,
        "-s"  //Be silent
      }
    );
    assert(QFile::exists(temp_cpp.c_str()));
    assert(QFile::exists(temp_h.c_str()));
    std::remove(temp_png.c_str());
    std::remove(temp_cpp.c_str());
    std::remove(temp_h.c_str());
  }
  //Add classname
  {
    MenuDialog d;
    const std::string temp_png{"temp.png"};
    const std::string temp_h{"temp.h"};
    const std::string temp_cpp{"temp.cpp"};
    QImage image(":/p2c/images/R.png");
    image.save(temp_png.c_str());
    assert(QFile::exists(temp_png.c_str()));
    d.Execute(
      { "PicToCode",
        "-f", temp_png,
        "-t", "nds",
        "-c", temp_cpp,
        "-e", temp_h,
        "-l", "MyPicture",
        //"-s"  //Be silent
      }
    );
    assert(QFile::exists(temp_cpp.c_str()));
    assert(QFile::exists(temp_h.c_str()));
    std::remove(temp_png.c_str());
    std::remove(temp_cpp.c_str());
    std::remove(temp_h.c_str());
  }
}
#endif
