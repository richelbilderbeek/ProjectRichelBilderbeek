//---------------------------------------------------------------------------
/*
Program, class for a program by Richel Bilderbeek
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeekProgram.htm
//---------------------------------------------------------------------------
#ifndef RIBI_RICHELBILDERBEEKPROGRAM_H
#define RIBI_RICHELBILDERBEEKPROGRAM_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "richelbilderbeekprogramstatus.h"
#include "richelbilderbeekprogramtype.h"
#pragma GCC diagnostic pop

namespace ribi {

///RichelBilderbeek::Program is the base class for program information
struct Program
{
  virtual ~Program() noexcept {}

  ///Create a std::vector with all different Program instances in it
  static boost::shared_ptr<Program> CreateProgram(const ProgramType type) noexcept;

  ///Create a std::vector with all different Program instances in it
  static std::vector<boost::shared_ptr<Program>> GetAllPrograms() noexcept;

  ///Get the filename of a console version screenshot
  virtual std::string GetFilenameConsole() const noexcept = 0;

  ///Get the filename of a desktop platform-independent version screenshot
  virtual std::string GetFilenameDesktop() const noexcept = 0;

  ///Get the filename of a desktop windows-only version screenshot
  virtual std::string GetFilenameDesktopWindowsOnly() const noexcept = 0;

  ///Get the filename of a web application version screenshot
  virtual std::string GetFilenameWeb() const noexcept = 0;

  ///Status of the console-only version
  virtual ProgramStatus GetStatusConsole() const noexcept = 0;

  ///Status of the Windows-only desktop version
  virtual ProgramStatus GetStatusDesktopWindowsOnly() const noexcept = 0;

  ///Status of the platform-independent desktop version
  virtual ProgramStatus GetStatusDesktop() const noexcept = 0;

  ///Status of the web application version
  virtual ProgramStatus GetStatusWebApplication() const noexcept = 0;

  ///The item its enum name, e.g. 'k3OpEenRij'
  std::string GetName() const noexcept;

  ///The item its on-screen name, e.g. 'K3-Op-Een-Rij'
  std::string GetScreenName() const noexcept;

  ///The program, e.g. 'RichelBilderbeekProgramType::boenken'
  virtual ProgramType GetType() const noexcept = 0;

  ///The type of program its name, e.g. 'Game'
  virtual std::string GetTypeName() const noexcept = 0;

  ///The item its URL (at http://ww.richelbilderbeek.nl), e.g. 'ToolSimMysteryMachine.htm'
  virtual std::string GetUrl() const noexcept = 0;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///Get the base of a filename
  std::string GetFilenameBase() const noexcept;
};

///ProgramClass is the base class for all class demonstration programs
struct ProgramClass : public Program
{
  virtual ~ProgramClass() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept { return "class"; }
};

struct ProgramGame : public Program
{
  virtual ~ProgramGame() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept { return "game"; }
};

struct ProgramProject : public Program
{
  virtual ~ProgramProject() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept { return "project"; }
};

struct ProgramTool : public Program
{
  virtual ~ProgramTool() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept { return "tool"; }
};

struct ProgramAminoAcidFighter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameAminoAcidFighter_0_9.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameAminoAcidFighter_0_9.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "AminoAcidFighter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::aminoAcidFighter; }
  std::string GetUrl() const noexcept { return "GameAminoAcidFighter.htm"; }
};

struct ProgramAthleticLand : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Athletic Land"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::athleticLand; }
  std::string GetUrl() const noexcept { return "GameAthleticLand.htm"; }
};

struct ProgramAthleticLandVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameAthleticLand_0_9.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Athletic Land (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::athleticLandVcl; }
  std::string GetUrl() const noexcept { return "GameAthleticLandVcl.htm"; }
};

struct ProgramAsciiArter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolAsciiArter_6_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolAsciiArter_5_2.png"; }
  std::string GetScreenName() const noexcept { return "AsciiArter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::asciiArter; }
  std::string GetUrl() const noexcept { return "ToolAsciiArter.htm"; }
};

struct ProgramAsciiArterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolAsciiArter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "AsciiArter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::asciiArterVcl; }
  std::string GetUrl() const noexcept { return "ToolAsciiArterVcl.htm"; }
};

struct ProgramBarbaImage : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolBarbaImage_1_3.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "BarbaImage"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::barbaImage; }
  std::string GetUrl() const noexcept { return "ToolBarbaImage.htm"; }
};

struct ProgramBeerWanter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameBeerWanter5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "BeerWanter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::beerWanter; }
  std::string GetUrl() const noexcept { return "GameBeerWanter.htm"; }
};

struct ProgramBeerWanterVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameBeerWanter3.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "BeerWanter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::beerWanterVcl; }
  std::string GetUrl() const noexcept { return "GameBeerWanterVcl.htm"; }
};

struct ProgramBochum : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ProjectBochumGaborFiltersResults.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Project Bochum"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::bochum; }
  std::string GetUrl() const noexcept { return "ProjectBochum.htm"; }
};

struct ProgramBoenken : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameBoenken_4_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Boenken"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::boenken; }
  std::string GetUrl() const noexcept { return "GameBoenken.htm"; }
};

struct ProgramBoenkenVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameBoenken_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Boenken (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::boenkenVcl; }
  std::string GetUrl() const noexcept { return "GameBoenkenVcl.htm"; }
};

struct ProgramBrainweaver : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Brainweaver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::brainweaver; }
  std::string GetUrl() const noexcept { return "ProjectBrainweaver.htm"; }
};

struct ProgramBristol : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ProjectBristol_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Bristol"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::bristol; }
  std::string GetUrl() const noexcept { return "ProjectBristol.htm"; }
};

struct ProgramCaesarCipher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolCaesarCipher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "CaesarCipher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::caesarCipher; }
  std::string GetUrl() const noexcept { return "ToolCaesarCipher.htm"; }
};

struct ProgramChrisWiley : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectChrisWiley_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Project Chris Wiley"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::chrisWiley; }
  std::string GetUrl() const noexcept { return "ProjectChrisWiley.htm"; }
};

struct ProgramCodeBreaker : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "CodeBreaker"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::codeBreaker; }
  std::string GetUrl() const noexcept { return "ToolCodeBreaker.htm"; }
};

struct ProgramCodeToHtml : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolCodeToHtml_3_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolCodeToHtml_2_0.png"; }
  std::string GetScreenName() const noexcept { return "CodeToHtml"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::codeToHtml; }
  std::string GetUrl() const noexcept { return "ToolCodeToHtml.htm"; }
};

struct ProgramConnectThree : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameConnectThree_5_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "GameConnectThree_6_0.png"; }
  std::string GetScreenName() const noexcept { return "ConnectThree"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::connectThree; }
  std::string GetUrl() const noexcept { return "GameConnectThree.htm"; }
};

struct ProgramCorridor : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameCorridor.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Corridor"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::corridor; }
  std::string GetUrl() const noexcept { return "GameCorridor.htm"; }
};

struct ProgramCreateGlossary : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolCreateGlossary_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "CreateGlossary"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createGlossary; }
  std::string GetUrl() const noexcept { return "ToolCreateGlossary.htm"; }
};

struct ProgramCreateQtProjectZipFile : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolCreateQtProjectZipFile_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "CreateQtProjectZipFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createQtProjectZipFile; }
  std::string GetUrl() const noexcept { return "ToolCreateQtProjectZipFile.htm"; }
};

struct ProgramCrossPoll : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectCrossPoll3.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "CrossPoll"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::crossPoll; }
  std::string GetUrl() const noexcept { return "ProjectCrossPoll.htm"; }
};

struct ProgramDasWahreSchlagerfest : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return "GameDasWahreSchlagerfest_2_5.png"; }
  std::string GetFilenameDesktop() const noexcept { return "GameDasWahreSchlagerfest_2_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Das Wahre Schlagerfest"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::dasWahreSchlagerfest; }
  std::string GetUrl() const noexcept { return "GameDasWahreSchlagerfest.htm"; }
};

struct ProgramDasWahreSchlagerfestVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameDasWahreSchlagerfest_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Das Wahre Schlagerfest (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::dasWahreSchlagerfestVcl; }
  std::string GetUrl() const noexcept { return "GameDasWahreSchlagerfestVcl.htm"; }
};

struct ProgramDotMatrix : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolDotMatrix_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "DotMatrix"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::dotMatrix; }
  std::string GetUrl() const noexcept { return "ToolDotMatrix.htm"; }
};

struct ProgramDotMatrixVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolDotMatrix_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "DotMatrix (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::dotMatrixVcl; }
  std::string GetUrl() const noexcept { return "ToolDotMatrixVcl.htm"; }
};

struct ProgramEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolEncranger_2_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return "ToolEncranger_2_1.png"; }
  std::string GetScreenName() const noexcept { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::encranger; }
  std::string GetUrl() const noexcept { return "ToolEncranger.htm"; }
};

struct ProgramEverythingToPiecesShooter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "EverythingToPiecesShooter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::everythingToPiecesShooter; }
  std::string GetUrl() const noexcept { return "GameEverythingToPiecesShooter.htm"; }
};

struct ProgramFakeEvy : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "GrayFakeEvy"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::fakeEvy; }
  std::string GetUrl() const noexcept { return "ToolFakeEvy.htm"; }
};

struct ProgramFilterOperationer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolFilterOperationer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "FilterOperationer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::filterOperationer; }
  std::string GetUrl() const noexcept { return "ToolFilterOperationer.htm"; }
};

struct ProgramFilterOperationerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFilterOperationer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "FilterOperationer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::filterOperationerVcl; }
  std::string GetUrl() const noexcept { return "ToolFilterOperationerVcl.htm"; }
};

struct ProgramFryskLeareLieder : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFryskLeareLieder_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "FryskLeareLieder"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::fryskLeareLieder; }
  std::string GetUrl() const noexcept { return "ToolFryskLeareLieder.htm"; }
};

struct ProgramFunctionPlotter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolFunctionPlotter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "FunctionPlotter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::functionPlotter; }
  std::string GetUrl() const noexcept { return "ToolFunctionPlotter.htm"; }
};

struct ProgramFunctionPlotterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFunctionPlotter_1_1.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "FunctionPlotter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::functionPlotterVcl; }
  std::string GetUrl() const noexcept { return "ToolFunctionPlotterVcl.htm"; }
};

struct ProgramGaborFilter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolGaborFilter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "GaborFilter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::gaborFilter; }
  std::string GetUrl() const noexcept { return "ToolGaborFilter.htm"; }
};

struct ProgramGaborFilterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolGaborFilter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "GaborFilter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::gaborFilterVcl; }
  std::string GetUrl() const noexcept { return "ToolGaborFilterVcl.htm"; }
};

struct ProgramGrayCoder : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolGrayCoder_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "GrayCoder"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::grayCoder; }
  std::string GetUrl() const noexcept { return "ToolGrayCoder.htm"; }
};

struct ProgramGrayCoderVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolGrayCoder_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "GrayCoder (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::grayCoderVcl; }
  std::string GetUrl() const noexcept { return "ToolGrayCoderVcl.htm"; }
};

struct ProgramGtst : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ProjectGtst_1_2.png"; }
  std::string GetScreenName() const noexcept { return "GTST"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::gtst; }
  std::string GetUrl() const noexcept { return "ProjectGtst.htm"; }
};

struct ProgramHistogramEqualizationer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolHistogramEqualizationer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "HistogramEqualizationer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept { return ProgramType::histogramEqualizationer; }
  std::string GetUrl() const noexcept { return "ToolHistogramEqualizationer.htm"; }
};

struct ProgramHistogramEqualizationerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolHistogramEqualizationer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "HistogramEqualizationer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::histogramEqualizationerVcl; }
  std::string GetUrl() const noexcept { return "ToolHistogramEqualizationerVcl.htm"; }
};

struct ProgramHometrainer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolHometrainer_2_0.png"; }
  std::string GetScreenName() const noexcept { return "Hometrainer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::hometrainer; }
  std::string GetUrl() const noexcept { return "ToolHometrainer.htm"; }
};

struct ProgramHometrainerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolHometrainer_1_8.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Hometrainer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::hometrainerVcl; }
  std::string GetUrl() const noexcept { return "ToolHometrainerVcl.htm"; }
};

struct ProgramImageRotater : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolImageRotater_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ImageRotater"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept { return ProgramType::imageRotater; }
  std::string GetUrl() const noexcept { return "ToolImageRotater.htm"; }
};


struct ProgramImageRotaterClx : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolImageRotaterClx_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ImageRotater (CLX)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::imageRotaterClx; }
  std::string GetUrl() const noexcept { return "ToolImageRotaterClx.htm"; }
};

struct ProgramImageRotaterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolImageRotaterVcl_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ImageRotater (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::imageRotaterVcl; }
  std::string GetUrl() const noexcept { return "ToolImageRotaterVcl.htm"; }
};

struct ProgramK3OpEenRij : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameK3OpEenRij_6_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "GameK3OpEenRij_5_0.png"; }
  std::string GetScreenName() const noexcept { return "K3 Op Een Rij"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::k3OpEenRij; }
  std::string GetUrl() const noexcept { return "GameK3OpEenRij.htm"; }
};

struct ProgramK3OpEenRijVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameK3OpEenRij_4_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "K3 Op Een Rij (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::k3OpEenRijVcl; }
  std::string GetUrl() const noexcept { return "GameK3OpEenRijVcl.htm"; }
};

struct ProgramKalmanFilterer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolKalmanFilterer_1_15.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "KalmanFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::kalmanFilterer; }
  std::string GetUrl() const noexcept { return "ToolKalmanFilterer.htm"; }
};

struct ProgramKeySender : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolKeySender_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "KeySender"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::keySender; }
  std::string GetUrl() const noexcept { return "ToolKeySender.htm"; }
};

struct ProgramKnokfighter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Knokfighter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::knokfighter; }
  std::string GetUrl() const noexcept { return "GameKnokfighter.htm"; }
};

struct ProgramKnokfighterVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameKnokfighter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Knokfighter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::knokfighterVcl; }
  std::string GetUrl() const noexcept { return "GameKnokfighterVcl.htm"; }
};


struct ProgramKTouchLectureCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "KTouchLectureCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::kTouchLectureCreator; }
  std::string GetUrl() const noexcept { return "ToolKTouchLectureCreator.htm"; }
};

struct ProgramLambdaBot : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "LambdaBot"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::lambdaBot; }
  std::string GetUrl() const noexcept { return "ToolLambdaBot.htm"; }
};

struct ProgramLearyCircumplex : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolLearyCircumplex_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "LearyCircumplex"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::learyCircumplex; }
  std::string GetUrl() const noexcept { return "ToolLearyCircumplex.htm"; }
};

struct ProgramLogisticGrowthSimulator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolLogisticGrowthSimulator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "LogisticGrowthSimulator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::logisticGrowthSimulator; }
  std::string GetUrl() const noexcept { return "ToolLogisticGrowthSimulator.htm"; }
};

struct ProgramLoose : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolLoose_2_0.png"; }
  std::string GetScreenName() const noexcept { return "Loose"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::loose; }
  std::string GetUrl() const noexcept { return "ToolLoose.htm"; }
};

struct ProgramMartianCafeTuinemaTycoon : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMartianCafeTuinemaTycoon_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MartianCafeTuinemaTycoon"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::martianCafeTuinemaTycoon; }
  std::string GetUrl() const noexcept { return "GameMartianCafeTuinemaTycoon.htm"; }
};

struct ProgramMazeCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolMazeCreator_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MazeCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::mazeCreator; }
  std::string GetUrl() const noexcept { return "ToolMazeCreator.htm"; }
};

struct ProgramMazeCreatorVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMazeCreator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MazeCreator (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::mazeCreatorVcl; }
  std::string GetUrl() const noexcept { return "ToolMazeCreatorVcl.htm"; }
};

struct ProgramMaziak : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameMaziak_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Maziak"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::maziak; }
  std::string GetUrl() const noexcept { return "GameMaziak.htm"; }
};

struct ProgramMaziakVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMaziak_2_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Maziak (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::maziakVcl; }
  std::string GetUrl() const noexcept { return "GameMaziakVcl.htm"; }
};

struct ProgramMetZnDrieen : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MetZnDrieen"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::metZnDrieen; }
  std::string GetUrl() const noexcept { return "GameMetZnDrieen.htm"; }
};

struct ProgramMetZnDrieenVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMetZnDrieen_1_3.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MetZnDrieen (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::metZnDrieenVcl; }
  std::string GetUrl() const noexcept { return "GameMetZnDrieenVcl.htm"; }
};

struct ProgramMidiLessonCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MidiLessonCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::midiLessonCreator; }
  std::string GetUrl() const noexcept { return "ToolMidiLessonCreator.htm"; }
};

struct ProgramMorpher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMorpher_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Morpher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::morpher; }
  std::string GetUrl() const noexcept { return "ToolMorpher.htm"; }
};

struct ProgramMultiEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolMultiEncranger_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MultiEncranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::multiEncranger; }
  std::string GetUrl() const noexcept { return "ToolMultiEncranger.htm"; }
};

struct ProgramMultiEncrangerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMultiEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MultiEncranger (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::multiEncrangerVcl; }
  std::string GetUrl() const noexcept { return "ToolMultiEncrangerVcl.htm"; }
};

struct ProgramMuscaDomestica : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectMuscaDomestica_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Project Musca Domestica"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::muscaDomestica; }
  std::string GetUrl() const noexcept { return "ProjectMuscaDomestica.htm"; }
};

struct ProgramMusicTheory : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolMusicTheory_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "MusicTheory"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::musicTheory; }
  std::string GetUrl() const noexcept { return "ToolMusicTheory.htm"; }
};

struct ProgramNdsmake : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Ndsmake"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ndsmake; }
  std::string GetUrl() const noexcept { return "ToolNdsmake.htm"; }
};

struct ProgramNdsPaint : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "NdsPaint"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ndsPaint; }
  std::string GetUrl() const noexcept { return "ToolNdsPaint.htm"; }
};

struct ProgramPaperRockScissors : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PaperRockScissors"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::paperRockScissors; }
  std::string GetUrl() const noexcept { return "ToolPaperRockScissors.htm"; }
};

struct ProgramPaperRockScissorsVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolPaperRockScissors_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PaperRockScissors (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::paperRockScissorsVcl; }
  std::string GetUrl() const noexcept { return "ToolPaperRockScissorsVcl.htm"; }
};

struct ProgramPause : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Pause"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pause; }
  std::string GetUrl() const noexcept { return "ToolPause.htm"; }
};

struct ProgramPerfectElasticCollision : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolPerfectElasticCollision_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PerfectElasticCollision"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::perfectElasticCollision; }
  std::string GetUrl() const noexcept { return "ToolPerfectElasticCollision.htm"; }
};

struct ProgramPicToCode : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolPicToCode_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolPicToCode_1_3.png"; }
  std::string GetScreenName() const noexcept { return "PicToCode"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::picToCode; }
  std::string GetUrl() const noexcept { return "ToolPicToCode.htm"; }
};

struct ProgramPixelator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Pixelator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pixelator; }
  std::string GetUrl() const noexcept { return "ToolPixelator.htm"; }
};

struct ProgramPixelatorVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolPixelator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Pixelator (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::pixelatorVcl; }
  std::string GetUrl() const noexcept { return "ToolPixelatorVcl.htm"; }
};

struct ProgramPokeVolley : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GamePokeVolley_2_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PokeVolley"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pokeVolley; }
  std::string GetUrl() const noexcept { return "GamePokeVolley.htm"; }
};

struct ProgramPong : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Pong"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pong; }
  std::string GetUrl() const noexcept { return "GamePong.htm"; }
};

struct ProgramPreDickAdvocaTor : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolPreDickAdvocaTor_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PreDickAdvocaTor"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::preDickAdvocaTor; }
  std::string GetUrl() const noexcept { return "ToolPreDickAdvocaTor.htm"; }
};

struct ProgramPrimeExpert : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolPrimeExpert_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolTestPrimeExpert_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "PrimeExpert"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::primeExpert; }
  std::string GetUrl() const noexcept { return "ToolPrimeExpert.htm"; }
};

struct ProgramProjectRichelBilderbeek : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ProjectRichelBilderbeek_1_14.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ProjectRichelBilderbeek"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::projectRichelBilderbeek; }
  std::string GetUrl() const noexcept { return "ProjectRichelBilderbeek.htm"; }
};


struct ProgramPylos : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GamePylos_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Pylos"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::pylos; }
  std::string GetUrl() const noexcept { return "GamePylos.htm"; }
};

struct ProgramQmakeWatcher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolQmakeWatcher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "QmakeWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::qmakeWatcher; }
  std::string GetUrl() const noexcept { return "ToolQmakeWatcher.htm"; }
};

struct ProgramQuadraticSolver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return "ToolQuadraticSolver_1_0.png"; }
  std::string GetFilenameDesktop() const noexcept { return "ToolQuadraticSolver_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "QuadraticSolver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::quadraticSolver; }
  std::string GetUrl() const noexcept { return "ToolQuadraticSolver.htm"; }
};

struct ProgramRampalEtienne : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ProjectRampalEtienne"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::rampalEtienne; }
  std::string GetUrl() const noexcept { return "ProjectRampalEtienne.htm"; }
};

struct ProgramRandomCode : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolRandomCode_4_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolRandomCode_3_0.png"; }
  std::string GetScreenName() const noexcept { return "RandomCode"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::randomCode; }
  std::string GetUrl() const noexcept { return "ToolRandomCode.htm"; }
};

struct ProgramRandomCodeVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolRandomCode_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "RandomCode (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::randomCodeVcl; }
  std::string GetUrl() const noexcept { return "ToolRandomCodeVcl.htm"; }
};

struct ProgramRasper : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolRasper_0_3.png"; }
  std::string GetScreenName() const noexcept { return "Rasper"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::rasper; }
  std::string GetUrl() const noexcept { return "ToolRasper.htm"; }
};

struct ProgramRefrigeratorPuzzleSolver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolRefrigeratorPuzzleSolver_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "RefrigeratorPuzzleSolver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::refrigeratorPuzzleSolver; }
  std::string GetUrl() const noexcept { return "ToolRefrigeratorPuzzleSolver.htm"; }
};

struct ProgramRegexTester : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolRegexTester_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "RegexTester"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::regexTester; }
  std::string GetUrl() const noexcept { return "ToolRegexTester.htm"; }
};

struct ProgramReversi : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameReversi_0_1.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Reversi"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::reversi; }
  std::string GetUrl() const noexcept { return "GameReversi.htm"; }
};

struct ProgramReversiVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameReversiVcl_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Reversi VCL"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::reversiVcl; }
  std::string GetUrl() const noexcept { return "GameReversiVcl.htm"; }
};


struct ProgramRichelBilderbeekGallery : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolRichelBilderbeekGallery_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "RichelBilderbeekGallery"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::richelBilderbeekGallery; }
  std::string GetUrl() const noexcept { return "ToolRichelBilderbeekGallery.htm"; }
};

struct ProgramRichelBilderbeekNlSitemapGenerator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "RichelBilderbeekNlSitemapGenerator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::richelbilderbeekNlSitemapGenerator; }
  std::string GetUrl() const noexcept { return "ToolRichelbilderbeekNlSitemapGenerator.htm"; }
};

struct ProgramRubiksClock : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameRubiksClock_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "GameRubiksClock_2_1.png"; }
  std::string GetScreenName() const noexcept { return "Rubik's Clock"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::rubiksClock; }
  std::string GetUrl() const noexcept { return "GameRubiksClock.htm"; }
};

struct ProgramRubiksClockVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameRubiksClock_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Rubik's Clock (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::rubiksClockVcl; }
  std::string GetUrl() const noexcept { return "GameRubiksClockVcl.htm"; }
};

struct ProgramSearchAndDestroyChess : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Search And Destroy Chess"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::searchAndDestroyChess; }
  std::string GetUrl() const noexcept { return "GameSearchAndDestroyChess.htm"; }
};

struct ProgramSearchAndDestroyChessVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return "GameSearchAndDestroyChessConsole_1_0.png"; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSearchAndDestroyChess_2_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Search And Destroy Chess (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::searchAndDestroyChessVcl; }
  std::string GetUrl() const noexcept { return "GameSearchAndDestroyChessVcl.htm"; }
};

struct ProgramSecretMessage : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolSecretMessage_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SecretMessage"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::secretMessage; }
  std::string GetUrl() const noexcept { return "ToolSecretMessage.htm"; }
};

struct ProgramSecretMessageVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSecretMessage_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SecretMessage (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::secretMessageVcl; }
  std::string GetUrl() const noexcept { return "ToolSecretMessageVcl.htm"; }
};

struct ProgramSimBrainiac : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimBrainiac_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SimBrainiac"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simBrainiac; }
  std::string GetUrl() const noexcept { return "ToolSimBrainiac.htm"; }
};

struct ProgramSimImmuneResponse : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimImmuneResponse_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SimImmuneResponse"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simImmuneResponse; }
  std::string GetUrl() const noexcept { return "ToolSimImmuneResponse.htm"; }
};

struct ProgramSimMysteryMachine : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolSimMysteryMachine_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolSimMysteryMachine_1_1_web.png"; }
  std::string GetScreenName() const noexcept { return "SimMysteryMachine"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::simMysteryMachine; }
  std::string GetUrl() const noexcept { return "ToolSimMysteryMachine.htm"; }
};

struct ProgramSimplifyNewick : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolSimplifyNewick_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SimplifyNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simplifyNewick; }
  std::string GetUrl() const noexcept { return "ToolSimplifyNewick.htm"; }
};

struct ProgramSimPredator : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSimPredator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SimPredator"; }

  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simPredator; }
  std::string GetUrl() const noexcept { return "GameSimPredator.htm"; }
};

struct ProgramSimStagecraft : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimStagecraft_1_1.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SimStagecraft"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simStagecraft; }
  std::string GetUrl() const noexcept { return "ToolSimStagecraft.htm"; }
};

struct ProgramSoaSim : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSoaSim_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SoaSim"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::soaSim; }
  std::string GetUrl() const noexcept { return "ToolSoaSim.htm"; }
};

struct ProgramSolvePuzzleX : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SolvePuzzleX"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::solvePuzzleX; }
  std::string GetUrl() const noexcept { return "ToolSolvePuzzleX.htm"; }
};

struct ProgramSpaceHarry : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Space Harry"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::spaceHarry; }
  std::string GetUrl() const noexcept { return "GameSpaceHarry.htm"; }
};

struct ProgramSpaceHarryVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSpaceHarry_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Space Harry (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::spaceHarryVcl; }
  std::string GetUrl() const noexcept { return "GameSpaceHarryVcl.htm"; }
};

struct ProgramStaircaseCardCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "StaircaseCardCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::staircaseCardCreator; }
  std::string GetUrl() const noexcept { return "ToolStaircaseCardCreator.htm"; }
};

struct ProgramStateObserver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolStateObserver_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "StateObserver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::stateObserver; }
  std::string GetUrl() const noexcept { return "ToolStateObserver.htm"; }
};

struct ProgramStyleSheetSetter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "StyleSheetSetter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::styleSheetSetter; }
  std::string GetUrl() const noexcept { return "ToolStyleSheetSetter.htm"; }
};

struct ProgramSuperNsanaBros : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Super Nsana Bros"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::superNsanaBros; }
  std::string GetUrl() const noexcept { return "GameSuperNsanaBros.htm"; }
};

struct ProgramSurfacePlotter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolSurfacePlotter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SurfacePlotter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::surfacePlotter; }
  std::string GetUrl() const noexcept { return "ToolSurfacePlotter.htm"; }
};

struct ProgramSurfacePlotterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSurfacePlotter_1_2.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "SurfacePlotter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::surfacePlotterVcl; }
  std::string GetUrl() const noexcept { return "ToolSurfacePlotterVcl.htm"; }
};

struct ProgramTankBattalion : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TankBattalion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::tankBattalion; }
  std::string GetUrl() const noexcept { return "GameTankBattalion.htm"; }
};

struct ProgramTestAbout : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestAbout_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestAbout"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testAbout; }
  std::string GetUrl() const noexcept { return "ToolTestAbout.htm"; }
};

struct ProgramTestApproximator : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestApproximator_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testApproximator; }
  std::string GetUrl() const noexcept { return "ToolTestApproximator.htm"; }
};

struct ProgramTestBinaryNewickVector : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestBinaryNewickVector_1_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestBinaryNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBinaryNewickVector; }
  std::string GetUrl() const noexcept { return "ToolTestBinaryNewickVector.htm"; }
};

struct ProgramTestBouncingBallsWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestBouncingBallsWidget_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestBouncingBallsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBouncingBallsWidget; }
  std::string GetUrl() const noexcept { return "ToolTestBouncingBallsWidget.htm"; }
};

struct ProgramTestBouncingRectsWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestBouncingRectsWidget_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestBouncingRectsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBouncingRectsWidget; }
  std::string GetUrl() const noexcept { return "ToolTestBouncingRectsWidget.htm"; }
};

struct ProgramTestBroadcastServer : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestBroadcastServer_1_0.png"; }
  std::string GetScreenName() const noexcept { return "TestBroadcastServer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testBroadcastServer; }
  std::string GetUrl() const noexcept { return "ToolTestBroadcastServer.htm"; }
};


struct ProgramTestChess : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestChess20120209.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestChess20120207.png"; }
  std::string GetScreenName() const noexcept { return "TestChess"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::testChess; }
  std::string GetUrl() const noexcept { return "ToolTestChess.htm"; }
};

struct ProgramTestConceptMap : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestConceptMap_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestConceptMap"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept { return ProgramType::testConceptMap; }
  std::string GetUrl() const noexcept { return "ToolTestConceptMap.htm"; }
};

struct ProgramTestDial : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestDial_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestDial_1_1.png"; }
  std::string GetScreenName() const noexcept { return "TestDial"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testDial; }
  std::string GetUrl() const noexcept { return "ToolTestDial.htm"; }
};

struct ProgramTestDrawCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestDrawCanvas_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestDrawCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testDrawCanvas; }
  std::string GetUrl() const noexcept { return "ToolTestDrawCanvas.htm"; }
};

struct ProgramTestEntrance : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestEntrance_1_0.png"; }
  std::string GetScreenName() const noexcept { return "TestEntrance"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testEntrance; }
  std::string GetUrl() const noexcept { return "ToolTestEntrance.htm"; }
};

struct ProgramTestExercise : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestExercise_1_0.png"; }
  std::string GetScreenName() const noexcept { return "TestExercise"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testExercise; }
  std::string GetUrl() const noexcept { return "ToolTestExercise.htm"; }
};

struct ProgramTestFunctionParser : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestFunctionParser_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolTestFunctionParser_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestFunctionParser_2_1.png"; }
  std::string GetScreenName() const noexcept { return "TestFunctionParser"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testFunctionParser; }
  std::string GetUrl() const noexcept { return "ToolTestFunctionParser.htm"; }
};

struct ProgramTestGnuplotInterface : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestGnuplotInterface"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGnuplotInterface; }
  std::string GetUrl() const noexcept { return "ToolTestGnuplotInterface.htm"; }
};

struct ProgramTestGraphicsProxyWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestGraphicsProxyWidget_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestGraphicsProxyWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGraphicsProxyWidget; }
  std::string GetUrl() const noexcept { return "ToolTestGraphicsProxyWidget.htm"; }
};

struct ProgramTestGravityWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestGravityWidget_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestGravityWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGravityWidget; }
  std::string GetUrl() const noexcept { return "ToolTestGravityWidget.htm"; }
};

struct ProgramTestGroupWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestGroupWidget_1_0.png"; }
  std::string GetScreenName() const noexcept { return "TestGroupWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testGroupWidget; }
  std::string GetUrl() const noexcept { return "ToolTestGroupWidget.htm"; }
};

struct ProgramTestHugeVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestHugeVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testHugeVector; }
  std::string GetUrl() const noexcept { return "ToolTestHugeVector.htm"; }
};

struct ProgramTestImageCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestImageCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestImageCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testImageCanvas; }
  std::string GetUrl() const noexcept { return "ToolTestImageCanvas.htm"; }
};

struct ProgramTestLazy_init : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestLazy_init"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testLazy_init; }
  std::string GetUrl() const noexcept { return "ToolTestLazy_init.htm"; }
};

struct ProgramTestLed : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestLed_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestLed_1_1.png"; }
  std::string GetScreenName() const noexcept { return "TestLed"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testLed; }
  std::string GetUrl() const noexcept { return "ToolTestLed.htm"; }
};

struct ProgramTestManyDigitNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestManyDigitNewick_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestManyDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testManyDigitNewick; }
  std::string GetUrl() const noexcept { return "ToolTestManyDigitNewick.htm"; }
};

struct ProgramTestMultiApproximator : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestMultiApproximator_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestMultiApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultiApproximator; }
  std::string GetUrl() const noexcept { return "ToolTestMultiApproximator.htm"; }
};

struct ProgramTestMultiCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestMultiCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestMultiCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultiCanvas; }
  std::string GetUrl() const noexcept { return "ToolTestMultiCanvas.htm"; }
};

struct ProgramTestMultipleChoiceQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestMultipleChoiceQuestionDialog_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestMultipleChoiceQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultipleChoiceQuestion; }
  std::string GetUrl() const noexcept { return "ToolTestMultipleChoiceQuestion.htm"; }
};

struct ProgramTestMultiVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestMultiVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultiVector; }
  std::string GetUrl() const noexcept { return "ToolTestMultiVector.htm"; }
};

struct ProgramTestPlane : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestPlane_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestPlane"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPlane; }
  std::string GetUrl() const noexcept { return "ToolTestPlane.htm"; }
};

struct ProgramTestNdsmake : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestNdsmake_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestNdsmake"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNdsmake; }
  std::string GetUrl() const noexcept { return "ToolTestNdsmake.htm"; }
};

struct ProgramTestNeuralNet : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestNeuralNet_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestNeuralNet"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNeuralNet; }
  std::string GetUrl() const noexcept { return "ToolTestNeuralNet.htm"; }
};

struct ProgramTestNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNewick; }
  std::string GetUrl() const noexcept { return "ToolTestNewick.htm"; }
};

struct ProgramTestNewickVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestNewickVector_3_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNewickVector; }
  std::string GetUrl() const noexcept { return "ToolTestNewickVector.htm"; }
};

struct ProgramTestOpenQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestOpenQuestion_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestOpenQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testOpenQuestion; }
  std::string GetUrl() const noexcept { return "ToolTestOpenQuestion.htm"; }
};

struct ProgramTestPolyFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestPolyFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPolyFile; }
  std::string GetUrl() const noexcept { return "ToolTestPolyFile.htm"; }
};

struct ProgramTestPolyFileFromPolygons : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestPolyFileFromPolygons"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPolyFileFromPolygons; }
  std::string GetUrl() const noexcept { return "ToolTestPolyFileFromPolygons.htm"; }
};

struct ProgramTestPylos : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestPylos_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestPylos"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPylos; }
  std::string GetUrl() const noexcept { return "ToolTestPylos.htm"; }
};

struct ProgramTestQrcFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQrcFile_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQrcFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQrcFile; }
  std::string GetUrl() const noexcept { return "ToolTestQrcFile.htm"; }
};

struct ProgramTestQtArrowItems : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtArrowItems_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtArrowItems"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtArrowItems; }
  std::string GetUrl() const noexcept { return "ToolTestQtArrowItems.htm"; }
};

struct ProgramTestQtCreatorProFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtCreatorProFile_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtCreatorProFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtCreatorProFile; }
  std::string GetUrl() const noexcept { return "ToolTestQtCreatorProFile.htm"; }
};

struct ProgramTestQtHideAndShowDialog : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtHideAndShowDialog_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtHideAndShowDialog"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtHideAndShowDialog; }
  std::string GetUrl() const noexcept { return "ToolTestQtHideAndShowDialog.htm"; }
};

struct ProgramTestQtKeyboardFriendlyGraphicsView : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestKeyboardFriendlyGraphicsView_0_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtKeyboardFriendlyGraphicsView"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtKeyboardFriendlyGraphicsView; }
  std::string GetUrl() const noexcept { return "ToolTestQtKeyboardFriendlyGraphicsView.htm"; }
};

struct ProgramTestQtModels : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtModels_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtModels"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtModels; }
  std::string GetUrl() const noexcept { return "ToolTestQtModels.htm"; }
};

struct ProgramTestQtOcrWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtOcrWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtOcrWidget; }
  std::string GetUrl() const noexcept { return "ToolTestQtOcrWidget.htm"; }
};

struct ProgramTestQtRoundedEditRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedEditRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtRoundedEditRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedEditRectItem; }
  std::string GetUrl() const noexcept { return "ToolTestQtRoundedEditRectItem.htm"; }
};

struct ProgramTestQtRoundedRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtRoundedRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedRectItem; }
  std::string GetUrl() const noexcept { return "ToolTestQtRoundedRectItem.htm"; }
};

struct ProgramTestQtRoundedTextRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedTextRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQtRoundedTextRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedTextRectItem; }
  std::string GetUrl() const noexcept { return "ToolTestQtRoundedTextRectItem.htm"; }
};

struct ProgramTestQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestQuestion_3_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testQuestion; }
  std::string GetUrl() const noexcept { return "ToolTestQuestion.htm"; }
};

struct ProgramTestReversi : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestReversi_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestReversi"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testReversi; }
  std::string GetUrl() const noexcept { return "ToolTestReversi.htm"; }
};

struct ProgramTestSelectFileDialog : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestSelectFileDialog_1_1.png"; }
  std::string GetScreenName() const noexcept { return "TestSelectFileDialog"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testSelectFileDialog; }
  std::string GetUrl() const noexcept { return "ToolTestSelectFileDialog.htm"; }
};

struct ProgramTestServerPusher : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testServerPusher; }
  std::string GetUrl() const noexcept { return "ToolTestServerPusher.htm"; }
};

struct ProgramTestShape : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestShape_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestShape_1_0_web.png"; }
  std::string GetScreenName() const noexcept { return "TestShape"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testShape; }
  std::string GetUrl() const noexcept { return "ToolTestShape.htm"; }
};

struct ProgramTestShinyButton : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestShinyButton_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestShinyButton_2_0_web.png"; }
  std::string GetScreenName() const noexcept { return "TestShinyButton"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testShinyButton; }
  std::string GetUrl() const noexcept { return "ToolTestShinyButton.htm"; }
};

struct ProgramTestSimpleLinearRegression : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestSimpleLinearRegression_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestSimpleLinearRegression"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testSimpleLinearRegression; }
  std::string GetUrl() const noexcept { return "ToolTestSimpleLinearRegression.htm"; }
};

struct ProgramTestStopwatch : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestStopwatch"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testStopwatch; }
  std::string GetUrl() const noexcept { return "ToolTestStopwatch.htm"; }
};

struct ProgramTestTextCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestTextCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestTextCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTextCanvas; }
  std::string GetUrl() const noexcept { return "ToolTestTextCanvas.htm"; }
};

struct ProgramTestTextPositionWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestTextPositionWidget_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestTextPositionWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTextPositionWidget; }
  std::string GetUrl() const noexcept { return "ToolTestTextPositionWidget.htm"; }
};

struct ProgramTestTicTacToe : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestTicTacToe_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTestTicTacToe_1_2.png"; }
  std::string GetScreenName() const noexcept { return "TestTicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testTicTacToe; }
  std::string GetUrl() const noexcept { return "ToolTestTicTacToe.htm"; }
};

struct ProgramTestTimedServerPusher : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestTimedServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testTimedServerPusher; }
  std::string GetUrl() const noexcept { return "ToolTestTimedServerPusher.htm"; }
};

struct ProgramTestToggleButton : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestToggleButton_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestToggleButton"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testToggleButton; }
  std::string GetUrl() const noexcept { return "ToolTestToggleButton.htm"; }
};

struct ProgramTestTriangle : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestTriangle_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestTriangle"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTriangle; }
  std::string GetUrl() const noexcept { return "ToolTestTriangle.htm"; }
};


struct ProgramTestTwoDigitNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTestTwoDigitNewick_2_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TestTwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTwoDigitNewick; }
  std::string GetUrl() const noexcept { return "ToolTestTwoDigitNewick.htm"; }
};

struct ProgramThorVeen : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectThorVeen_0_9.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Project ThorVeen"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::thorVeen; }
  std::string GetUrl() const noexcept { return "ProjectThorVeen.htm"; }
};

struct ProgramThresholdFilterer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolThresholdFilterer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ThresholdFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::thresholdFilterer; }
  std::string GetUrl() const noexcept { return "ToolThresholdFilterer.htm"; }
};

struct ProgramThresholdFiltererVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolThresholdFilterer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ThresholdFilterer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::thresholdFiltererVcl; }
  std::string GetUrl() const noexcept { return "ToolThresholdFiltererVcl.htm"; }
};

struct ProgramTicTacToe : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return "GameTicTacToe_1_6.png"; }
  std::string GetFilenameDesktop() const noexcept { return "GameTicTacToe_1_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "GameTicTacToe_1_4.png"; }
  std::string GetScreenName() const noexcept { return "TicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToe; }
  std::string GetUrl() const noexcept { return "GameTicTacToe.htm"; }
};

struct ProgramTicTacToeLearner : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTicTacToeLearner_0_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TicTacToeLearner"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToeLearner; }
  std::string GetUrl() const noexcept { return "ToolTicTacToeLearner.htm"; }
};

struct ProgramTicTacToeValuer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTicTacToeValuer_0_7.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TicTacToeValuer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToeValuer; }
  std::string GetUrl() const noexcept { return "ToolTicTacToeValuer.htm"; }
};

struct ProgramTimePoll : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return "ToolTimePoll_4_1.png"; }
  std::string GetScreenName() const noexcept { return "TimePoll"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::timePoll; }
  std::string GetUrl() const noexcept { return "ToolTimePoll.htm"; }
};

struct ProgramTriangleMeshCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolTriangleMeshCreator_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TriangleMeshCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::triangleMeshCreator; }
  std::string GetUrl() const noexcept { return "ToolTriangleMeshCreator.htm"; }
};

struct ProgramTronCollection : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TronCollection"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::tronCollection; }
  std::string GetUrl() const noexcept { return "GameTronCollection.htm"; }
};

struct ProgramTronCollectionVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "TronCollection (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept { return ProgramType::tronCollectionVcl; }
  std::string GetUrl() const noexcept { return "GameTronCollectionVcl.htm"; }
};

struct ProgramUbuntuOneWatcher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolUbuntuOneWatcher_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "UbuntuOneWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ubuntuOneWatcher; }
  std::string GetUrl() const noexcept { return "ToolUbuntuOneWatcher.htm"; }
};


struct ProgramValentineCardDecrypter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolValentineCardDecrypter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "ValentineCardDecrypter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::valentineCardDecrypter; }
  std::string GetUrl() const noexcept { return "ToolValentineCardDecrypter.htm"; }
};


struct ProgramVanDenBogaart : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "VanDenBogaart"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::vanDenBogaart; }
  std::string GetUrl() const noexcept { return "ProjectVanDenBogaart.htm"; }
};

struct ProgramVigenereCipher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolVigenereCipher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "VigenereCipher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::vigenereCipher; }
  std::string GetUrl() const noexcept { return "ToolVigenereCipher.htm"; }
};

struct ProgramVirtualBastard : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "VirtualBastard"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::virtualBastard; }
  std::string GetUrl() const noexcept { return "ToolVirtualBastard.htm"; }
};

struct ProgramVisualAbc : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolVisualAbc_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "VisualAbc"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::visualAbc; }
  std::string GetUrl() const noexcept { return "ToolVisualAbc.htm"; }
};

struct ProgramWktToSvg : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "ToolWktToSvg_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "WktToSvg"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::wktToSvg; }
  std::string GetUrl() const noexcept { return "ToolWktToSvg.htm"; }
};

struct ProgramXeNonZero : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return "GameXeNonZero_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "XeNonZero"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::xeNonZero; }
  std::string GetUrl() const noexcept { return "GameXeNonZero.htm"; }
};

struct ProgramZork : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept { return "GameZork.png"; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetScreenName() const noexcept { return "Zork"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::zork; }
  std::string GetUrl() const noexcept { return "GameZork.htm"; }
};

/*
struct ProgramNewickVector : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetName() const { return "NewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::newickVector; }
  std::string GetUrl() const noexcept { return "ProjectNewickVector.htm"; }
};


struct ProgramTwoDigitNewick : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetName() const { return "TwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::twoDigitNewick; }
  std::string GetUrl() const noexcept { return "ProjectTwoDigitNewick.htm"; }
};






struct ProgramCreateSitemap : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetName() const { return "CreateSitemap"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createSitemap; }
  std::string GetUrl() const noexcept { return "ToolCreateSitemap.htm"; }
};


struct ProgramEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept { return ""; }
  std::string GetFilenameDesktop() const noexcept { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept { return ""; }
  std::string GetName() const { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::encranger; }
  std::string GetUrl() const noexcept { return "ToolEncranger.htm"; }
};

*/

std::ostream& operator<<(std::ostream& os, const Program& p) noexcept;
bool operator<(const Program& lhs, const Program& rhs) noexcept;

} //~namespace ribi

#endif // RIBI_RICHELBILDERBEEKPROGRAM_H
