//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2013-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef PVDBFILE_H
#define PVDBFILE_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

///The File used, also the main director of the program's flow
class File
{
  public:

  //Start an empty file
  File();

  ///Create a File from all its (non-static) member variables
  File(
    const std::string& about,
    const std::string& assessor_name,
    const boost::shared_ptr<pvdb::Cluster>& cluster,
    const boost::shared_ptr<ribi::cmap::ConceptMap>& concept_map,
    const std::string& question,
    const std::string& student_name,
    const std::string& version
  );

  File(const File& other) = delete;
  File& operator=(const File& other) = delete;

  ///Create a concept map with a center node with text
  static boost::shared_ptr<ribi::cmap::ConceptMap> CreateConceptMap(const std::string& text) noexcept;

  ///Convert the Cluster to a ConceptMap
  //void CreateConceptMapFromCluster();

  ///Convert XML to File
  static boost::shared_ptr<pvdb::File> FromXml(const std::string& s);

  ///Obtain the string which indicates this file is a PvdB file
  const std::string& GetAbout() const { return m_about; }

  ///Get the assessor his/her name
  const std::string& GetAssessorName() const { return m_assessor_name; }

  ///Get the student his/her clustering of concepts and examples
  boost::shared_ptr<const Cluster> GetCluster() const { return m_cluster; }
  boost::shared_ptr<      Cluster> GetCluster()       { return m_cluster; }

  ///Get the concept map
  boost::shared_ptr<const ribi::cmap::ConceptMap> GetConceptMap() const { return m_concept_map; }
  boost::shared_ptr<      ribi::cmap::ConceptMap> GetConceptMap()       { return m_concept_map; }

  ///Obtain the File filename extension
  static const std::string& GetFilenameExtension() { return m_filename_extension; }

  ///Get the assessors' questions
  std::string GetQuestion() const;

  ///Get the student his/her name
  const std::string& GetStudentName() const { return m_student_name; }

  ///Obtain a temporary filename
  static std::string GetTempFileName();

  ///Obtain a test filename
  static std::string GetTestFileName();

  ///Obtain multiple test files
  static std::vector<boost::shared_ptr<pvdb::File> > GetTests();

  ///Obtain the version of this class
  const std::string& GetVersion() const { return m_version; }

  ///Load to File from disk
  static boost::shared_ptr<pvdb::File> Load(const std::string& filename);

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
  void SetConceptMap(const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map);

  ///Set the question
  void SetQuestion(const std::string& question);

  ///Set the student his/her name
  void SetStudentName(const std::string& student_name);

  ///Convert File to XML
  static std::string ToXml(const File& file);

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
  boost::shared_ptr<ribi::cmap::ConceptMap> m_concept_map;

  ///The file extension of a a File
  static const std::string m_filename_extension;

  ///The question the student must answer
  std::string m_question;

  ///The student his/her name
  std::string m_student_name;

  ///The version of this class
  std::string m_version;

  ///AutoSave, called after each setter
  void AutoSave() const;

  ///Replace the regex_str in str with format_str
  static std::string DoXpressiveRegexReplace(
    const std::string& str,
    const std::string& regex_str,
    const std::string& format_str);

  ///Convert a file's content to a single std::string
  static std::string FileToStr(const std::string& filename);

  ///Convert a File from version 0.1
  static std::string ConvertFrom_0_1(const std::string& xml);

  ///Convert a File from version 0.2
  static std::string ConvertFrom_0_2(const std::string& xml);

  ///Convert a File from version 0.3
  static std::string ConvertFrom_0_3(const std::string& xml);

  ///Test this class
  static void Test() noexcept;

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(File* x);
};

bool operator==(const pvdb::File& lhs, const pvdb::File& rhs);

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBFILE_H
