#ifndef PVDBFILE_H
#define PVDBFILE_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <regex>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbcluster.h"
#include "pvdbconceptmap.h"
#endif

namespace pvdb {

///The File used, also the main director of the program's flow
struct File : public boost::noncopyable
{
  //Start an empty file
  File();

  ///Create a File from all its (non-static) member variables
  File(
    const std::string& about,
    const std::string& assessor_name,
    const boost::shared_ptr<pvdb::Cluster>& cluster,
    const boost::shared_ptr<pvdb::ConceptMap>& concept_map,
    const std::string& student_name,
    const std::string& version
  );

  //File(const File& other) = delete;
  //File& operator=(const File& other) = delete;

  ///Convert the Cluster to a ConceptMap
  //void CreateConceptMapFromCluster();

  ///Convert XML to File
  static const boost::shared_ptr<pvdb::File> FromXml(const std::string& s);

  ///Obtain the string which indicates this file is a PvdB file
  const std::string& GetAbout() const { return m_about; }

  ///Get the assessor his/her name
  const std::string& GetAssessorName() const { return m_assessor_name; }

  ///Get the student his/her clustering of concepts and examples
  const boost::shared_ptr<const pvdb::Cluster> GetCluster() const { return m_cluster; }
  const boost::shared_ptr<      Cluster> GetCluster()       { return m_cluster; }

  ///Get the concept map
  const boost::shared_ptr<const pvdb::ConceptMap> GetConceptMap() const { return m_concept_map; }
  const boost::shared_ptr<      ConceptMap> GetConceptMap()       { return m_concept_map; }

  ///Obtain the File filename extension
  static const std::string GetFilenameExtension() { return m_filename_extension; }

  ///Get the assessors' questions
  const std::string GetQuestion() const;

  ///Get the student his/her name
  const std::string& GetStudentName() const { return m_student_name; }

  ///Obtain a temporary filename
  static const std::string GetTempFileName();

  ///Obtain a test filename
  static const std::string GetTestFileName();

  ///Obtain multiple test files
  static const std::vector<boost::shared_ptr<pvdb::File> > GetTests();

  ///Obtain the version of this class
  const std::string& GetVersion() const { return m_version; }

  ///Load to File from disk
  static const boost::shared_ptr<pvdb::File> Load(const std::string& filename);

  ///Save a File
  ///File will have one line of XML
  void Save(const std::string& filename) const;

  ///Set the assessor his/her name
  void SetAssessorName(const std::string& assessor_name);

  ///Write a new clustering of concepts and examples
  ///Can only be done exactly once
  void SetCluster(const boost::shared_ptr<pvdb::Cluster>& cluster);

  ///Write a new ConceptMap from a Cluster
  ///Can only be done exactly once
  void SetConceptMap(const boost::shared_ptr<pvdb::ConceptMap> concept_map);

  ///Set the student his/her name
  void SetStudentName(const std::string& student_name);

  ///Convert File to XML
  static const std::string ToXml(const File& file);

  private:
  ///Block destructor, except for the friend boost::checked_delete
  ~File() {}

  ///The string which indicates this file is a PvdB file
  std::string m_about;

  ///The assessor his/her name
  std::string m_assessor_name;

  ///The clustering of items
  ///Initially will be nullptr
  boost::shared_ptr<pvdb::Cluster> m_cluster;

  ///The concept map
  ///Initially will be nullptr
  boost::shared_ptr<pvdb::ConceptMap> m_concept_map;

  ///The file extension of a a File
  static const std::string m_filename_extension;

  ///The student his/her name
  std::string m_student_name;

  ///The question the student must answer
  //std::string m_question;

  ///The version of this class
  std::string m_version;

  ///AutoSave, called after each setter
  void AutoSave() const;

  ///Convert a file's content to a single std::string
  static const std::string FileToStr(const std::string& filename);

  ///Convert a File from version 0.1
  static const std::string ConvertFrom_0_1(const std::string& xml);

  ///Convert a File from version 0.2
  static const std::string ConvertFrom_0_2(const std::string& xml);

  ///Test this class
  static void Test();

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(File* x);
};


bool IsEqual(const pvdb::File& lhs, const pvdb::File& rhs);
/*
bool operator==(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs) = delete;
bool operator==(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs) = delete;
bool operator==(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs) = delete;
bool operator==(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs) = delete;
bool operator!=(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<const pvdb::File>& rhs) = delete;
bool operator!=(const boost::shared_ptr<pvdb::File>& lhs, const boost::shared_ptr<pvdb::File>& rhs) = delete;
*/

} //~namespace pvdb


#endif // PVDBFILE_H
