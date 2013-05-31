#ifndef VISUALABCCHECKPREREQUISITES_H
#define VISUALABCCHECKPREREQUISITES_H

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

#endif // VISUALABCCHECKPREREQUISITES_H
