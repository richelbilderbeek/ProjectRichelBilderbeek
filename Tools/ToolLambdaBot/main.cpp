//Inspired by Quxbot, developed by Viderizer and Tyler Allen
#include <iostream>
#include <cstdio>
#include "ircbot.h"

const std::vector<std::string> Respond(const std::string& s);

int main()
{
  const std::string bot_name = "speaker";
  const std::string server_name = "irc.zeronode.net";
  const std::string channel_name = "#Hive5";
  const int port = 6697;

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

  //Say the message with espeak
  {
    //const std::string cmd = "espeak \"" + s + '\"';
    //std::system(cmd.c_str());
  }

  //Generate a response
  std::vector<std::string> v;

  if (s.find("JOIN") != std::string::npos)
  {
    //Welcome message
    if (s.find(":richel") != std::string::npos
     || s.find(":Bilderbikkel") != std::string::npos
     || s.find(":bilderbikkel") != std::string::npos
     || s.find(":assert") != std::string::npos
     )
    {
      v.push_back("Welcome master!");
    }
  }
  if (s.find("ain't that so?") != std::string::npos)
  {
    v.push_back("Yes, it is exactly like that!");
  }
  return v;
}
