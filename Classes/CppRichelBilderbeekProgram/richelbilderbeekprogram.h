//---------------------------------------------------------------------------
/*
RichelBilderbeek::Program, class for a program by Richel Bilderbeek
Copyright (C) 2012 Richel Bilderbeek

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
#ifndef RICHELBILDERBEEKPROGRAM_H
#define RICHELBILDERBEEKPROGRAM_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "richelbilderbeekprogramstatus.h"
#include "richelbilderbeekprogramtype.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace RichelBilderbeek {

///RichelBilderbeek::Program is the base class for program information
struct Program
{
  virtual ~Program() noexcept {}

  ///Create a std::vector with all different Program instances in it
  static const boost::shared_ptr<Program> CreateProgram(const ProgramType type) noexcept;

  ///Create a std::vector with all different Program instances in it
  static const std::vector<boost::shared_ptr<Program> > GetAllPrograms() noexcept;

  ///Get the filename of a console version screenshot
  virtual const std::string GetFilenameConsole() const noexcept = 0;

  ///Get the filename of a desktop platform-independent version screenshot
  virtual const std::string GetFilenameDesktop() const noexcept = 0;

  ///Get the filename of a desktop windows-only version screenshot
  virtual const std::string GetFilenameDesktopWindowsOnly() const noexcept = 0;

  ///Get the filename of a web application version screenshot
  virtual const std::string GetFilenameWeb() const noexcept = 0;

  ///Status of the console-only version
  virtual ProgramStatus GetStatusConsole() const noexcept = 0;

  ///Status of the Windows-only desktop version
  virtual ProgramStatus GetStatusDesktopWindowsOnly() const noexcept = 0;

  ///Status of the platform-independent desktop version
  virtual ProgramStatus GetStatusDesktop() const noexcept = 0;

  ///Status of the web application version
  virtual ProgramStatus GetStatusWebApplication() const noexcept = 0;

  ///The item its enum name, e.g. 'k3OpEenRij'
  const std::string GetName() const noexcept;

  ///The item its on-screen name, e.g. 'K3-Op-Een-Rij'
  const std::string GetScreenName() const noexcept;

  ///The program, e.g. 'RichelBilderbeekProgramType::boenken'
  virtual ProgramType GetType() const noexcept = 0;

  ///The type of program its name, e.g. 'Game'
  virtual const std::string GetTypeName() const noexcept = 0;

  ///The item its URL (at http://ww.richelbilderbeek.nl), e.g. 'ToolSimMysteryMachine.htm'
  virtual const std::string GetUrl() const noexcept = 0;

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///Get the base of a filename
  const std::string GetFilenameBase() const noexcept;
};

///RichelBilderbeek::ProgramClass is the base class for all class demonstration programs
struct ProgramClass : public RichelBilderbeek::Program
{
  virtual ~ProgramClass() noexcept {}

  ///The type of program its name, e.g. 'game'
  const std::string GetTypeName() const noexcept { return "class"; }
};

struct ProgramGame : public RichelBilderbeek::Program
{
  virtual ~ProgramGame() noexcept {}

  ///The type of program its name, e.g. 'game'
  const std::string GetTypeName() const noexcept { return "game"; }
};

struct ProgramProject : public RichelBilderbeek::Program
{
  virtual ~ProgramProject() noexcept {}

  ///The type of program its name, e.g. 'game'
  const std::string GetTypeName() const noexcept { return "project"; }
};

struct ProgramTool : public RichelBilderbeek::Program
{
  virtual ~ProgramTool() noexcept {}

  ///The type of program its name, e.g. 'game'
  const std::string GetTypeName() const noexcept { return "tool"; }
};

struct ProgramAminoAcidFighter : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameAminoAcidFighter_0_9.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameAminoAcidFighter_0_9.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "AminoAcidFighter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::aminoAcidFighter; }
  const std::string GetUrl() const noexcept { return "GameBeerAminoAcidFighter.htm"; }
};

struct ProgramAsciiArter : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolAsciiArter_5_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolAsciiArter_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestAsciiArter_4_1.png"; }
  const std::string GetScreenName() const noexcept { return "AsciiArter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::asciiArter; }
  const std::string GetUrl() const noexcept { return "ToolAsciiArter.htm"; }
};

struct ProgramBarbaImage : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolBarbaImage_1_3.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "BarbaImage"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::barbaImage; }
  const std::string GetUrl() const noexcept { return "ToolBarbaImage.htm"; }
};

struct ProgramBeerWanter : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameBeerWanter5.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameBeerWanter3.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "BeerWanter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::beerWanter; }
  const std::string GetUrl() const noexcept { return "GameBeerWanter.htm"; }
};

struct ProgramBillysGarden : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameBillysGarden_0_9.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameBillysGarden_0_9.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "BillysGarden"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::billysGarden; }
  const std::string GetUrl() const noexcept { return "GameBillysGarden.htm"; }
};

struct ProgramBochum : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ProjectBochumGaborFiltersResults.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Project Bochum"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::bochum; }
  const std::string GetUrl() const noexcept { return "ProjectBochum.htm"; }
};

struct ProgramBoenken : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameBoenken_4_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameBoenken_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Boenken"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::boenken; }
  const std::string GetUrl() const noexcept { return "GameBoenken.htm"; }
};

struct ProgramBrainweaver : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Brainweaver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::brainweaver; }
  const std::string GetUrl() const noexcept { return "ProjectBrainweaver.htm"; }
};

struct ProgramBristol : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ProjectBristol_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Bristol"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::brainweaver; }
  const std::string GetUrl() const noexcept { return "ProjectBristol.htm"; }
};

struct ProgramChrisWiley : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectChrisWiley_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Project Chris Wiley"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::chrisWiley; }
  const std::string GetUrl() const noexcept { return "ProjectChrisWiley.htm"; }
};

struct ProgramCodeToHtml : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolCodeToHtml_2_3.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolCodeToHtml_2_0.png"; }
  const std::string GetScreenName() const noexcept { return "CodeToHtml"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::codeToHtml; }
  const std::string GetUrl() const noexcept { return "ToolCodeToHtml.htm"; }
};

struct ProgramConnectThree : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameConnectThree_5_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "GameConnectThree_6_0.png"; }
  const std::string GetScreenName() const noexcept { return "ConnectThree"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::connectThree; }
  const std::string GetUrl() const noexcept { return "GameConnectThree.htm"; }
};

struct ProgramCorridor : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameCorridor.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Corridor"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::corridor; }
  const std::string GetUrl() const noexcept { return "GameCorridor.htm"; }
};

struct ProgramCreateGlossary : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "CreateGlossary"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createGlossary; }
  const std::string GetUrl() const noexcept { return "ToolCreateGlossary.htm"; }
};

struct ProgramCreateQtProjectZipFile : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolCreateQtProjectZipFile_2_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "CreateQtProjectZipFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createQtProjectZipFile; }
  const std::string GetUrl() const noexcept { return "ToolCreateQtProjectZipFile.htm"; }
};

struct ProgramCrossPoll : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectCrossPoll3.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "CrossPoll"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::crossPoll; }
  const std::string GetUrl() const noexcept { return "ProjectCrossPoll.htm"; }
};

struct ProgramDasWahreSchlagerfest : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameDasWahreSchlagerfest_2_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameDasWahreSchlagerfest_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Das Wahre Schlagerfest"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::dasWahreSchlagerfest; }
  const std::string GetUrl() const noexcept { return "GameDasWahreSchlagerfest.htm"; }
};

struct ProgramDotMatrix : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolDotMatrix_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "DotMatrix"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::dotMatrix; }
  const std::string GetUrl() const noexcept { return "ToolDotMatrix.htm"; }
};

struct ProgramEverythingToPiecesShooter : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "EverythingToPiecesShooter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::everythingToPiecesShooter; }
  const std::string GetUrl() const noexcept { return "GameEverythingToPiecesShooter.htm"; }
};

struct ProgramFakeEvy : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "GrayFakeEvy"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::fakeEvy; }
  const std::string GetUrl() const noexcept { return "ToolFakeEvy.htm"; }
};

struct ProgramFilterOperationer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFilterOperationer_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "FilterOperationer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::filterOperationer; }
  const std::string GetUrl() const noexcept { return "ToolFilterOperationer.htm"; }
};

struct ProgramFryskLeareLieder : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFryskLeareLieder_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "FryskLeareLieder"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::fryskLeareLieder; }
  const std::string GetUrl() const noexcept { return "ToolFryskLeareLieder.htm"; }
};

struct ProgramFunctionPlotter : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolFunctionPlotter_1_1.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "FunctionPlotter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::functionPlotter; }
  const std::string GetUrl() const noexcept { return "ToolFunctionPlotter.htm"; }
};

struct ProgramGaborFilter : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolGaborFilter_2_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolGaborFilter_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "GaborFilter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::gaborFilter; }
  const std::string GetUrl() const noexcept { return "ToolGaborFilter.htm"; }
};

struct ProgramGrayCoder : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolGrayCoder_2_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolGrayCoder_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "GrayCoder"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::grayCoder; }
  const std::string GetUrl() const noexcept { return "GrayCoder.htm"; }
};

struct ProgramGtst : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ProjectGtst_1_2.png"; }
  const std::string GetScreenName() const noexcept { return "GTST"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::gtst; }
  const std::string GetUrl() const noexcept { return "ProjectGtst.htm"; }
};

struct ProgramHistogramEqualizationer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolHistogramEqualizationer_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "HistogramEqualizationer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::unk; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::histogramEqualizationer; }
  const std::string GetUrl() const noexcept { return "ToolHistogramEqualizationer.htm"; }
};

struct ProgramHometrainer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolHometrainer_1_8.png"; }
  const std::string GetFilenameWeb() const noexcept { return "ToolHometrainer_2_0.png"; }
  const std::string GetScreenName() const noexcept { return "Hometrainer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::hometrainer; }
  const std::string GetUrl() const noexcept { return "ToolHometrainer.htm"; }
};

struct ProgramImageRotaterClx : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolImageRotaterClx_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "ImageRotater"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::imageRotaterClx; }
  const std::string GetUrl() const noexcept { return "ToolImageRotater.htm"; }
};

struct ProgramImageRotaterVcl : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolImageRotaterVcl_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "ImageRotater"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::imageRotaterClx; }
  const std::string GetUrl() const noexcept { return "ToolImageRotater.htm"; }
};

struct ProgramK3OpEenRij : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameK3OpEenRij_6_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameK3OpEenRij_4_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "GameK3OpEenRij_5_0.png"; }
  const std::string GetScreenName() const noexcept { return "K3 Op Een Rij"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::k3OpEenRij; }
  const std::string GetUrl() const noexcept { return "GameK3OpEenRij.htm"; }
};

struct ProgramKalmanFilterer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolKalmanFilterer_1_11.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolKalmanFilterer_1_4.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "KalmanFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::kalmanFilterer; }
  const std::string GetUrl() const noexcept { return "ToolKalmanFilterer.htm"; }
};

struct ProgramKeySender : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolKeySender_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "KeySender"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::keySender; }
  const std::string GetUrl() const noexcept { return "ToolKeySender.htm"; }
};

struct ProgramKnokfighter : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameKnokfighter_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Knokfighter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::knokfighter; }
  const std::string GetUrl() const noexcept { return "GameKnokfighter.htm"; }
};

struct ProgramKTouchLectureCreator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "KTouchLectureCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::kTouchLectureCreator; }
  const std::string GetUrl() const noexcept { return "ToolKTouchLectureCreator.htm"; }
};

struct ProgramLambdaBot : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "LambdaBot"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::lambdaBot; }
  const std::string GetUrl() const noexcept { return "ToolLambdaBot.htm"; }
};

struct ProgramLearyCircumplex : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolLearyCircumplex_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "LearyCircumplex"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::learyCircumplex; }
  const std::string GetUrl() const noexcept { return "ToolLearyCircumplex.htm"; }
};

struct ProgramLogisticGrowthSimulator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolLogisticGrowthSimulator_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "LogisticGrowthSimulator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::logisticGrowthSimulator; }
  const std::string GetUrl() const noexcept { return "ToolLogisticGrowthSimulator.htm"; }
};

struct ProgramLoose : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolLoose_2_0.png"; }
  const std::string GetScreenName() const noexcept { return "Loose"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::loose; }
  const std::string GetUrl() const noexcept { return "ToolLoose.htm"; }
};

struct ProgramMartianCafeTuinemaTycoon : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMartianCafeTuinemaTycoon_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MartianCafeTuinemaTycoon"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::martianCafeTuinemaTycoon; }
  const std::string GetUrl() const noexcept { return "GameMartianCafeTuinemaTycoon.htm"; }
};

struct ProgramMazeCreator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolMazeCreator_2_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMazeCreator_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MazeCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::mazeCreator; }
  const std::string GetUrl() const noexcept { return "ToolMazeCreator.htm"; }
};

struct ProgramMaziak : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameMaziak_1_3.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMaziak_2_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Maziak"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::maziak; }
  const std::string GetUrl() const noexcept { return "GameMaziak.htm"; }
};

struct ProgramMetZnDrieen : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameMetZnDrieen_1_3.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MetZnDrieen"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::metZnDrieen; }
  const std::string GetUrl() const noexcept { return "GameMetZnDrieen.htm"; }
};

struct ProgramMidiLessonCreator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MidiLessonCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::midiLessonCreator; }
  const std::string GetUrl() const noexcept { return "ToolMidiLessonCreator.htm"; }
};

struct ProgramMorpher : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMorpher_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Morpher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::morpher; }
  const std::string GetUrl() const noexcept { return "ToolMorpher.htm"; }
};

struct ProgramMultiEncranger : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolMultiEncranger_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MultiEncranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::multiEncranger; }
  const std::string GetUrl() const noexcept { return "ToolMultiEncranger.htm"; }
};

struct ProgramMuscaDomestica : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectMuscaDomestica_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Project Musca Domestica"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::muscaDomestica; }
  const std::string GetUrl() const noexcept { return "ProjectMuscaDomestica.htm"; }
};

struct ProgramMusicTheory : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolMusicTheory_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "MusicTheory"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::musicTheory; }
  const std::string GetUrl() const noexcept { return "ToolMusicTheory.htm"; }
};

struct ProgramNdsmake : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Ndsmake"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ndsmake; }
  const std::string GetUrl() const noexcept { return "CppNdsmake.htm"; }
};

struct ProgramNdsPaint : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "NdsPaint"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ndsPaint; }
  const std::string GetUrl() const noexcept { return "CppNdsPaint.htm"; }
};

struct ProgramPaperRockScissors : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolPaperRockScissors_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "PaperRockScissors"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::paperRockScissors; }
  const std::string GetUrl() const noexcept { return "ToolPaperRockScissors.htm"; }
};

struct ProgramPause : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Pause"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pause; }
  const std::string GetUrl() const noexcept { return "ToolPause.htm"; }
};

struct ProgramPerfectElasticCollision : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolPerfectElasticCollision_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "PerfectElasticCollision"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::perfectElasticCollision; }
  const std::string GetUrl() const noexcept { return "ToolPerfectElasticCollision.htm"; }
};

struct ProgramPicToCode : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolPicToCode_1_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolPicToCode_1_3.png"; }
  const std::string GetScreenName() const noexcept { return "PicToCode"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::picToCode; }
  const std::string GetUrl() const noexcept { return "ToolPicToCode.htm"; }
};

struct ProgramPixelator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolPixelator_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Pixelator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pixelator; }
  const std::string GetUrl() const noexcept { return "ToolPixelator.htm"; }
};

struct ProgramPokeVolley : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GamePokeVolley_2_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "PokeVolley"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pokeVolley; }
  const std::string GetUrl() const noexcept { return "GamePokeVolley.htm"; }
};

struct ProgramPong : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Pong"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pong; }
  const std::string GetUrl() const noexcept { return "GamePong.htm"; }
};

struct ProgramPrimeExpert : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "PrimeExpert"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::primeExpert; }
  const std::string GetUrl() const noexcept { return "ToolPrimeExpert.htm"; }
};

struct ProgramPylos : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GamePylos_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Pylos"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::pylos; }
  const std::string GetUrl() const noexcept { return "GamePylos.htm"; }
};

struct ProgramQmakeWatcher : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "QmakeWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::qmakeWatcher; }
  const std::string GetUrl() const noexcept { return "ToolQmakeWatcher.htm"; }
};

struct ProgramQuadraticSolver : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return "ToolQuadraticSolver_1_0.png"; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "QuadraticSolver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::quadraticSolver; }
  const std::string GetUrl() const noexcept { return "ToolQuadraticSolver.htm"; }
};

struct ProgramRampal : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "ProjectRampal"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::rampal; }
  const std::string GetUrl() const noexcept { return "ProjectRampal.htm"; }
};

struct ProgramRandomCode : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolRandomCode_4_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolRandomCode_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "ToolRandomCode_3_0.png"; }
  const std::string GetScreenName() const noexcept { return "RandomCode"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::randomCode; }
  const std::string GetUrl() const noexcept { return "ToolRandomCode.htm"; }
};

struct ProgramRasper : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolRasper_0_3.png"; }
  const std::string GetScreenName() const noexcept { return "Rasper"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::rasper; }
  const std::string GetUrl() const noexcept { return "ToolRasper.htm"; }
};

struct ProgramRefrigeratorPuzzleSolver : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolRefrigeratorPuzzleSolver_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "RefrigeratorPuzzleSolver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::refrigeratorPuzzleSolver; }
  const std::string GetUrl() const noexcept { return "ToolRefrigeratorPuzzleSolver.htm"; }
};

struct ProgramRegexTester : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolRegexTester_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "RegexTester"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::regexTester; }
  const std::string GetUrl() const noexcept { return "ToolRegexTester.htm"; }
};

struct ProgramReversi : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameReversi_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Reversi"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::reversi; }
  const std::string GetUrl() const noexcept { return "GameReversi.htm"; }
};

struct ProgramRichelBilderbeekGallery : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolRichelBilderbeekGallery_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "RichelBilderbeekGallery"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::richelBilderbeekGallery; }
  const std::string GetUrl() const noexcept { return "ToolRichelBilderbeekGallery.htm"; }
};

struct ProgramRichelBilderbeekNlSitemapGenerator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "RichelBilderbeekNlSitemapGenerator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::richelbilderbeekNlSitemapGenerator; }
  const std::string GetUrl() const noexcept { return "ToolRichelBilderbeekNlSitemapGenerator.htm"; }
};

struct ProgramRubiksClock : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameRubiksClockDesktop_2_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameRubiksClock_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "GameRubiksClock_2_1.png"; }
  const std::string GetScreenName() const noexcept { return "Rubik's Clock"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::rubiksClock; }
  const std::string GetUrl() const noexcept { return "GameRubiksClock.htm"; }
};

struct ProgramSearchAndDestroyChess : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return "GameSearchAndDestroyChessConsole_1_0.png"; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSearchAndDestroyChess_2_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Search And Destroy Chess"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::searchAndDestroyChess; }
  const std::string GetUrl() const noexcept { return "GameSearchAndDestroyChess.htm"; }
};

struct ProgramSecretMessage : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSecretMessage_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SecretMessage"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::secretMessage; }
  const std::string GetUrl() const noexcept { return "ToolSecretMessage.htm"; }
};

struct ProgramSimBrainiac : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimBrainiac_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SimBrainiac"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simBrainiac; }
  const std::string GetUrl() const noexcept { return "ToolSimBrainiac.htm"; }
};

struct ProgramSimImmuneResponse : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimImmuneResponse_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SimImmuneResponse"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simImmuneResponse; }
  const std::string GetUrl() const noexcept { return "ToolSimImmuneResponse.htm"; }
};

struct ProgramSimMysteryMachine : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolSimMysteryMachine_1_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolSimMysteryMachine_1_1_web.png"; }
  const std::string GetScreenName() const noexcept { return "SimMysteryMachine"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::simMysteryMachine; }
  const std::string GetUrl() const noexcept { return "ToolSimMysteryMachine.htm"; }
};

struct ProgramSimplifyNewick : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolSimplifyNewick_1_2.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SimplifyNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simplifyNewick; }
  const std::string GetUrl() const noexcept { return "ToolSimplifyNewick.htm"; }
};

struct ProgramSimPredator : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSimPredator_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SimPredator"; }

  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simPredator; }
  const std::string GetUrl() const noexcept { return "ToolSimPredator.htm"; }
};

struct ProgramSimStagecraft : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSimStagecraft_1_1.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SimStagecraft"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::simStagecraft; }
  const std::string GetUrl() const noexcept { return "ToolSimStagecraft.htm"; }
};

struct ProgramSoaSim : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSoaSim_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SoaSim"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::soaSim; }
  const std::string GetUrl() const noexcept { return "ToolSoaSim.htm"; }
};

struct ProgramSolvePuzzleX : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SolvePuzzleX"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::solvePuzzleX; }
  const std::string GetUrl() const noexcept { return "ToolSolvePuzzleX.htm"; }
};

struct ProgramSpaceHarry : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "GameSpaceHarry_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Space Harry"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::spaceHarry; }
  const std::string GetUrl() const noexcept { return "GameSpaceHarry.htm"; }
};

struct ProgramStaircaseCardCreator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "StaircaseCardCreator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::staircaseCardCreator; }
  const std::string GetUrl() const noexcept { return "ToolStaircaseCardCreator.htm"; }
};

struct ProgramStateObserver : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolStateObserver_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "StateObserver"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::stateObserver; }
  const std::string GetUrl() const noexcept { return "ToolStateObserver.htm"; }
};

struct ProgramStyleSheetSetter : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "StyleSheetSetter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::styleSheetSetter; }
  const std::string GetUrl() const noexcept { return "ToolStyleSheetSetter.htm"; }
};

struct ProgramSuperNsanaBros : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Super Nsana Bros"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::superNsanaBros; }
  const std::string GetUrl() const noexcept { return "GameSuperNsanaBros.htm"; }
};

struct ProgramSurfacePlotter : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolSurfacePlotter_1_2.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "SurfacePlotter"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::surfacePlotter; }
  const std::string GetUrl() const noexcept { return "ToolSurfacePlotter.htm"; }
};

struct ProgramTankBattalion : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TankBattalion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::tankBattalion; }
  const std::string GetUrl() const noexcept { return "GameTankBattalion.htm"; }
};

struct ProgramTestAbout : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestAbout_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestAbout"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testAbout; }
  const std::string GetUrl() const noexcept { return "ToolTestAbout.htm"; }
};

struct ProgramTestApproximator : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestApproximator_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testApproximator; }
  const std::string GetUrl() const noexcept { return "ToolTestApproximator.htm"; }
};

struct ProgramTestBinaryNewickVector : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestBinaryNewickVector_1_5.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestBinaryNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBinaryNewickVector; }
  const std::string GetUrl() const noexcept { return "ToolTestBinaryNewickVector.htm"; }
};

struct ProgramTestBouncingBallsWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestBouncingBallsWidget_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestBouncingBallsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBouncingBallsWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestBouncingBallsWidget.htm"; }
};

struct ProgramTestBouncingRectsWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestBouncingRectsWidget_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestBouncingRectsWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testBouncingRectsWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestBouncingRectsWidget.htm"; }
};

struct ProgramTestBroadcastServer : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestBroadcastServer_1_0.png"; }
  const std::string GetScreenName() const noexcept { return "TestBroadcastServer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testBroadcastServer; }
  const std::string GetUrl() const noexcept { return "ToolTestBroadcastServer.htm"; }
};

struct ProgramTestCanvas : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestCanvas"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testCanvas; }
  const std::string GetUrl() const noexcept { return "ToolTestCanvas.htm"; }
};

struct ProgramTestChess : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestChess20120209.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestChess20120207.png"; }
  const std::string GetScreenName() const noexcept { return "TestChess"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::wip; }
  ProgramType GetType() const noexcept { return ProgramType::testChess; }
  const std::string GetUrl() const noexcept { return "ToolTestChess.htm"; }
};

struct ProgramTestDial : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestDial_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestDial_1_1.png"; }
  const std::string GetScreenName() const noexcept { return "TestDial"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testDial; }
  const std::string GetUrl() const noexcept { return "ToolTestDial.htm"; }
};

struct ProgramEncranger : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolEncranger_2_5.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolEncranger_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "ToolEncranger_2_1.png"; }
  const std::string GetScreenName() const noexcept { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::encranger; }
  const std::string GetUrl() const noexcept { return "ToolEncranger.htm"; }
};

struct ProgramTestEntrance : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestEntrance_1_0.png"; }
  const std::string GetScreenName() const noexcept { return "TestEntrance"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::n_a; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testEntrance; }
  const std::string GetUrl() const noexcept { return "ToolTestEntrance.htm"; }
};

struct ProgramTestExercise : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestExercise_1_0.png"; }
  const std::string GetScreenName() const noexcept { return "TestExercise"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testExercise; }
  const std::string GetUrl() const noexcept { return "ToolTestExercise.htm"; }
};

struct ProgramTestFunctionParser : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestFunctionParser_2_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolTestFunctionParser_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestFunctionParser_2_1.png"; }
  const std::string GetScreenName() const noexcept { return "TestFunctionParser"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testFunctionParser; }
  const std::string GetUrl() const noexcept { return "ToolTestFunctionParser.htm"; }
};

struct ProgramTestGnuplotInterface : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestGnuplotInterface"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGnuplotInterface; }
  const std::string GetUrl() const noexcept { return "ToolTestGnuplotInterface.htm"; }
};

struct ProgramTestGraphicsProxyWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestGraphicsProxyWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGraphicsProxyWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestGraphicsProxyWidget.htm"; }
};

struct ProgramTestGravityWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestGravityWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testGravityWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestGravityWidget.htm"; }
};

struct ProgramTestGroupWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestGroupWidget_1_0.png"; }
  const std::string GetScreenName() const noexcept { return "TestGroupWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testGroupWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestGroupWidget.htm"; }
};

struct ProgramTestHugeVector : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestHugeVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testHugeVector; }
  const std::string GetUrl() const noexcept { return "ToolTestHugeVector.htm"; }
};

struct ProgramTestTestLazy_init : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestLazy_init"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testLazy_init; }
  const std::string GetUrl() const noexcept { return "ToolTestLazy_init.htm"; }
};

struct ProgramTestLed : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestLed_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestLed_1_1.png"; }
  const std::string GetScreenName() const noexcept { return "TestLed"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testLed; }
  const std::string GetUrl() const noexcept { return "ToolTestLed.htm"; }
};

struct ProgramTestManyDigitNewick : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestManyDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testManyDigitNewick; }
  const std::string GetUrl() const noexcept { return "ToolTestManyDigitNewick.htm"; }
};

struct ProgramTestMultiApproximator : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestMultiApproximator_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestMultiApproximator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultiApproximator; }
  const std::string GetUrl() const noexcept { return "ToolTestMultiApproximator.htm"; }
};

struct ProgramTestMultipleChoiceQuestion : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestMultipleChoiceQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultipleChoiceQuestion; }
  const std::string GetUrl() const noexcept { return "ToolTestMultipleChoiceQuestion.htm"; }
};

struct ProgramTestMultiVector : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestMultiVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testMultiVector; }
  const std::string GetUrl() const noexcept { return "ToolTestMultiVector.htm"; }
};

struct ProgramTestNdsmake : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestNdsmake_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestNdsmake"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNdsmake; }
  const std::string GetUrl() const noexcept { return "ToolTestNdsmake.htm"; }
};

struct ProgramTestNeuralNet : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestNeuralNet_0_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestNeuralNet"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNeuralNet; }
  const std::string GetUrl() const noexcept { return "ToolTestNeuralNet.htm"; }
};

struct ProgramTestNewick : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNewick; }
  const std::string GetUrl() const noexcept { return "ToolTestNewick.htm"; }
};

struct ProgramTestNewickVector : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestNewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testNewickVector; }
  const std::string GetUrl() const noexcept { return "ToolTestNewickVector.htm"; }
};

struct ProgramTestOpenQuestion : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestOpenQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testOpenQuestion; }
  const std::string GetUrl() const noexcept { return "ToolTestOpenQuestion.htm"; }
};

struct ProgramTestPrimeExpert : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestPrimeExpert_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestPrimeExpert"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPrimeExpert; }
  const std::string GetUrl() const noexcept { return "ToolTestPrimeExpert.htm"; }
};

struct ProgramTestPylos : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestPylos_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestPylos"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testPylos; }
  const std::string GetUrl() const noexcept { return "ToolTestPylos.htm"; }
};

struct ProgramTestQrcFile : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQrcFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQrcFile; }
  const std::string GetUrl() const noexcept { return "ToolTestQrcFile.htm"; }
};

struct ProgramTestQtArrowItems : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestQtArrowItems_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtArrowItems"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtArrowItems; }
  const std::string GetUrl() const noexcept { return "ToolTestQtArrowItems.htm"; }
};

struct ProgramTestQtCreatorProFile : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtCreatorProFile"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtCreatorProFile; }
  const std::string GetUrl() const noexcept { return "ToolTestQtCreatorProFile.htm"; }
};

struct ProgramTestQtHideAndShowDialog : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtHideAndShowDialog"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtHideAndShowDialog; }
  const std::string GetUrl() const noexcept { return "ToolTestQtHideAndShowDialog.htm"; }
};

struct ProgramTestQtKeyboardFriendlyGraphicsView : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtKeyboardFriendlyGraphicsView"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtKeyboardFriendlyGraphicsView; }
  const std::string GetUrl() const noexcept { return "ToolTestQtKeyboardFriendlyGraphicsView.htm"; }
};

struct ProgramTestQtModels : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtModels"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtModels; }
  const std::string GetUrl() const noexcept { return "ToolTestQtModels.htm"; }
};

struct ProgramTestQtOcrWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtOcrWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtOcrWidget; }
  const std::string GetUrl() const noexcept { return "ToolTestQtOcrWidget.htm"; }
};

struct ProgramTestQtRoundedEditRectItem : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedEditRectItem_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtRoundedEditRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedEditRectItem; }
  const std::string GetUrl() const noexcept { return "ToolTestQtRoundedEditRectItem.htm"; }
};

struct ProgramTestQtRoundedRectItem : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedRectItem_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtRoundedRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedRectItem; }
  const std::string GetUrl() const noexcept { return "ToolTestQtRoundedRectItem.htm"; }
};

struct ProgramTestQtRoundedTextRectItem : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestQtRoundedTextRectItem_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQtRoundedTextRectItem"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testQtRoundedTextRectItem; }
  const std::string GetUrl() const noexcept { return "ToolTestQtRoundedTextRectItem.htm"; }
};

struct ProgramTestQuestion : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestQuestion_2_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestQuestion"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::unk; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testQuestion; }
  const std::string GetUrl() const noexcept { return "ToolTestQuestion.htm"; }
};

struct ProgramTestReversi : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestReversi"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testReversi; }
  const std::string GetUrl() const noexcept { return "ToolTestReversi.htm"; }
};

struct ProgramTestSelectFileDialog : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestSelectFileDialog_1_1.png"; }
  const std::string GetScreenName() const noexcept { return "TestSelectFileDialog"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testSelectFileDialog; }
  const std::string GetUrl() const noexcept { return "ToolTestSelectFileDialog.htm"; }
};

struct ProgramTestServerPusher : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testServerPusher; }
  const std::string GetUrl() const noexcept { return "ToolTestServerPusher.htm"; }
};

struct ProgramTestShape : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestShape_1_0_desktop.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestShape_1_0_web.png"; }
  const std::string GetScreenName() const noexcept { return "TestShape"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testShape; }
  const std::string GetUrl() const noexcept { return "ToolTestShape.htm"; }
};

struct ProgramTestShinyButton : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestShinyButton_2_0_desktop.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestShinyButton_2_0_web.png"; }
  const std::string GetScreenName() const noexcept { return "TestShinyButton"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testShinyButton; }
  const std::string GetUrl() const noexcept { return "ToolTestShinyButton.htm"; }
};

struct ProgramTestSimpleLinearRegression : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestSimpleLinearRegression_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestSimpleLinearRegression"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testSimpleLinearRegression; }
  const std::string GetUrl() const noexcept { return "ToolTestSimpleLinearRegression.htm"; }
};

struct ProgramTestStopwatch : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestStopwatch"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testStopwatch; }
  const std::string GetUrl() const noexcept { return "ToolTestStopwatch.htm"; }
};

struct ProgramTestTextPositionWidget : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestTextPositionWidget"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTextPositionWidget; }
  const std::string GetUrl() const noexcept { return "ToolTextPositionWidget.htm"; }
};

struct ProgramTestTicTacToe : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestTicTacToe_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTestTicTacToe_1_2.png"; }
  const std::string GetScreenName() const noexcept { return "TestTicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testTicTacToe; }
  const std::string GetUrl() const noexcept { return "ToolTestTicTacToe.htm"; }
};

struct ProgramTestTimedServerPusher : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestTimedServerPusher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testTimedServerPusher; }
  const std::string GetUrl() const noexcept { return "ToolTestTimedServerPusher.htm"; }
};

struct ProgramTestToggleButton : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestToggleButton"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::testToggleButton; }
  const std::string GetUrl() const noexcept { return "ToolTestToggleButton.htm"; }
};

struct ProgramTestTwoDigitNewick : public RichelBilderbeek::ProgramClass
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTestTwoDigitNewick_0_6.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TestTwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::testTwoDigitNewick; }
  const std::string GetUrl() const noexcept { return "ToolTestTwoDigitNewick.htm"; }
};

struct ProgramThorVeen : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ProjectThorVeen_0_9.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Project ThorVeen"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::thorVeen; }
  const std::string GetUrl() const noexcept { return "ProjectThorVeen.htm"; }
};

struct ProgramThresholdFilterer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolThresholdFilterer_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "ThresholdFilterer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::thresholdFilterer; }
  const std::string GetUrl() const noexcept { return "ToolThresholdFilterer.htm"; }
};

struct ProgramTicTacToe : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameTicTacToe_1_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "GameTicTacToe_1_4.png"; }
  const std::string GetScreenName() const noexcept { return "TicTacToe"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToe; }
  const std::string GetUrl() const noexcept { return "GameTicTacToe.htm"; }
};

struct ProgramTicTacToeLearner : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTicTacToeLearner_0_3.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TicTacToeLearner"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToeLearner; }
  const std::string GetUrl() const noexcept { return "ToolTicTacToeLearner.htm"; }
};

struct ProgramTicTacToeValuer : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolTicTacToeValuer_0_7.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TicTacToeValuer"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ticTacToeValuer; }
  const std::string GetUrl() const noexcept { return "ToolTicTacToeValuer.htm"; }
};

struct ProgramTimePoll : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return "ToolTimePoll_4_1.png"; }
  const std::string GetScreenName() const noexcept { return "TimePoll"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::timePoll; }
  const std::string GetUrl() const noexcept { return "ToolTimePoll.htm"; }
};

struct ProgramTronCollection : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "TronCollection"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::wip; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::tronCollection; }
  const std::string GetUrl() const noexcept { return "GameTronCollection.htm"; }
};

struct ProgramUbuntuOneWatcher : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolUbuntuOneWatcher_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "UbuntuOneWatcher"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::ubuntuOneWatcher; }
  const std::string GetUrl() const noexcept { return "ToolUbuntuOneWatcher.htm"; }
};

struct ProgramVanDenBogaart : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "VanDenBogaart"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::vanDenBogaart; }
  const std::string GetUrl() const noexcept { return "ProjectVanDenBogaart.htm"; }
};

struct ProgramVirtualBastard : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "VirtualBastard"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::virtualBastard; }
  const std::string GetUrl() const noexcept { return "ToolVirtualBastard.htm"; }
};

struct ProgramVisualAbc : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolVisualAbc_1_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "VisualAbc"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::visualAbc; }
  const std::string GetUrl() const noexcept { return "ToolVisualAbc.htm"; }
};

struct ProgramXeNonZero : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "GameXeNonZero_0_1.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "XeNonZero"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::xeNonZero; }
  const std::string GetUrl() const noexcept { return "GameXeNonZero.htm"; }
};

struct ProgramZork : public RichelBilderbeek::ProgramGame
{
  const std::string GetFilenameConsole() const noexcept { return "GameZork.png"; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetScreenName() const noexcept { return "Zork"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::zork; }
  const std::string GetUrl() const noexcept { return "GameZork.htm"; }
};

/*




struct ProgramNewickVector : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetName() const { return "NewickVector"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::yes; }
  ProgramType GetType() const noexcept { return ProgramType::newickVector; }
  const std::string GetUrl() const noexcept { return "ProjectNewickVector.htm"; }
};


struct ProgramTwoDigitNewick : public RichelBilderbeek::ProgramProject
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetName() const { return "TwoDigitNewick"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::twoDigitNewick; }
  const std::string GetUrl() const noexcept { return "ProjectTwoDigitNewick.htm"; }
};






struct ProgramCreateSitemap : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetName() const { return "CreateSitemap"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::createSitemap; }
  const std::string GetUrl() const noexcept { return "ToolCreateSitemap.htm"; }
};


struct ProgramEncranger : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return ""; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return "ToolEncranger_1_0.png"; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetName() const { return "Encranger"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::encranger; }
  const std::string GetUrl() const noexcept { return "ToolEncranger.htm"; }
};

struct ProgramRichelBilderbeekNlSitemapGenerator : public RichelBilderbeek::ProgramTool
{
  const std::string GetFilenameConsole() const noexcept { return ""; }
  const std::string GetFilenameDesktop() const noexcept { return "ToolRichelbilderbeekNlSitemapGenerator_2_0.png"; }
  const std::string GetFilenameDesktopWindowsOnly() const noexcept { return ""; }
  const std::string GetFilenameWeb() const noexcept { return ""; }
  const std::string GetName() const { return "RichelBilderbeekNlSitemapGenerator"; }
  ProgramStatus GetStatusConsole() const noexcept { return ProgramStatus::no; }
  ProgramStatus GetStatusDesktopWindowsOnly() const noexcept { return ProgramStatus::nvr; }
  ProgramStatus GetStatusDesktop() const noexcept { return ProgramStatus::yes; }
  ProgramStatus GetStatusWebApplication() const noexcept { return ProgramStatus::no; }
  ProgramType GetType() const noexcept { return ProgramType::richelBilderbeekNlSitemapGenerator; }
  const std::string GetUrl() const noexcept { return "ToolRichelBilderbeekNlSitemapGenerator.htm"; }
};

*/

std::ostream& operator<<(std::ostream& os, const Program& p) noexcept;
bool operator<(const Program& lhs, const Program& rhs) noexcept;

} //~namespace RichelBilderbeek

} //~namespace ribi

#endif // RICHELBILDERBEEKPROGRAM_H
