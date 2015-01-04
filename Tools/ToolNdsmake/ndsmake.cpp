//---------------------------------------------------------------------------
/*
ndsmake, tool to generate NDS makefile from Qt Creator project file
Copyright (C) 2010-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolNdsmake.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "ndsmake.h"

#include <fstream>

#include "fileio.h"
#include "qtcreatorprofile.h"
#pragma GCC diagnostic pop

ribi::Ndsmake::Ndsmake(const std::string filename)
  : m_command{CreateCommand()},
    m_proFile(new ribi::QtCreatorProFile(filename))
{

}

std::string ribi::Ndsmake::CreateCommand() const noexcept
{
  //Copy ProFile files to the needed folders
  std::string s
    = "cd .. ;"
    + std::string("mkdir ") + m_proFile->GetBuildDir() + "; "
    + "cd " + m_proFile->GetBuildDir() + "; "
    + "mkdir source; ";
  //Start copying all files
  {
    const std::size_t sz = m_proFile->GetHeaders().size();
    for (std::size_t i = 0; i!=sz; ++i)
    //BOOST_FOREACH(const std::string& f,m_proFile->GetHeaders())
    {
      const std::string f = m_proFile->GetHeaders()[i];
      s += std::string("cp ")
        + m_proFile->GetCurDirFull()
        + std::string("/")
        + f
        + std::string(" ")
        + m_proFile->GetBuildDirFull()
        + std::string("/source/")
        + f
        + std::string("; ");
    }
  }
  {
    const std::size_t sz = m_proFile->GetSources().size();
    for (std::size_t i = 0; i!=sz; ++i)
    //BOOST_FOREACH(const std::string& f,m_proFile->GetSources())
    {
      const std::string f = m_proFile->GetSources()[i];
      s += std::string("cp ")
        + m_proFile->GetCurDirFull()
        + std::string("/")
        + f
        + std::string(" ")
        + m_proFile->GetBuildDirFull()
        + std::string("/source/")
        + f
        + std::string("; ");
    }
  }
  return s;
}

void ribi::Ndsmake::CreateHolyMakefile() const noexcept
{
  std::ofstream f("Makefile");
  f
  << "#---------------------------------------------------------------------------------\n"
  << ".SUFFIXES:\n"
  << "#---------------------------------------------------------------------------------\n"
  << "\n"
  << "ifeq ($(strip $(DEVKITARM)),)\n"
  << "$(error \"Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM\")\n"
  << "endif\n"
  << "\n"
  << "include $(DEVKITARM)/ds_rules\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# TARGET is the name of the output\n"
  << "# BUILD is the directory where object files & intermediate files will be placed\n"
  << "# SOURCES is a list of directories containing source code\n"
  << "# INCLUDES is a list of directories containing extra header files\n"
  << "#---------------------------------------------------------------------------------\n"
  << "TARGET		:=	$(shell basename $(CURDIR))\n"
  << "BUILD		:=	build\n"
  << "SOURCES		:=	gfx source data  \n"
  << "INCLUDES	:=	include build /opt/devkitpro/libnds-1.4.7/include\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# options for code generation\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ARCH	:=	-mthumb -mthumb-interwork\n"
  << "\n"
  << "CFLAGS	:=	-g -Wall -O2\\\n"
  << " 			-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\\\n"
  << "			-ffast-math \\\n"
  << "			$(ARCH)\n"
  << "\n"
  << "CFLAGS	+=	$(INCLUDE) -DARM9\n"
  << "CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions\n"
  << "\n"
  << "ASFLAGS	:=	-g $(ARCH)\n"
  << "LDFLAGS	=	-specs=ds_arm9.specs -g $(ARCH) -mno-fpu -Wl,-Map,$(notdir $*.map)\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# any extra libraries we wish to link with the project\n"
  << "#---------------------------------------------------------------------------------\n"
  << "LIBS	:= -lnds9\n"
  << " \n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# list of directories containing libraries, this must be the top level containing\n"
  << "# include and lib\n"
  << "#---------------------------------------------------------------------------------\n"
  << "LIBDIRS	:=	$(LIBNDS)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# no real need to edit anything past this point unless you need to add additional\n"
  << "# rules for different file extensions\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ifneq ($(BUILD),$(notdir $(CURDIR)))\n"
  << "#---------------------------------------------------------------------------------\n"
  << " \n"
  << "export OUTPUT	:=	$(CURDIR)/$(TARGET)\n"
  << " \n"
  << "export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))\n"
  << "export DEPSDIR	:=	$(CURDIR)/$(BUILD)\n"
  << "\n"
  << "CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))\n"
  << "CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))\n"
  << "SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))\n"
  << "BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# use CXX for linking C++ projects, CC for standard C\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ifeq ($(strip $(CPPFILES)),)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	export LD	:=	$(CC)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "else\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	export LD	:=	$(CXX)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "endif\n"
  << "#---------------------------------------------------------------------------------\n"
  << "\n"
  << "export OFILES	:=	$(BINFILES:.bin=.o) \\\n"
  << "					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)\n"
  << " \n"
  << "export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \\\n"
  << "					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \\\n"
  << "					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \\\n"
  << "					-I$(CURDIR)/$(BUILD)\n"
  << " \n"
  << "export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)\n"
  << " \n"
  << ".PHONY: $(BUILD) clean\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "$(BUILD):\n"
  << "	@[ -d $@ ] || mkdir -p $@\n"
  << "	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "clean:\n"
  << "	@echo clean ...\n"
  << "	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).ds.gba \n"
  << " \n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "else\n"
  << " \n"
  << "DEPENDS	:=	$(OFILES:.o=.d)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# main targets\n"
  << "#---------------------------------------------------------------------------------\n"
  << "$(OUTPUT).nds	: 	$(OUTPUT).elf\n"
  << "$(OUTPUT).elf	:	$(OFILES)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "%.o	:	%.bin\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	@echo $(notdir $<)\n"
  << "	$(bin2o)\n"
  << " \n"
  << " \n"
  << "-include $(DEPENDS)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------------\n"
  << "endif\n"
  << "#---------------------------------------------------------------------------------------\n";
}

void ribi::Ndsmake::CreateMakefile(const QtCreatorProFile& p) const noexcept
{
  std::ofstream f("Makefile");
  f
  //Add header
  << "# ndsmake version 0.2\n"
  << "# by Richel Bilderbeek\n"
  << "# www.richelbilderbeek.nl\n"
  << "# Arguments: " << p.GetQtCreatorProFilename() << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << ".SUFFIXES:\n"
  << "#---------------------------------------------------------------------------------\n"
  //<< "DEVKITARM:=/opt/devkitpro/devkitARM\n" //Bilderbikkel addition
  //<< "DEVKITPRO:=/opt/devkitpro\n" //Bilderbikkel addition
  << "\n"
  << "ifeq ($(strip $(DEVKITARM)),)\n"
  << "$(error \"Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM\")\n"
  << "endif\n"
  << "\n"
  << "include $(DEVKITARM)/ds_rules\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# TARGET is the name of the output\n"
  << "# BUILD is the directory where object files & intermediate files will be placed\n"
  << "# SOURCES is a list of directories containing source code\n"
  << "# INCLUDES is a list of directories containing extra header files\n"
  << "#---------------------------------------------------------------------------------\n"
  << "TARGET := " << (*p.GetTarget().begin()) << "\n" //Bilderbikkel addition
  << "BUILD		:=	build\n"
  << "SOURCES		:=	gfx source data  \n"
  << "INCLUDES	:=	include build /usr/include /opt/devkitpro/libnds-1.4.7/include\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# options for code generation\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ARCH	:=	-mthumb -mthumb-interwork\n"
  << "\n"
  << "CFLAGS	:=	-g -Wall -O2\\\n"
  << " 			-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\\\n"
  << "			-ffast-math \\\n"
  << "			$(ARCH)\n"
  << "\n"
  << "CFLAGS	+=	$(INCLUDE) -DARM9\n"
  << "CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions\n"
  << "\n"
  << "ASFLAGS	:=	-g $(ARCH)\n"
  << "LDFLAGS	=	-specs=ds_arm9.specs -g $(ARCH) -mno-fpu -Wl,-Map,$(notdir $*.map)\n"
  << "\n"
  << "#---------------------------------------------------------------------------------\n"
  << "# any extra libraries we wish to link with the project\n"
  << "#---------------------------------------------------------------------------------\n"
  << "LIBS	:= -lnds9\n"
  << " \n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# list of directories containing libraries, this must be the top level containing\n"
  << "# include and lib\n"
  << "#---------------------------------------------------------------------------------\n"
  << "LIBDIRS	:=	$(LIBNDS)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# no real need to edit anything past this point unless you need to add additional\n"
  << "# rules for different file extensions\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ifneq ($(BUILD),$(notdir $(CURDIR)))\n"
  << "#---------------------------------------------------------------------------------\n"
  << " \n"
  << "export OUTPUT	:=	$(CURDIR)/$(TARGET)\n"
  << " \n"
  << "export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))\n"
  << "export DEPSDIR	:=	$(CURDIR)/$(BUILD)\n"
  << "\n"
  << "CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))\n"
  << "CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))\n"
  << "SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))\n"
  << "BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# use CXX for linking C++ projects, CC for standard C\n"
  << "#---------------------------------------------------------------------------------\n"
  << "ifeq ($(strip $(CPPFILES)),)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	export LD	:=	$(CC)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "else\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	export LD	:=	$(CXX)\n"
  << "#---------------------------------------------------------------------------------\n"
  << "endif\n"
  << "#---------------------------------------------------------------------------------\n"
  << "\n"
  << "export OFILES	:=	$(BINFILES:.bin=.o) \\\n"
  << "					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)\n"
  << " \n"
  << "export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \\\n"
  << "					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \\\n"
  << "					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \\\n"
  << "					-I$(CURDIR)/$(BUILD)\n"
  << " \n"
  << "export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)\n"
  << " \n"
  << ".PHONY: $(BUILD) clean\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "$(BUILD):\n"
  << "	@[ -d $@ ] || mkdir -p $@\n"
  << "	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "clean:\n"
  << "	@echo clean ...\n"
  << "	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).ds.gba \n"
  << " \n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "else\n"
  << " \n"
  << "DEPENDS	:=	$(OFILES:.o=.d)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "# main targets\n"
  << "#---------------------------------------------------------------------------------\n"
  << "$(OUTPUT).nds	: 	$(OUTPUT).elf\n"
  << "$(OUTPUT).elf	:	$(OFILES)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------\n"
  << "%.o	:	%.bin\n"
  << "#---------------------------------------------------------------------------------\n"
  << "	@echo $(notdir $<)\n"
  << "	$(bin2o)\n"
  << " \n"
  << " \n"
  << "-include $(DEPENDS)\n"
  << " \n"
  << "#---------------------------------------------------------------------------------------\n"
  << "endif\n"
  << "#---------------------------------------------------------------------------------------\n";
}

std::vector<std::string> ribi::Ndsmake::GetHelp() noexcept
{
  std::vector<std::string> v;
  v.push_back("Usage: ndsmake [options] [target]");
  v.push_back("");
  v.push_back("[target] must be the full path and filename of your Qt Creator project");
  v.push_back("for example: 'ndsmake /myqtfolder/myqtproject.pro'");
  v.push_back("");
  v.push_back("Options:");
  v.push_back("  --help: prints this message and exits");
  v.push_back("  --history: prints this ndsmake version history and exits");
  v.push_back("  --licence: prints the ndsmake licence and exits");
  v.push_back("  --version: print the current version of ndsmake and exits");
  return v;
}

std::vector<std::string> ribi::Ndsmake::GetHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2010-10-10: version 0.1: incomplete, could not be run from Qt Creator");
  v.push_back("2010-10-13: version 1.0: initial release, works from Qt Creator, tested by TestNdsmake");
  v.push_back("2010-12-19: version 1.1: added extra commands, use of ProFile class");
  v.push_back("2010-12-19: version 1.2: use of Ndsmake class");
  return v;
}

std::vector<std::string> ribi::Ndsmake::GetLicence() noexcept
{
  std::vector<std::string> v;
  v.push_back("ndsmake, tool to generate NDS makefile from Qt Creator project file");
  v.push_back("Copyright (C) 2010-2015 Richel Bilderbeek");
  v.push_back("");
  v.push_back("This program is free software: you can redistribute it and/or modify");
  v.push_back("it under the terms of the GNU General Public License as published by");
  v.push_back("the Free Software Foundation, either version 3 of the License, or");
  v.push_back("(at your option) any later version.");
  v.push_back("");
  v.push_back("This program is distributed in the hope that it will be useful,");
  v.push_back("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  v.push_back("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the");
  v.push_back("GNU General Public License for more details.");
  v.push_back("You should have received a copy of the GNU General Public License");
  v.push_back("along with this program.If not, see <http://www.gnu.org/licenses/>.");
  return v;
}

std::string ribi::Ndsmake::GetTarget() const noexcept
{
  assert(m_proFile);
  return m_proFile->GetTarget().empty()
    ? RemoveExtension( this->m_proFile->GetQtCreatorProFilename() )
    : (*m_proFile->GetTarget().begin());
}

std::string RemoveExtension(const std::string& filename)
{
  const int dot_index = filename.rfind(".",filename.size());
  assert(dot_index != -1 && "No dot found in filename");
  return filename.substr(0,dot_index);
}
