#ifndef TEXT_H
#define TEXT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

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
