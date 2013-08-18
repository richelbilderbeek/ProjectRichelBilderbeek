//Inspired by Quxbot, developed by Viderizer and Tyler Allen

#include <ircbot.h>

#include <stdexcept>
#include <netdb.h>

#include <boost/lexical_cast.hpp>

IrcBot::IrcBot(
  const std::string& bot_name,
  const std::string& channel_name,
  const int port,
  const std::string& server_name,
  const std::function<const std::vector<std::string>(const std::string& input)>& respond_function)
{
  const std::string port_str = boost::lexical_cast<std::string>(port);

  addrinfo hints;
  memset(&hints, 0, sizeof(hints)); // make sure the struct is empty

  hints.ai_family   = AF_UNSPEC; // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

  addrinfo *servinfo = 0;

  if (const int res = getaddrinfo(const_cast<char*>(server_name.c_str()), const_cast<char*>(port_str.c_str()), &hints, &servinfo))
  {
    const std::string s = std::string("getaddrinfo: ") + std::string(gai_strerror(res));
    throw std::runtime_error(s);
  }

  const int socket_index = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (socket_index == -1)
  {
    std::perror("client: socket");
    const std::string s = "client: socket";
    throw std::runtime_error(s);
  }

  if (connect(socket_index, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
  {
    close(socket_index);
    std::perror("client: connect");
    const std::string s = "client: connect";
    throw std::runtime_error(s);
  }

  freeaddrinfo(servinfo);

  for (int count = 0; ; ++count)
  {
    switch (count)
    {
      case 2: //Note: must be 2 on e.g. irc.freenode.net
      {
        const std::string nickname_str = "NICK " + bot_name + "\r\n";
        send(socket_index,nickname_str.c_str(),nickname_str.size(),0);

        const std::string user_str = "USER " + bot_name + " tolmoon tolsun :" + bot_name + "\r\n";
        send(socket_index,user_str.c_str(),user_str.size(),0);
      }
      break;
      case 3: //Note: must be 3 on e.g. irc.freenode.net
      {
        const std::string joinmsg = "JOIN " + channel_name + "\r\n";
        send(socket_index,joinmsg.c_str(),joinmsg.size(),0);
        break;
      }
      default:
        break;
    }

    const int max_data_size = 1024;
    char buf[max_data_size];
    const int numbytes = recv(socket_index, buf, max_data_size-1, 0);
    buf[numbytes] = '\0';

    const std::vector<std::string> response = respond_function(buf);
    for (const std::string& s: response)
    {
      const std::string msg = std::string("PRIVMSG ") + channel_name + std::string(" :") + s + std::string("\r\n");
      send(socket_index,msg.c_str(),msg.size(),0);
    }

    if (std::string(buf).find("PING") != std::string::npos)
    {
      const std::string msg = std::string("PONG\r\n");
      send(socket_index,msg.c_str(),msg.size(),0);
    }

    if (numbytes == 0)
    {
      std::cout << "CONNECTION CLOSED\n";
      break;
    }
  }
  close(socket_index);
}
