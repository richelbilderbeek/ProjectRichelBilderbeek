#include "secretmessagemenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>
#include <QImage>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "secretmessagemaindialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::sema::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  const int n = static_cast<int>(argv.size());
  if (argc != 7 && argc != 8)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::string source_filename;
  for (int i=1; i!=n-1; ++i)
  {
    if (argv[i] == "-s" || argv[i] == "--source")
    {
      source_filename = argv[i+1];
    }
  }
  std::string message_filename;
  for (int i=1; i!=n-1; ++i)
  {
    if (argv[i] == "-m" || argv[i] == "--message")
    {
      message_filename = argv[i+1];
    }
  }
  std::string result_filename;
  for (int i=1; i!=n-1; ++i)
  {
    if (argv[i] == "-r" || argv[i] == "--result")
    {
      result_filename = argv[i+1];
    }
  }
  bool force_overwrite = false;
  for (int i=1; i!=n; ++i)
  {
    if (argv[i] == "-f" || argv[i] == "--force")
    {
      force_overwrite = true;
    }
  }

  if (!fileio::FileIo().IsRegularFile(source_filename))
  {
    std::cout << "Please supply a valid source filename" << '\n';
    return 1;
  }

  if (!fileio::FileIo().IsRegularFile(message_filename))
  {
    std::cout << "Please supply a valid message filename" << '\n';
    return 1;
  }

  if (fileio::FileIo().IsRegularFile(result_filename) && !force_overwrite)
  {
    std::cout << "Result file already exists" << '\n'
      << "Use -f to force overwrite of existing file" << '\n';
    return 1;
  }

  const boost::shared_ptr<QImage> source { new QImage(source_filename.c_str()) };
  const boost::shared_ptr<QImage> message { new QImage(message_filename.c_str()) };
  const boost::shared_ptr<QImage> result { MainDialog().CreateSecretMessageRed(source,message) };
  result->save(result_filename.c_str());
  assert(fileio::FileIo().IsRegularFile(result_filename));
  return 1;
}

ribi::About ribi::sema::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SecretMessage",
    "tool to add secret messages to images",
    "the 23rd of February 2014",
    "2009-2015",
    "http://www.richelbilderbeek.nl/ToolSecretMessage.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::sema::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('f',"force","force to overwrite result to file if it already exists"),
      Help::Option('s',"source","filename of the source image"),
      Help::Option('m',"message","filename of the message image"),
      Help::Option('r',"result","filename of the resulting image"),
    },
    {
      GetAbout().GetFileTitle() + "-s source.png -m message.png -r result.png",
      GetAbout().GetFileTitle() + "-s source.png -m message.png -f -r result.png",
      GetAbout().GetFileTitle() + "--source beach.png --message secret.png --results beach_with_message.png"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::sema::MenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramSecretMessage
  };
  assert(p);
  return p;
}

std::string ribi::sema::MenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::sema::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-01-11: version 1.0: initial Windows-only version",
    "2012-08-03: version 2.0: port to Qt Creator"
    "2014-02-23: version 2.1: added command-line interface"
  };
}

#ifndef NDEBUG
void ribi::sema::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string source_file { fileio::FileIo().GetTempFileName(".png") };
  const std::string message_file { fileio::FileIo().GetTempFileName(".png") };
  const std::string target_file { fileio::FileIo().GetTempFileName(".png") };
  {
    QFile qt_source_file(":/secretmessage/images/ToolSecretMessageWhite.png");
    qt_source_file.copy(source_file.c_str());
  }
  {
    QFile qt_message_file(":/secretmessage/images/ToolSecretMessageR.png");
    qt_message_file.copy(message_file.c_str());
  }
  assert( fileio::FileIo().IsRegularFile(source_file));
  assert( fileio::FileIo().IsRegularFile(message_file));
  assert(!fileio::FileIo().IsRegularFile(target_file));
  MenuDialog().Execute( { "ToolSecretMessage", "-s",source_file,"-m",message_file,"-r",target_file} );
  assert(fileio::FileIo().IsRegularFile(source_file));
  assert(fileio::FileIo().IsRegularFile(message_file));
  assert(fileio::FileIo().IsRegularFile( target_file));

  fileio::FileIo().DeleteFile(source_file);
  fileio::FileIo().DeleteFile(message_file);
  fileio::FileIo().DeleteFile(target_file);

  assert(!fileio::FileIo().IsRegularFile(source_file));
  assert(!fileio::FileIo().IsRegularFile(message_file));
  assert(!fileio::FileIo().IsRegularFile( target_file));
}
#endif
