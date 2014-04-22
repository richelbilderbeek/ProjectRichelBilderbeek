//Inspired by Quxbot, developed by Viderizer and Tyler Allen
#include <ircbot.h>

#include <fstream>
#include <stdexcept>
#include <netdb.h>

#include <boost/lexical_cast.hpp>

IrcBot::IrcBot(
  const std::string& bot_name,
  const std::string& channel_name,
  const int port,
  const std::string& server_name,
  const std::function<const std::vector<std::string>(const std::string& input)>& respond_function)
  : m_log_file("log_lambdabot.txt"),
    m_socket_index{-1}
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

  m_socket_index = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (m_socket_index == -1)
  {
    std::perror("client: socket");
    const std::string s = "client: socket";
    throw std::runtime_error(s);
  }

  if (connect(m_socket_index, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
  {
    close(m_socket_index);
    std::perror("client: connect");
    const std::string s = "client: connect";
    throw std::runtime_error(s);
  }

  freeaddrinfo(servinfo);

  for (int count = 0; ; ++count)
  {
    std::cout << count << std::endl;
    switch (count)
    {
      case 2: //Note: must be 2 on e.g. irc.freenode.net
      {
        const std::string nickname_str = "NICK " + bot_name;
        Send(nickname_str);

        const std::string user_str = "USER " + bot_name + " tolmoon tolsun :" + bot_name;
        Send(user_str);
      }
      break;
      case 3: //Note: must be 3 on e.g. irc.freenode.net
      {
        const std::string joinmsg = "JOIN " + channel_name;
        Send(joinmsg);
        break;
      }
      default:
        break;
    }
    //Read text from IRC
    const std::string line { ReadLine() };

    if (line.find("PING") != std::string::npos)
    {
      const std::string msg = std::string("PONG");
      Send(msg);
      continue;
    }
    if (1 == 2 && line.find("266") != std::string::npos)
    {

      const std::string joinmsg = "JOIN " + channel_name;
      Send(joinmsg);
      continue;
    }

    if (1 == 1 && line.find("Found your hostname") != std::string::npos)
    {
      const std::string connect_str = "/connect " + server_name + "/6697 -ssl";
      Send(connect_str);
      continue;
    }

    if (1==2)
    {
      const std::string nickname_str = "NICK " + bot_name;
      Send(nickname_str);
      const std::string user_str = "USER " + bot_name + " tolmoon tolsun :" + bot_name;
      Send(user_str);
    }

    const std::vector<std::string> response = respond_function(line);
    for (const std::string& s: response)
    {
      const std::string msg = std::string("PRIVMSG ")
        + channel_name + std::string(" :") + s;
      Send(msg.c_str());
    }

    if (line.empty() == true)
    {
      m_log_file << "CONNECTION CLOSED" << std::endl;
      std::clog << "CONNECTION CLOSED" << std::endl;
      break;
    }
  }
  close(m_socket_index);
}

const std::string IrcBot::ReadLine() const
{
  const int max_data_size = 1024;
  char buf[max_data_size];
  std::cout << "Start reading line" << std::endl;
  const int numbytes = recv(m_socket_index, buf, max_data_size-1, 0);
  buf[numbytes] = '\0';
  const std::string line{buf};
  m_log_file << "Received: '" << line << "\'\n";
  std::clog << "Received: '" << line << "\'" << std::endl;
  return line;
}

void IrcBot::Send(const std::string& s)
{
  const std::string t = s + "\r\n";
  m_log_file << "Sent: '" << s << '\'' << std::endl;
  std::clog << "Sent: '" << s << '\'' << std::endl;
  send(m_socket_index,t.c_str(),t.size(),0);
}
