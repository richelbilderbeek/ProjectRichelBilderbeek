#include "qtbuttonincrementcommand.h"

#include <cassert>
#include <QPushButton>

QtButtonIncrementCommand::QtButtonIncrementCommand(
  QPushButton * const button)
  : m_button(button)
{
  assert(m_button);
}

void QtButtonIncrementCommand::redo()
{
  const int current_number = m_button->text().toInt();
  const int new_number = current_number + 1;
  m_button->setText(QString::number(new_number) );
  this->setText("Incremented number to " + QString::number(new_number));
}

void QtButtonIncrementCommand::undo()
{
  const int current_number = m_button->text().toInt();
  const int new_number = current_number - 1;
  m_button->setText(QString::number(new_number) );
}
