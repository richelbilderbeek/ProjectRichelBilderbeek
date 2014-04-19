//---------------------------------------------------------------------------

#ifndef UnitQuestionGeneratorH
#define UnitQuestionGeneratorH
//---------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
#include <set>
#include "UnitQuestionType.h"
//---------------------------------------------------------------------------
struct QuestionGenerator
{
  typedef std::multimap<std::string,std::string> QuestionMap;
  typedef QuestionMap::const_iterator Iterator;
  typedef std::pair<Iterator,Iterator> Range;

  QuestionGenerator(const std::set<QuestionType>& types);
  //Main communication
  std::string GetQuestion() const;
  bool GiveAnswer(const std::string& answer);
  std::vector<std::string> GetAnswers() const;
  //Correct/incorrect
  int GetNcorrect() const { return mNcorrect; }
  int GetNincorrect() const { return mNincorrect; }
  //Question types
  std::set<QuestionType> mQuestionTypes;

  const QuestionMap mEasyVerbs;
  const QuestionMap mMediumVerbs;
  const QuestionMap mHardVerbs;
  const QuestionMap mEasyNouns;
  const QuestionMap mMediumNouns;
  const QuestionMap mHardNouns;
  const QuestionMap mEasySentences;
  const QuestionMap mMediumSentences;
  const QuestionMap mHardSentences;

  private:
  int mNcorrect;
  int mNincorrect;

  mutable std::string mLastQuestion;
  mutable Range mAnswers;


  //Create the question maps
  //Verbs
  QuestionMap GetEasyVerbs() const;
  QuestionMap GetMediumVerbs() const;
  QuestionMap GetHardVerbs() const;
  //Nouns
  QuestionMap GetEasyNouns() const;
  QuestionMap GetMediumNouns() const;
  QuestionMap GetHardNouns() const;
  //Sentences
  QuestionMap GetEasySentences() const;
  QuestionMap GetMediumSentences() const;
  QuestionMap GetHardSentences() const;

  //Read from the existing question maps
  //Verbs
  std::string GetQuestion(const QuestionMap& questions) const;
};
//---------------------------------------------------------------------------
std::string ToUpperCase(std::string s);

#endif
