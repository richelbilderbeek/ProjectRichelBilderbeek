#ifndef OPENQUESTIONDIALOGFACTORY_H
#define OPENQUESTIONDIALOGFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct OpenQuestion;
struct OpenQuestionDialog;

struct OpenQuestionDialogFactory final
{
  OpenQuestionDialogFactory();

  ///Throws an exception if it cannot be constructed
  boost::shared_ptr<OpenQuestionDialog> Create(
    const boost::shared_ptr<OpenQuestion>& open_question
  ) const;

  ///Throws an exception if it cannot be constructed
  boost::shared_ptr<OpenQuestionDialog>
    Create(
      const std::string& filename,
      const std::string& question,
      const std::vector<std::string>& answers
  ) const;

  ///Throws an exception if it cannot be constructed
  boost::shared_ptr<OpenQuestionDialog> Create(
    const std::string& s
  ) const;

  std::vector<boost::shared_ptr<OpenQuestionDialog>> GetTestOpenQuestionDialogs() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // OPENQUESTIONDIALOGFACTORY_H
