//Inspired by Quxbot, developed by Viderizer and Tyler Allen

#include <iostream>
#include "ircbot.h"

const std::vector<std::string> Respond(const std::string& s);

int main()
{
  const std::string bot_name = "lambda";
  const std::string server_name = "irc.zeronode.net";
  const std::string channel_name = "#Hive5";
  const int port = 6667;

  IrcBot(
    bot_name,
    channel_name,
    port,
    server_name,
    Respond
  );
}

const std::vector<std::string> Respond(const std::string& s)
{
  //Display the raw message to respond to
  std::cout << s << std::endl;

  //Generate a response
  std::vector<std::string> v;
  if (s.find("JOIN") != std::string::npos)
  {
    //Welcome message
    if (s.find(":richel") != std::string::npos || s.find(":Bilderbikkel") != std::string::npos)
    {
      v.push_back("Welcome master!");
    }
    if (s.find(":FSX!") != std::string::npos)
    {
      v.push_back("Hi FSX!");
    }
    if (s.find(":joachim") != std::string::npos)
    {
      v.push_back("Yo joachim!");
    }
    if (s.find(":voidzero") != std::string::npos)
    {
      v.push_back("Howdy voidzero!");
    }
    if (s.find(":winand") != std::string::npos || s.find(":Winand") != std::string::npos)
    {
      v.push_back("Wassup Winand!");
    }
  }
  if (s.find("ain't that so?") != std::string::npos)
  {
    v.push_back("Yes, it is exactly like that!");
  }
  if (s.find("lambda, who do you like best?") != std::string::npos)
  {
    v.push_back("::::::::::::::::::::::::::::::::::::::::");
    v.push_back("::::::::::::::::::::::::::::::::::::::::");
    v.push_back("::::::::::::::::+oo+so/:::::::::::::::::");
    v.push_back("::::::::::::::+yhdddddhy+:::::::::::::::");
    v.push_back("::::::::::::/sdddddddddddy+:::::::::::::");
    v.push_back(":::::::::::+ydddddddddddddds/:::::::::::");
    v.push_back("::::::::::/yddddddddddddddddy+::::::::::");
    v.push_back("::::::::::sdhhyssssyyhdddddddd+:::::::::");
    v.push_back(":::::::::oddyo++///++ooossydddy::::::::-");
    v.push_back("::::-:::oddy+++/////////++osddd+:::::::-");
    v.push_back("::::-:::sdho++///::://///+++yddo::-:::::");
    v.push_back("::::--::ydy++///::::::////++ohdy::::::::");
    v.push_back("::::---:hdo++//::::::::///+++ydy:--:::-:");
    v.push_back("::::-::/hho++//::::::::://+++shs::::::::");
    v.push_back("::::---/hho+////:::::::///+++shy:::::::-");
    v.push_back("::::---:hhs+///::::::::///++oyhy::::::::");
    v.push_back(":::::::/dds++++/::::::://+++oydy::::::::");
    v.push_back(":::::::/dhooyyhhs+:::/+osyyooshy::::::::");
    v.push_back(":::::::/hhoso+osys+//oyhyssyoshs::::::::");
    v.push_back(":::::::/sdo+osyyys+//oyyyysoosho/:::::::");
    v.push_back(":::::::ooy++osshoo+//osoysyo+osos:::::::");
    v.push_back(":::::::o+++++oooo++//ooooo+++oo+o:::::::");
    v.push_back("////:::o+o+////++++//++++//+++s++:::::::");
    v.push_back("///////++o+//////++//++/////++oo+:::::::");
    v.push_back("///////++++//:://++//+o+////+ooo/:::::::");
    v.push_back("////////++++/::/+++//oo+///++o+o::::::::");
    v.push_back("////////++o+///+++sooso+++/++o+/::::::::");
    v.push_back("//////////o++/+++++ooooo++++oo/:::::::::");
    v.push_back("//////////+o+++++++++++oo+++o+::::::::::");
    v.push_back("//////////+o++++oooooosss++oo/::::::::::");
    v.push_back("/////////+ooo++++ooooooo+++oo/::::::::::");
    v.push_back("///////+syyso+++++++oo++++ooo///::::::::");
    v.push_back("///////syhyyooo++++ooo++ooossy+///:///::");
    v.push_back("//////+yhhhhsooo+++++++ooossshs///////::");
    v.push_back("++/+//oyhhhyosooo+++++oosssoshss+//////:");
    v.push_back("/+++//syhhyyoossooooooossysosyssyo/////:");
    v.push_back("++++++syhhyyoosyyyyssyyyysoosyssyyo/////");
    v.push_back("++++++syhyyyooosyhhhhhyyysoosysssys+////");
    v.push_back("++++++syyssyooossssssssssoooshssssss////");
    v.push_back("++++++syyssho+oooooooooooooosyssssss+///");
  }
  return v;
}
