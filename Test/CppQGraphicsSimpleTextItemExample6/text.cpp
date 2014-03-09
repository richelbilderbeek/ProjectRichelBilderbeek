#include "text.h"

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
