//Inspired by Quxbot, developed by Viderizer and Tyler Allen

#include <fstream>
#include <functional>
#include <string>
#include <vector>

struct IrcBot
{
  IrcBot(
  const std::string& bot_name,
  const std::string& channel_name,
  const int port,
  const std::string& server_name,
  const std::function<const std::vector<std::string>(const std::string& input)>& respond_function);

  private:
  const std::string ReadLine() const;
  void Send(const std::string& text);

  mutable std::fstream m_log_file;
  int m_socket_index;
};
