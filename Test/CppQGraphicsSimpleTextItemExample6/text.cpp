#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "text.h"
#pragma GCC diagnostic pop

Text::Text(const std::string& text)
  : m_signal_text_changed{},
    m_text(text)

{

}

void Text::SetText(const std::string& text)
{
  m_text = text;
  m_signal_text_changed();
}

