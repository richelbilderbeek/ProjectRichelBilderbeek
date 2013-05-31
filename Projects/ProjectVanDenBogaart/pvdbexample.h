#ifndef PVDBEXAMPLE_H
#define PVDBEXAMPLE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "pvdbcompetency.h"


namespace pvdb {

struct ExampleFactory;

struct Example
{
  Example(const pvdb::Example&) = delete;
  pvdb::Example& operator=(const pvdb::Example&) = delete;

  ///Convert a pvdb::Competency to a std::string
  static const std::string CompetencyToStr(const pvdb::Competency competency);

  ///Create an example from XML
  static const boost::shared_ptr<pvdb::Example> FromXml(const std::string& s);

  ///Get the competency, as might be judged by an assessor
  pvdb::Competency GetCompetency() const { return m_competency; }

  ///Get the text of the example
  const std::string& GetText() const { return m_text; }

  ///Set the competency
  void SetCompetency(const pvdb::Competency competency);

  ///Set the text
  void SetText(const std::string& text);

  ///Convert a std::string to a pvdb::Competency
  static pvdb::Competency StrToCompetency(const std::string& s);

  ///Test this class
  static void Test();

  ///Convert Example to a std::string
  static const std::string ToXml(const boost::shared_ptr<const pvdb::Example>& t);

  ///Emitted when SetCompetency changes the competency
  boost::signals2::signal<void(Example*)> m_signal_competency_changed;

  ///Emitted when SetText changes the text
  boost::signals2::signal<void(Example*)> m_signal_text_changed;

private:

  ///The competency, as might be judged by an assessor
  pvdb::Competency m_competency;

  ///The text of the example
  ///For example: 'Plato', 'When I was a kid', 'As I did on holiday'
  std::string m_text;

  ///Set the competency with a string
  void SetCompetencyAsStr(const std::string& s) const;

  ///Use checked_delete only
  ~Example() {}
  friend void boost::checked_delete<>(Example* x);

  ///Only let ExampleFactory create Example instances
  Example(const std::string& text, const pvdb::Competency competency = pvdb::Competency::uninitialized);
  friend class ExampleFactory;
};


bool operator==(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator==(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator==(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator==(const pvdb::Example& lhs,const pvdb::Example& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator!=(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator!=(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator!=(const pvdb::Example& lhs,const pvdb::Example& rhs) = delete;
bool operator<(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator<(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator<(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator>(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator>(const boost::shared_ptr<const pvdb::Example>& lhs,const boost::shared_ptr<pvdb::Example>& rhs);
bool operator>(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);
bool operator>(const boost::shared_ptr<pvdb::Example>& lhs,const boost::shared_ptr<const pvdb::Example>& rhs);

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbexamplefactory.h"
#endif

#endif // PVDBEXAMPLE_H
