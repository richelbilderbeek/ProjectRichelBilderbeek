#ifndef HOMETRAINERMAINDIALOG_H
#define HOMETRAINERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <vector>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct Question;

struct HometrainerMainDialog
{
  ///Load questions from file
  HometrainerMainDialog(const std::string& filename);

  HometrainerMainDialog(const std::vector<boost::shared_ptr<const ribi::Question> >& questions);

  ///Get the parsed questions
  const std::vector<boost::shared_ptr<const Question> > GetQuestions() const noexcept
  {
    return m_questions;
  }


  private:

  ///The questions loaded
  const std::vector<boost::shared_ptr<const Question> > m_questions;

  static const std::vector<boost::shared_ptr<const Question> > CreateQuestions(
    const std::string& filename);

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  static bool IsRegularFile(const std::string& filename) noexcept;
};

} //namespace ribi

#endif // HOMETRAINERMAINDIALOG_H
