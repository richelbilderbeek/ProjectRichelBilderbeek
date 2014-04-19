#include "commander.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "firstdialog.h"
#include "seconddialog.h"
#pragma GCC diagnostic pop

Commander * Commander::m_instance = 0;

Commander::Commander()
  : m_quit(false)
{

}

Commander * Commander::GetInstance()
{
  if (!m_instance) m_instance = new Commander;
  return m_instance;
}

void Commander::Quit()
{
  m_quit = true;
}

void Commander::Run()
{
  while (!m_quit)
  {
    boost::shared_ptr<QDialog> dialog(
      ((std::rand() >> 4) % 2)
      ? dynamic_cast<QDialog*>(new FirstDialog)
      : dynamic_cast<QDialog*>(new SecondDialog));
    dialog->exec();
  }
}
