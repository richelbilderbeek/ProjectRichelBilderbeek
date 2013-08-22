#ifndef COMMANDER_H
#define COMMANDER_H

///Commander is a Singleton for managing program flow
struct Commander
{
  ///Get the Commander's only instance
  static Commander * GetInstance();

  ///Start the program
  void Run();

  ///Child asks to quit the program
  void Quit();

  private:
  ///A Singleton's constructor is private
  Commander();

  ///The one and only Commander instance
  static Commander * m_instance;

  ///Flag the tell whether to quit
  bool m_quit;
};

#endif // COMMANDER_H
