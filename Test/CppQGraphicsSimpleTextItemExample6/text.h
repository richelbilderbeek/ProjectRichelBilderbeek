#ifndef TEXT_H
#define TEXT_H

#include <boost/signals2.hpp>

struct Text
{
  Text(const std::string& text);

  const std::string& GetText() const { return m_text; }

  void SetText(const std::string& text);

  ///Allow a const Text to send signals
  mutable boost::signals2::signal<void()> m_signal_text_changed;

  private:

  std::string m_text;
};

#endif // TEXT_H
