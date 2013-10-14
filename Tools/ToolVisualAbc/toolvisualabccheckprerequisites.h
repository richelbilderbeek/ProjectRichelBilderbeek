#ifndef TOOLVISUALABCCHECKPREREQUISITES_H
#define TOOLVISUALABCCHECKPREREQUISITES_H

namespace ribi {

struct CheckPrerequisites
{
  CheckPrerequisites();

  private:
  void CheckAbc2midi();
  void CheckAbcm2ps();
  void CheckConvert();
  void CheckPlaysound();
  static bool FileExists(const std::string& filename);
};

} //~namespace ribi

#endif // TOOLVISUALABCCHECKPREREQUISITES_H
