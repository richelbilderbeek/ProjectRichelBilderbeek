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
  virtual std::string GetScreenName() const noexcept;

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
  std::string GetTypeName() const noexcept override { return "class"; }
};

struct ProgramGame : public Program
{
  virtual ~ProgramGame() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept override { return "game"; }
};

struct ProgramProject : public Program
{
  virtual ~ProgramProject() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept override { return "project"; }
};

struct ProgramTool : public Program
{
  virtual ~ProgramTool() noexcept {}

  ///The type of program its name, e.g. 'game'
  std::string GetTypeName() const noexcept override { return "tool"; }
};

struct ProgramAthleticLandVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameAthleticLand_0_9.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Athletic Land (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::athleticLandVcl; }
  std::string GetUrl() const noexcept override final { return "GameAthleticLandVcl.htm"; }
};

struct ProgramAsciiArter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolAsciiArter_6_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolAsciiArter_5_2.png"; }
  std::string GetScreenName() const noexcept override final { return "AsciiArter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::asciiArter; }
  std::string GetUrl() const noexcept override final { return "ToolAsciiArter.htm"; }
};

struct ProgramAsciiArterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolAsciiArter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "AsciiArter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::asciiArterVcl; }
  std::string GetUrl() const noexcept override final { return "ToolAsciiArterVcl.htm"; }
};

struct ProgramBarbaImage : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolBarbaImage_1_3.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "BarbaImage"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::barbaImage; }
  std::string GetUrl() const noexcept override final { return "ToolBarbaImage.htm"; }
};

struct ProgramBeerWanter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameBeerWanter5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "BeerWanter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::beerWanter; }
  std::string GetUrl() const noexcept override final { return "GameBeerWanter.htm"; }
};

struct ProgramBeerWanterVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameBeerWanter3.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "BeerWanter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::beerWanterVcl; }
  std::string GetUrl() const noexcept override final { return "GameBeerWanterVcl.htm"; }
};

struct ProgramBochum : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ProjectBochumGaborFiltersResults.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Project Bochum"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::bochum; }
  std::string GetUrl() const noexcept override final { return "ProjectBochum.htm"; }
};

struct ProgramBoenken : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameBoenken_4_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Boenken"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::boenken; }
  std::string GetUrl() const noexcept override final { return "GameBoenken.htm"; }
};

struct ProgramBoenkenVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameBoenken_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Boenken (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::boenkenVcl; }
  std::string GetUrl() const noexcept override final { return "GameBoenkenVcl.htm"; }
};

struct ProgramBrainweaver : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Brainweaver"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::brainweaver; }
  std::string GetUrl() const noexcept override final { return "ProjectBrainweaver.htm"; }
};

struct ProgramBristol : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ProjectBristol_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Bristol"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::bristol; }
  std::string GetUrl() const noexcept override final { return "ProjectBristol.htm"; }
};

struct ProgramCaesarCipher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolCaesarCipher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "CaesarCipher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::caesarCipher; }
  std::string GetUrl() const noexcept override final { return "ToolCaesarCipher.htm"; }
};

struct ProgramChrisWiley : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ProjectChrisWiley_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Project Chris Wiley"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::chrisWiley; }
  std::string GetUrl() const noexcept override final { return "ProjectChrisWiley.htm"; }
};

struct ProgramCodeBreaker : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "CodeBreaker"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::codeBreaker; }
  std::string GetUrl() const noexcept override final { return "ToolCodeBreaker.htm"; }
};

struct ProgramCodeToHtml : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolCodeToHtml_3_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolCodeToHtml_2_0.png"; }
  std::string GetScreenName() const noexcept override final { return "CodeToHtml"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::codeToHtml; }
  std::string GetUrl() const noexcept override final { return "ToolCodeToHtml.htm"; }
};

struct ProgramConnectThree : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameConnectThree_5_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "GameConnectThree_6_0.png"; }
  std::string GetScreenName() const noexcept override final { return "ConnectThree"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::connectThree; }
  std::string GetUrl() const noexcept override final { return "GameConnectThree.htm"; }
};

struct ProgramCorridor : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameCorridor.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Corridor"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::corridor; }
  std::string GetUrl() const noexcept override final { return "GameCorridor.htm"; }
};

struct ProgramCreateGlossary : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolCreateGlossary_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "CreateGlossary"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::createGlossary; }
  std::string GetUrl() const noexcept override final { return "ToolCreateGlossary.htm"; }
};

struct ProgramCreateQtProjectZipFile : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolCreateQtProjectZipFile_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "CreateQtProjectZipFile"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::createQtProjectZipFile; }
  std::string GetUrl() const noexcept override final { return "ToolCreateQtProjectZipFile.htm"; }
};

struct ProgramCrossPoll : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ProjectCrossPoll3.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "CrossPoll"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::crossPoll; }
  std::string GetUrl() const noexcept override final { return "ProjectCrossPoll.htm"; }
};

struct ProgramDasWahreSchlagerfest : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return "GameDasWahreSchlagerfest_2_5.png"; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameDasWahreSchlagerfest_2_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Das Wahre Schlagerfest"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::dasWahreSchlagerfest; }
  std::string GetUrl() const noexcept override final { return "GameDasWahreSchlagerfest.htm"; }
};

struct ProgramDasWahreSchlagerfestVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameDasWahreSchlagerfest_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Das Wahre Schlagerfest (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::dasWahreSchlagerfestVcl; }
  std::string GetUrl() const noexcept override final { return "GameDasWahreSchlagerfestVcl.htm"; }
};

struct ProgramDotMatrix : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolDotMatrix_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "DotMatrix"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::dotMatrix; }
  std::string GetUrl() const noexcept override final { return "ToolDotMatrix.htm"; }
};

struct ProgramDotMatrixVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolDotMatrix_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "DotMatrix (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::dotMatrixVcl; }
  std::string GetUrl() const noexcept override final { return "ToolDotMatrixVcl.htm"; }
};

struct ProgramEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolEncranger_2_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolEncranger_2_1.png"; }
  std::string GetScreenName() const noexcept override final { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::encranger; }
  std::string GetUrl() const noexcept override final { return "ToolEncranger.htm"; }
};

struct ProgramEverythingToPiecesShooter : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "EverythingToPiecesShooter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::everythingToPiecesShooter; }
  std::string GetUrl() const noexcept override final { return "GameEverythingToPiecesShooter.htm"; }
};

struct ProgramFilterOperationer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolFilterOperationer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "FilterOperationer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::filterOperationer; }
  std::string GetUrl() const noexcept override final { return "ToolFilterOperationer.htm"; }
};

struct ProgramFilterOperationerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolFilterOperationer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "FilterOperationer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::filterOperationerVcl; }
  std::string GetUrl() const noexcept override final { return "ToolFilterOperationerVcl.htm"; }
};

struct ProgramFryskLeareLieder : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolFryskLeareLieder_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "FryskLeareLieder"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::fryskLeareLieder; }
  std::string GetUrl() const noexcept override final { return "ToolFryskLeareLieder.htm"; }
};

struct ProgramFunctionPlotter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolFunctionPlotter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "FunctionPlotter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::functionPlotter; }
  std::string GetUrl() const noexcept override final { return "ToolFunctionPlotter.htm"; }
};

struct ProgramFunctionPlotterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolFunctionPlotter_1_1.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "FunctionPlotter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::functionPlotterVcl; }
  std::string GetUrl() const noexcept override final { return "ToolFunctionPlotterVcl.htm"; }
};

struct ProgramGaborFilter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolGaborFilter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "GaborFilter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::gaborFilter; }
  std::string GetUrl() const noexcept override final { return "ToolGaborFilter.htm"; }
};

struct ProgramGaborFilterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolGaborFilter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "GaborFilter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::gaborFilterVcl; }
  std::string GetUrl() const noexcept override final { return "ToolGaborFilterVcl.htm"; }
};

struct ProgramGrayCoder : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolGrayCoder_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "GrayCoder"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::grayCoder; }
  std::string GetUrl() const noexcept override final { return "ToolGrayCoder.htm"; }
};

struct ProgramGrayCoderVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolGrayCoder_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "GrayCoder (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::grayCoderVcl; }
  std::string GetUrl() const noexcept override final { return "ToolGrayCoderVcl.htm"; }
};

struct ProgramGtst : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ProjectGtst_1_2.png"; }
  std::string GetScreenName() const noexcept override final { return "GTST"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::gtst; }
  std::string GetUrl() const noexcept override final { return "ProjectGtst.htm"; }
};

struct ProgramHistogramEqualizationer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolHistogramEqualizationer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "HistogramEqualizationer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept override final { return ProgramType::histogramEqualizationer; }
  std::string GetUrl() const noexcept override final { return "ToolHistogramEqualizationer.htm"; }
};

struct ProgramHistogramEqualizationerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolHistogramEqualizationer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "HistogramEqualizationer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::histogramEqualizationerVcl; }
  std::string GetUrl() const noexcept override final { return "ToolHistogramEqualizationerVcl.htm"; }
};

struct ProgramHometrainer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolHometrainer_2_0.png"; }
  std::string GetScreenName() const noexcept override final { return "Hometrainer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::hometrainer; }
  std::string GetUrl() const noexcept override final { return "ToolHometrainer.htm"; }
};

struct ProgramHometrainerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolHometrainer_1_8.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Hometrainer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::hometrainerVcl; }
  std::string GetUrl() const noexcept override final { return "ToolHometrainerVcl.htm"; }
};

struct ProgramImageRotater : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolImageRotater_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ImageRotater"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept override final { return ProgramType::imageRotater; }
  std::string GetUrl() const noexcept override final { return "ToolImageRotater.htm"; }
};


struct ProgramImageRotaterClx : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolImageRotaterClx_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ImageRotater (CLX)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::imageRotaterClx; }
  std::string GetUrl() const noexcept override final { return "ToolImageRotaterClx.htm"; }
};

struct ProgramImageRotaterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolImageRotaterVcl_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ImageRotater (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::imageRotaterVcl; }
  std::string GetUrl() const noexcept override final { return "ToolImageRotaterVcl.htm"; }
};

struct ProgramK3OpEenRij : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameK3OpEenRij_6_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "GameK3OpEenRij_5_0.png"; }
  std::string GetScreenName() const noexcept override final { return "K3 Op Een Rij"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::k3OpEenRij; }
  std::string GetUrl() const noexcept override final { return "GameK3OpEenRij.htm"; }
};

struct ProgramK3OpEenRijVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameK3OpEenRij_4_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "K3 Op Een Rij (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::k3OpEenRijVcl; }
  std::string GetUrl() const noexcept override final { return "GameK3OpEenRijVcl.htm"; }
};

struct ProgramKalmanFilterer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolKalmanFilterer_1_15.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "KalmanFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::kalmanFilterer; }
  std::string GetUrl() const noexcept override final { return "ToolKalmanFilterer.htm"; }
};

struct ProgramKeySender : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolKeySender_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "KeySender"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::keySender; }
  std::string GetUrl() const noexcept override final { return "ToolKeySender.htm"; }
};

struct ProgramKnokfighterVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameKnokfighter_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Knokfighter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::knokfighterVcl; }
  std::string GetUrl() const noexcept override final { return "GameKnokfighterVcl.htm"; }
};


struct ProgramKTouchLectureCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "KTouchLectureCreator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::kTouchLectureCreator; }
  std::string GetUrl() const noexcept override final { return "ToolKTouchLectureCreator.htm"; }
};

struct ProgramLambdaBot : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "LambdaBot"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::lambdaBot; }
  std::string GetUrl() const noexcept override final { return "ToolLambdaBot.htm"; }
};

struct ProgramLearyCircumplex : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolLearyCircumplex_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "LearyCircumplex"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::learyCircumplex; }
  std::string GetUrl() const noexcept override final { return "ToolLearyCircumplex.htm"; }
};

struct ProgramLogisticGrowthSimulator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolLogisticGrowthSimulator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "LogisticGrowthSimulator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::logisticGrowthSimulator; }
  std::string GetUrl() const noexcept override final { return "ToolLogisticGrowthSimulator.htm"; }
};

struct ProgramLoose : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolLoose_2_0.png"; }
  std::string GetScreenName() const noexcept override final { return "Loose"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::loose; }
  std::string GetUrl() const noexcept override final { return "ToolLoose.htm"; }
};

struct ProgramMartianCafeTuinemaTycoon : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameMartianCafeTuinemaTycoon_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MartianCafeTuinemaTycoon"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::martianCafeTuinemaTycoon; }
  std::string GetUrl() const noexcept override final { return "GameMartianCafeTuinemaTycoon.htm"; }
};

struct ProgramMazeCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolMazeCreator_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MazeCreator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::mazeCreator; }
  std::string GetUrl() const noexcept override final { return "ToolMazeCreator.htm"; }
};

struct ProgramMazeCreatorVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolMazeCreator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MazeCreator (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::mazeCreatorVcl; }
  std::string GetUrl() const noexcept override final { return "ToolMazeCreatorVcl.htm"; }
};

struct ProgramMaziak : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameMaziak_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Maziak"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::maziak; }
  std::string GetUrl() const noexcept override final { return "GameMaziak.htm"; }
};

struct ProgramMaziakVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameMaziak_2_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Maziak (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::maziakVcl; }
  std::string GetUrl() const noexcept override final { return "GameMaziakVcl.htm"; }
};

/*
struct ProgramMetZnDrieen : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MetZnDrieen"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::metZnDrieen; }
  std::string GetUrl() const noexcept override final { return "GameMetZnDrieen.htm"; }
};
*/

struct ProgramMetZnDrieenVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameMetZnDrieen_1_3.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MetZnDrieen (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::metZnDrieenVcl; }
  std::string GetUrl() const noexcept override final { return "GameMetZnDrieenVcl.htm"; }
};

struct ProgramMidiLessonCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MidiLessonCreator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::midiLessonCreator; }
  std::string GetUrl() const noexcept override final { return "ToolMidiLessonCreator.htm"; }
};

struct ProgramMorpher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolMorpher_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Morpher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::morpher; }
  std::string GetUrl() const noexcept override final { return "ToolMorpher.htm"; }
};

struct ProgramMultiEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolMultiEncranger_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MultiEncranger"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::multiEncranger; }
  std::string GetUrl() const noexcept override final { return "ToolMultiEncranger.htm"; }
};

struct ProgramMultiEncrangerVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolMultiEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MultiEncranger (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::multiEncrangerVcl; }
  std::string GetUrl() const noexcept override final { return "ToolMultiEncrangerVcl.htm"; }
};

struct ProgramMuscaDomestica : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ProjectMuscaDomestica_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Project Musca Domestica"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::muscaDomestica; }
  std::string GetUrl() const noexcept override final { return "ProjectMuscaDomestica.htm"; }
};

struct ProgramMusicTheory : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolMusicTheory_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "MusicTheory"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::musicTheory; }
  std::string GetUrl() const noexcept override final { return "ToolMusicTheory.htm"; }
};

struct ProgramNdsmake : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Ndsmake"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::ndsmake; }
  std::string GetUrl() const noexcept override final { return "ToolNdsmake.htm"; }
};


struct ProgramPaperRockScissorsVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolPaperRockScissors_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "PaperRockScissors (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::paperRockScissorsVcl; }
  std::string GetUrl() const noexcept override final { return "ToolPaperRockScissorsVcl.htm"; }
};

struct ProgramPause : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Pause"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::pause; }
  std::string GetUrl() const noexcept override final { return "ToolPause.htm"; }
};

struct ProgramPerfectElasticCollision : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolPerfectElasticCollision_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "PerfectElasticCollision"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::perfectElasticCollision; }
  std::string GetUrl() const noexcept override final { return "ToolPerfectElasticCollision.htm"; }
};

struct ProgramPicToCode : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolPicToCode_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolPicToCode_1_3.png"; }
  std::string GetScreenName() const noexcept override final { return "PicToCode"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::picToCode; }
  std::string GetUrl() const noexcept override final { return "ToolPicToCode.htm"; }
};

struct ProgramPixelator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Pixelator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::pixelator; }
  std::string GetUrl() const noexcept override final { return "ToolPixelator.htm"; }
};

struct ProgramPixelatorVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolPixelator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Pixelator (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::pixelatorVcl; }
  std::string GetUrl() const noexcept override final { return "ToolPixelatorVcl.htm"; }
};

struct ProgramPokeVolleyVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GamePokeVolley_2_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "PokeVolley (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::pokeVolleyVcl; }
  std::string GetUrl() const noexcept override final { return "GamePokeVolley.htm"; }
};

struct ProgramPreDickAdvocaTor : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolPreDickAdvocaTor_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "PreDickAdvocaTor"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::preDickAdvocaTor; }
  std::string GetUrl() const noexcept override final { return "ToolPreDickAdvocaTor.htm"; }
};

struct ProgramPrimeExpert : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolPrimeExpert_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolTestPrimeExpert_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "PrimeExpert"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::primeExpert; }
  std::string GetUrl() const noexcept override final { return "ToolPrimeExpert.htm"; }
};

struct ProgramProjectRichelBilderbeek : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ProjectRichelBilderbeek_1_14.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ProjectRichelBilderbeek"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::projectRichelBilderbeek; }
  std::string GetUrl() const noexcept override final { return "ProjectRichelBilderbeek.htm"; }
};


struct ProgramPylos : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GamePylos_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Pylos"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::pylos; }
  std::string GetUrl() const noexcept override final { return "GamePylos.htm"; }
};

struct ProgramQmakeWatcher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolQmakeWatcher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "QmakeWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::qmakeWatcher; }
  std::string GetUrl() const noexcept override final { return "ToolQmakeWatcher.htm"; }
};

struct ProgramQuadraticSolver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return "ToolQuadraticSolver_1_0.png"; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolQuadraticSolver_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "QuadraticSolver"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::quadraticSolver; }
  std::string GetUrl() const noexcept override final { return "ToolQuadraticSolver.htm"; }
};

struct ProgramRampalEtienne : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ProjectRampalEtienne"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::rampalEtienne; }
  std::string GetUrl() const noexcept override final { return "ProjectRampalEtienne.htm"; }
};

struct ProgramRandomCode : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolRandomCode_4_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolRandomCode_3_0.png"; }
  std::string GetScreenName() const noexcept override final { return "RandomCode"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::randomCode; }
  std::string GetUrl() const noexcept override final { return "ToolRandomCode.htm"; }
};

struct ProgramRandomCodeVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolRandomCode_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "RandomCode (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::randomCodeVcl; }
  std::string GetUrl() const noexcept override final { return "ToolRandomCodeVcl.htm"; }
};

struct ProgramRasper : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolRasper_0_3.png"; }
  std::string GetScreenName() const noexcept override final { return "Rasper"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::rasper; }
  std::string GetUrl() const noexcept override final { return "ToolRasper.htm"; }
};

struct ProgramRefrigeratorPuzzleSolver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolRefrigeratorPuzzleSolver_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "RefrigeratorPuzzleSolver"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::refrigeratorPuzzleSolver; }
  std::string GetUrl() const noexcept override final { return "ToolRefrigeratorPuzzleSolver.htm"; }
};

struct ProgramRegexTester : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolRegexTester_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "RegexTester"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::regexTester; }
  std::string GetUrl() const noexcept override final { return "ToolRegexTester.htm"; }
};

struct ProgramReversi : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameReversi_0_1.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Reversi"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::reversi; }
  std::string GetUrl() const noexcept override final { return "GameReversi.htm"; }
};

struct ProgramReversiVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameReversiVcl_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Reversi VCL"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::reversiVcl; }
  std::string GetUrl() const noexcept override final { return "GameReversiVcl.htm"; }
};


struct ProgramRichelBilderbeekGallery : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolRichelBilderbeekGallery_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "RichelBilderbeekGallery"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::richelBilderbeekGallery; }
  std::string GetUrl() const noexcept override final { return "ToolRichelBilderbeekGallery.htm"; }
};

struct ProgramRichelBilderbeekNlSitemapGenerator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "RichelBilderbeekNlSitemapGenerator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::richelbilderbeekNlSitemapGenerator; }
  std::string GetUrl() const noexcept override final { return "ToolRichelbilderbeekNlSitemapGenerator.htm"; }
};

struct ProgramRubiksClock : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameRubiksClock_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "GameRubiksClock_2_1.png"; }
  std::string GetScreenName() const noexcept override final { return "Rubik's Clock"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::rubiksClock; }
  std::string GetUrl() const noexcept override final { return "GameRubiksClock.htm"; }
};

struct ProgramRubiksClockVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameRubiksClock_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Rubik's Clock (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::rubiksClockVcl; }
  std::string GetUrl() const noexcept override final { return "GameRubiksClockVcl.htm"; }
};

struct ProgramSearchAndDestroyChess : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Search And Destroy Chess"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::searchAndDestroyChess; }
  std::string GetUrl() const noexcept override final { return "GameSearchAndDestroyChess.htm"; }
};

struct ProgramSearchAndDestroyChessVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return "GameSearchAndDestroyChessConsole_1_0.png"; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameSearchAndDestroyChess_2_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Search And Destroy Chess (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::searchAndDestroyChessVcl; }
  std::string GetUrl() const noexcept override final { return "GameSearchAndDestroyChessVcl.htm"; }
};

struct ProgramSecretMessage : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolSecretMessage_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SecretMessage"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::secretMessage; }
  std::string GetUrl() const noexcept override final { return "ToolSecretMessage.htm"; }
};

struct ProgramSecretMessageVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSecretMessage_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SecretMessage (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::secretMessageVcl; }
  std::string GetUrl() const noexcept override final { return "ToolSecretMessageVcl.htm"; }
};

struct ProgramSimBrainiac : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSimBrainiac_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SimBrainiac"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::simBrainiac; }
  std::string GetUrl() const noexcept override final { return "ToolSimBrainiac.htm"; }
};

struct ProgramSimImmuneResponse : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSimImmuneResponse_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SimImmuneResponse"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::simImmuneResponse; }
  std::string GetUrl() const noexcept override final { return "ToolSimImmuneResponse.htm"; }
};

struct ProgramSimMysteryMachine : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolSimMysteryMachine_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolSimMysteryMachine_1_1_web.png"; }
  std::string GetScreenName() const noexcept override final { return "SimMysteryMachine"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::simMysteryMachine; }
  std::string GetUrl() const noexcept override final { return "ToolSimMysteryMachine.htm"; }
};

struct ProgramSimplifyNewick : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolSimplifyNewick_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SimplifyNewick"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::simplifyNewick; }
  std::string GetUrl() const noexcept override final { return "ToolSimplifyNewick.htm"; }
};

struct ProgramSimPredatorVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameSimPredator_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SimPredator (VCL)"; }

  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::simPredatorVcl; }
  std::string GetUrl() const noexcept override final { return "GameSimPredator.htm"; }
};

struct ProgramSimStagecraft : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSimStagecraft_1_1.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SimStagecraft"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::simStagecraft; }
  std::string GetUrl() const noexcept override final { return "ToolSimStagecraft.htm"; }
};

struct ProgramSoaSim : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSoaSim_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SoaSim"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::soaSim; }
  std::string GetUrl() const noexcept override final { return "ToolSoaSim.htm"; }
};

struct ProgramSolvePuzzleX : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SolvePuzzleX"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::solvePuzzleX; }
  std::string GetUrl() const noexcept override final { return "ToolSolvePuzzleX.htm"; }
};

struct ProgramSpaceHarryVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "GameSpaceHarry_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Space Harry (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::spaceHarryVcl; }
  std::string GetUrl() const noexcept override final { return "GameSpaceHarryVcl.htm"; }
};

struct ProgramStaircaseCardCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "StaircaseCardCreator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::staircaseCardCreator; }
  std::string GetUrl() const noexcept override final { return "ToolStaircaseCardCreator.htm"; }
};

struct ProgramStateObserver : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolStateObserver_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "StateObserver"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::stateObserver; }
  std::string GetUrl() const noexcept override final { return "ToolStateObserver.htm"; }
};

struct ProgramStyleSheetSetter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "StyleSheetSetter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::styleSheetSetter; }
  std::string GetUrl() const noexcept override final { return "ToolStyleSheetSetter.htm"; }
};

struct ProgramSurfacePlotter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolSurfacePlotter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SurfacePlotter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::surfacePlotter; }
  std::string GetUrl() const noexcept override final { return "ToolSurfacePlotter.htm"; }
};

struct ProgramSurfacePlotterVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolSurfacePlotter_1_2.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "SurfacePlotter (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::surfacePlotterVcl; }
  std::string GetUrl() const noexcept override final { return "ToolSurfacePlotterVcl.htm"; }
};

struct ProgramTankBattalion : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TankBattalion"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::tankBattalion; }
  std::string GetUrl() const noexcept override final { return "GameTankBattalion.htm"; }
};

struct ProgramTestAbout : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestAbout_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestAbout"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testAbout; }
  std::string GetUrl() const noexcept override final { return "ToolTestAbout.htm"; }
};

struct ProgramTestApproximator : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestApproximator_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testApproximator; }
  std::string GetUrl() const noexcept override final { return "ToolTestApproximator.htm"; }
};

struct ProgramTestBinaryNewickVector : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestBinaryNewickVector_1_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestBinaryNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testBinaryNewickVector; }
  std::string GetUrl() const noexcept override final { return "ToolTestBinaryNewickVector.htm"; }
};

struct ProgramTestBouncingBallsWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestBouncingBallsWidget_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestBouncingBallsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testBouncingBallsWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestBouncingBallsWidget.htm"; }
};

struct ProgramTestBouncingRectsWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestBouncingRectsWidget_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestBouncingRectsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testBouncingRectsWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestBouncingRectsWidget.htm"; }
};

struct ProgramTestBroadcastServer : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestBroadcastServer_1_0.png"; }
  std::string GetScreenName() const noexcept override final { return "TestBroadcastServer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testBroadcastServer; }
  std::string GetUrl() const noexcept override final { return "ToolTestBroadcastServer.htm"; }
};


struct ProgramTestChess : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestChess20120209.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestChess20120207.png"; }
  std::string GetScreenName() const noexcept override final { return "TestChess"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::testChess; }
  std::string GetUrl() const noexcept override final { return "ToolTestChess.htm"; }
};

struct ProgramTestConceptMap : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestConceptMap_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestConceptMap"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::unk; }
  ProgramType GetType() const noexcept override final { return ProgramType::testConceptMap; }
  std::string GetUrl() const noexcept override final { return "ToolTestConceptMap.htm"; }
};

struct ProgramTestDial : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestDial_2_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestDial_1_1.png"; }
  std::string GetScreenName() const noexcept override final { return "TestDial"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testDial; }
  std::string GetUrl() const noexcept override final { return "ToolTestDial.htm"; }
};

struct ProgramTestDrawCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestDrawCanvas_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestDrawCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testDrawCanvas; }
  std::string GetUrl() const noexcept override final { return "ToolTestDrawCanvas.htm"; }
};

struct ProgramTestEntrance : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestEntrance_1_0.png"; }
  std::string GetScreenName() const noexcept override final { return "TestEntrance"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testEntrance; }
  std::string GetUrl() const noexcept override final { return "ToolTestEntrance.htm"; }
};

struct ProgramTestExercise : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestExercise_1_0.png"; }
  std::string GetScreenName() const noexcept override final { return "TestExercise"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testExercise; }
  std::string GetUrl() const noexcept override final { return "ToolTestExercise.htm"; }
};

struct ProgramTestFunctionParser : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestFunctionParser_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolTestFunctionParser_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestFunctionParser_2_1.png"; }
  std::string GetScreenName() const noexcept override final { return "TestFunctionParser"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testFunctionParser; }
  std::string GetUrl() const noexcept override final { return "ToolTestFunctionParser.htm"; }
};

struct ProgramTestGnuplotInterface : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestGnuplotInterface"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testGnuplotInterface; }
  std::string GetUrl() const noexcept override final { return "ToolTestGnuplotInterface.htm"; }
};

struct ProgramTestGraphicsProxyWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestGraphicsProxyWidget_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestGraphicsProxyWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testGraphicsProxyWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestGraphicsProxyWidget.htm"; }
};

struct ProgramTestGravityWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestGravityWidget_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestGravityWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testGravityWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestGravityWidget.htm"; }
};

struct ProgramTestGroupWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestGroupWidget_1_0.png"; }
  std::string GetScreenName() const noexcept override final { return "TestGroupWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testGroupWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestGroupWidget.htm"; }
};

struct ProgramTestHugeVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestHugeVector"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testHugeVector; }
  std::string GetUrl() const noexcept override final { return "ToolTestHugeVector.htm"; }
};

struct ProgramTestImageCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestImageCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestImageCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testImageCanvas; }
  std::string GetUrl() const noexcept override final { return "ToolTestImageCanvas.htm"; }
};

struct ProgramTestLazy_init : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestLazy_init"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testLazy_init; }
  std::string GetUrl() const noexcept override final { return "ToolTestLazy_init.htm"; }
};

struct ProgramTestLed : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestLed_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestLed_1_1.png"; }
  std::string GetScreenName() const noexcept override final { return "TestLed"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testLed; }
  std::string GetUrl() const noexcept override final { return "ToolTestLed.htm"; }
};

struct ProgramTestManyDigitNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestManyDigitNewick_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestManyDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testManyDigitNewick; }
  std::string GetUrl() const noexcept override final { return "ToolTestManyDigitNewick.htm"; }
};

struct ProgramTestMultiApproximator : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestMultiApproximator_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestMultiApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testMultiApproximator; }
  std::string GetUrl() const noexcept override final { return "ToolTestMultiApproximator.htm"; }
};

struct ProgramTestMultiCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestMultiCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestMultiCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testMultiCanvas; }
  std::string GetUrl() const noexcept override final { return "ToolTestMultiCanvas.htm"; }
};

struct ProgramTestMultipleChoiceQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestMultipleChoiceQuestionDialog_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestMultipleChoiceQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testMultipleChoiceQuestion; }
  std::string GetUrl() const noexcept override final { return "ToolTestMultipleChoiceQuestion.htm"; }
};

struct ProgramTestMultiVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestMultiVector"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testMultiVector; }
  std::string GetUrl() const noexcept override final { return "ToolTestMultiVector.htm"; }
};

struct ProgramTestPlane : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestPlane_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestPlane"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testPlane; }
  std::string GetUrl() const noexcept override final { return "ToolTestPlane.htm"; }
};

struct ProgramTestNdsmake : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestNdsmake_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestNdsmake"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testNdsmake; }
  std::string GetUrl() const noexcept override final { return "ToolTestNdsmake.htm"; }
};

struct ProgramTestNeuralNet : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestNeuralNet_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestNeuralNet"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testNeuralNet; }
  std::string GetUrl() const noexcept override final { return "ToolTestNeuralNet.htm"; }
};

struct ProgramTestNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestNewick"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testNewick; }
  std::string GetUrl() const noexcept override final { return "ToolTestNewick.htm"; }
};

struct ProgramTestNewickVector : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestNewickVector_3_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testNewickVector; }
  std::string GetUrl() const noexcept override final { return "ToolTestNewickVector.htm"; }
};

struct ProgramTestOpenQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestOpenQuestion_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestOpenQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testOpenQuestion; }
  std::string GetUrl() const noexcept override final { return "ToolTestOpenQuestion.htm"; }
};

struct ProgramTestPolyFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestPolyFile"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testPolyFile; }
  std::string GetUrl() const noexcept override final { return "ToolTestPolyFile.htm"; }
};

struct ProgramTestPolyFileFromPolygons : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestPolyFileFromPolygons"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testPolyFileFromPolygons; }
  std::string GetUrl() const noexcept override final { return "ToolTestPolyFileFromPolygons.htm"; }
};

struct ProgramTestPylos : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestPylos_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestPylos"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testPylos; }
  std::string GetUrl() const noexcept override final { return "ToolTestPylos.htm"; }
};

struct ProgramTestQrcFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQrcFile_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQrcFile"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQrcFile; }
  std::string GetUrl() const noexcept override final { return "ToolTestQrcFile.htm"; }
};

struct ProgramTestQtArrowItems : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtArrowItems_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtArrowItems"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtArrowItems; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtArrowItems.htm"; }
};

struct ProgramTestQtCreatorProFile : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtCreatorProFile_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtCreatorProFile"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtCreatorProFile; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtCreatorProFile.htm"; }
};

struct ProgramTestQtHideAndShowDialog : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtHideAndShowDialog_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtHideAndShowDialog"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtHideAndShowDialog; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtHideAndShowDialog.htm"; }
};

struct ProgramTestQtKeyboardFriendlyGraphicsView : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestKeyboardFriendlyGraphicsView_0_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtKeyboardFriendlyGraphicsView"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtKeyboardFriendlyGraphicsView; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtKeyboardFriendlyGraphicsView.htm"; }
};

struct ProgramTestQtModels : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtModels_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtModels"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtModels; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtModels.htm"; }
};

struct ProgramTestQtOcrWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtOcrWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtOcrWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtOcrWidget.htm"; }
};

struct ProgramTestQtRoundedEditRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtRoundedEditRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtRoundedEditRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtRoundedEditRectItem; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtRoundedEditRectItem.htm"; }
};

struct ProgramTestQtRoundedRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtRoundedRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtRoundedRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtRoundedRectItem; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtRoundedRectItem.htm"; }
};

/*
struct ProgramTestQtRoundedTextRectItem : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQtRoundedTextRectItem_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQtRoundedTextRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQtRoundedTextRectItem; }
  std::string GetUrl() const noexcept override final { return "ToolTestQtRoundedTextRectItem.htm"; }
};
*/

struct ProgramTestQuestion : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestQuestion_3_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testQuestion; }
  std::string GetUrl() const noexcept override final { return "ToolTestQuestion.htm"; }
};

struct ProgramTestReversi : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestReversi_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestReversi"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testReversi; }
  std::string GetUrl() const noexcept override final { return "ToolTestReversi.htm"; }
};

struct ProgramTestSelectFileDialog : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestSelectFileDialog_1_1.png"; }
  std::string GetScreenName() const noexcept override final { return "TestSelectFileDialog"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testSelectFileDialog; }
  std::string GetUrl() const noexcept override final { return "ToolTestSelectFileDialog.htm"; }
};

struct ProgramTestServerPusher : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testServerPusher; }
  std::string GetUrl() const noexcept override final { return "ToolTestServerPusher.htm"; }
};

struct ProgramTestShape : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestShape_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestShape_1_0_web.png"; }
  std::string GetScreenName() const noexcept override final { return "TestShape"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testShape; }
  std::string GetUrl() const noexcept override final { return "ToolTestShape.htm"; }
};

struct ProgramTestShinyButton : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestShinyButton_2_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestShinyButton_2_0_web.png"; }
  std::string GetScreenName() const noexcept override final { return "TestShinyButton"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testShinyButton; }
  std::string GetUrl() const noexcept override final { return "ToolTestShinyButton.htm"; }
};

struct ProgramTestSimpleLinearRegression : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestSimpleLinearRegression_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestSimpleLinearRegression"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testSimpleLinearRegression; }
  std::string GetUrl() const noexcept override final { return "ToolTestSimpleLinearRegression.htm"; }
};

struct ProgramTestStopwatch : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestStopwatch"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testStopwatch; }
  std::string GetUrl() const noexcept override final { return "ToolTestStopwatch.htm"; }
};

struct ProgramTestTextCanvas : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestTextCanvas_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestTextCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTextCanvas; }
  std::string GetUrl() const noexcept override final { return "ToolTestTextCanvas.htm"; }
};

struct ProgramTestTextPositionWidget : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestTextPositionWidget_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestTextPositionWidget"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTextPositionWidget; }
  std::string GetUrl() const noexcept override final { return "ToolTestTextPositionWidget.htm"; }
};

struct ProgramTestTicTacToe : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestTicTacToe_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTestTicTacToe_1_2.png"; }
  std::string GetScreenName() const noexcept override final { return "TestTicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTicTacToe; }
  std::string GetUrl() const noexcept override final { return "ToolTestTicTacToe.htm"; }
};

struct ProgramTestTimedServerPusher : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestTimedServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTimedServerPusher; }
  std::string GetUrl() const noexcept override final { return "ToolTestTimedServerPusher.htm"; }
};

struct ProgramTestToggleButton : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestToggleButton_1_4.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestToggleButton"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::testToggleButton; }
  std::string GetUrl() const noexcept override final { return "ToolTestToggleButton.htm"; }
};

struct ProgramTestTriangle : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestTriangle_1_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestTriangle"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTriangle; }
  std::string GetUrl() const noexcept override final { return "ToolTestTriangle.htm"; }
};


struct ProgramTestTwoDigitNewick : public ProgramClass
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTestTwoDigitNewick_2_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TestTwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::testTwoDigitNewick; }
  std::string GetUrl() const noexcept override final { return "ToolTestTwoDigitNewick.htm"; }
};

struct ProgramThorVeen : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ProjectThorVeen_0_9.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Project ThorVeen"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::thorVeen; }
  std::string GetUrl() const noexcept override final { return "ProjectThorVeen.htm"; }
};

struct ProgramThresholdFilterer : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolThresholdFilterer_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ThresholdFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::thresholdFilterer; }
  std::string GetUrl() const noexcept override final { return "ToolThresholdFilterer.htm"; }
};

struct ProgramThresholdFiltererVcl : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolThresholdFilterer_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ThresholdFilterer (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::thresholdFiltererVcl; }
  std::string GetUrl() const noexcept override final { return "ToolThresholdFiltererVcl.htm"; }
};

struct ProgramTicTacToe : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return "GameTicTacToe_1_6.png"; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameTicTacToe_1_5.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "GameTicTacToe_1_4.png"; }
  std::string GetScreenName() const noexcept override final { return "TicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::ticTacToe; }
  std::string GetUrl() const noexcept override final { return "GameTicTacToe.htm"; }
};

struct ProgramTimePoll : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return "ToolTimePoll_4_1.png"; }
  std::string GetScreenName() const noexcept override final { return "TimePoll"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::timePoll; }
  std::string GetUrl() const noexcept override final { return "ToolTimePoll.htm"; }
};

struct ProgramTriangleMeshCreator : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolTriangleMeshCreator_1_2.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TriangleMeshCreator"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::triangleMeshCreator; }
  std::string GetUrl() const noexcept override final { return "ToolTriangleMeshCreator.htm"; }
};

struct ProgramTronCollection : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TronCollection"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::tronCollection; }
  std::string GetUrl() const noexcept override final { return "GameTronCollection.htm"; }
};

struct ProgramTronCollectionVcl : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "TronCollection (VCL)"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::nvr; }
  ProgramType GetType() const noexcept override final { return ProgramType::tronCollectionVcl; }
  std::string GetUrl() const noexcept override final { return "GameTronCollectionVcl.htm"; }
};

struct ProgramUbuntuOneWatcher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolUbuntuOneWatcher_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "UbuntuOneWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::ubuntuOneWatcher; }
  std::string GetUrl() const noexcept override final { return "ToolUbuntuOneWatcher.htm"; }
};


struct ProgramValentineCardDecrypter : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolValentineCardDecrypter_2_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "ValentineCardDecrypter"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::valentineCardDecrypter; }
  std::string GetUrl() const noexcept override final { return "ToolValentineCardDecrypter.htm"; }
};

struct ProgramVigenereCipher : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolVigenereCipher_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "VigenereCipher"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept override final { return ProgramType::vigenereCipher; }
  std::string GetUrl() const noexcept override final { return "ToolVigenereCipher.htm"; }
};

struct ProgramVirtualBastard : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "VirtualBastard"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::virtualBastard; }
  std::string GetUrl() const noexcept override final { return "ToolVirtualBastard.htm"; }
};

struct ProgramVisualAbc : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolVisualAbc_1_0.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "VisualAbc"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::visualAbc; }
  std::string GetUrl() const noexcept override final { return "ToolVisualAbc.htm"; }
};

struct ProgramWktToSvg : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "ToolWktToSvg_1_3.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "WktToSvg"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::wktToSvg; }
  std::string GetUrl() const noexcept override final { return "ToolWktToSvg.htm"; }
};

struct ProgramXeNonZero : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return "GameXeNonZero_0_1.png"; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "XeNonZero"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::xeNonZero; }
  std::string GetUrl() const noexcept override final { return "GameXeNonZero.htm"; }
};

struct ProgramZork : public ProgramGame
{
  std::string GetFilenameConsole() const noexcept override final { return "GameZork.png"; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetScreenName() const noexcept override final { return "Zork"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::zork; }
  std::string GetUrl() const noexcept override final { return "GameZork.htm"; }
};

/*
struct ProgramNewickVector : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetName() const { return "NewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept override final { return ProgramType::newickVector; }
  std::string GetUrl() const noexcept override final { return "ProjectNewickVector.htm"; }
};


struct ProgramTwoDigitNewick : public ProgramProject
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetName() const { return "TwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::twoDigitNewick; }
  std::string GetUrl() const noexcept override final { return "ProjectTwoDigitNewick.htm"; }
};






struct ProgramCreateSitemap : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return ""; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetName() const { return "CreateSitemap"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::createSitemap; }
  std::string GetUrl() const noexcept override final { return "ToolCreateSitemap.htm"; }
};


struct ProgramEncranger : public ProgramTool
{
  std::string GetFilenameConsole() const noexcept override final { return ""; }
  std::string GetFilenameDesktop() const noexcept override final { return ""; }
  std::string GetFilenameDesktopWindowsOnly() const noexcept override final { return "ToolEncranger_1_0.png"; }
  std::string GetFilenameWeb() const noexcept override final { return ""; }
  std::string GetName() const { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept override final { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept override final { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept override final { return ProgramStatus::no; }
  ProgramType GetType() const noexcept override final { return ProgramType::encranger; }
  std::string GetUrl() const noexcept override final { return "ToolEncranger.htm"; }
};

*/

std::ostream& operator<<(std::ostream& os, const Program& p) noexcept;
bool operator<(const Program& lhs, const Program& rhs) noexcept;

} //~namespace ribi

#endif // RIBI_RICHELBILDERBEEKPROGRAM_H
