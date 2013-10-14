#ifndef TOOLVISUALABCMAINDIALOG_H
#define TOOLVISUALABCMAINDIALOG_H

#include <string>
#include <vector>

namespace ribi {

struct VisualAbcMainDialog
{
  static void ConvertToPng(const std::string& s);
  static void ConvertToMid(const std::string& s);
  static void PlayMid();
  static const std::vector<std::string> GetAbcFriday();
  static const std::string m_abc_filename;
  static const std::string m_log_filename;
  static const std::string m_mid_filename;
  static const std::string m_png_filename;
  static const std::string m_pngs_filename;
};

} //~namespace ribi

#endif // TOOLVISUALABCMAINDIALOG_H
