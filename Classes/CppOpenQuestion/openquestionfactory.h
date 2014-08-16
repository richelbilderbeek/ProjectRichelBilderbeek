#ifndef OPENQUESTIONFACTORY_H
#define OPENQUESTIONFACTORY_H


#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct OpenQuestion;

struct OpenQuestionFactory
{
  OpenQuestionFactory();

  boost::shared_ptr<OpenQuestion> Create(const std::string& question) const;

  boost::shared_ptr<OpenQuestion>
    Create(
      const std::string& filename,
      const std::string& question,
      const std::vector<std::string>& answers
  ) const noexcept;


  std::string GetExampleOpenQuestionString() const noexcept { return "-,1+1=,2/two/Two"; }
  std::vector<std::string> GetInvalidOpenQuestionStrings() const noexcept;
  std::vector<boost::shared_ptr<OpenQuestion>> GetTestOpenQuestions() const noexcept;
  std::vector<std::string> GetValidOpenQuestionStrings() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // OPENQUESTIONFACTORY_H
