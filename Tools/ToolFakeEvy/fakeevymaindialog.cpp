#include "fakeevymaindialog.h"

#include <cstdlib>
#include <iostream>

#include <boost/lexical_cast.hpp>

FakeEvyMainDialog::FakeEvyMainDialog()
{
  const int course_index = 9;

  std::vector<std::string> cmds;

  //Create the initial file
  cmds.push_back("espeak \" \" -w \"tmp_empty.wav\"");
  cmds.push_back("sox tmp_empty.wav tmp_empty.ogg");
  //Create a silence of 1 minute
  cmds.push_back("sox tmp_empty.ogg tmp_empty.ogg pad 0:05");

  //Create the initial file
  cmds.push_back("espeak \"run\" -w \"tmp_run.ogg\"");
  cmds.push_back("espeak \"walk\" -w \"tmp_walk.ogg\"");

  //Create course index
  cmds.push_back("espeak \"course" + boost::lexical_cast<std::string>(course_index) + "\" -w \"tmp_course.ogg\"");
  //Merge
  cmds.push_back("sox tmp_course.ogg tmp_run.ogg --combine concatenate tmp_total_1.ogg");
  cmds.push_back("sox tmp_total_1.ogg tmp_empty.ogg --combine concatenate tmp_total_2.ogg");
  cmds.push_back("sox tmp_total_2.ogg tmp_walk.ogg --combine concatenate tmp_total_3.ogg");
  cmds.push_back("sox tmp_total_3.ogg tmp_empty.ogg --combine concatenate tmp_total_4.ogg");
  cmds.push_back("sox tmp_total_4.ogg tmp_run.ogg --combine concatenate tmp_total_5.ogg");


  for (const std::string& s: cmds)
  {
    std::cout << s << std::endl;
    const int error = std::system(s.c_str());
    if (error) std::cout << "Error: " << error << std::endl;
  }

}
