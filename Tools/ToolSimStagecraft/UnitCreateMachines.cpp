//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop
//---------------------------------------------------------------------------
#include "UnitFormCdPlayer.h"
#include "UnitFormDimblockV3.h"
#include "UnitFormEasyAmp.h"
#include "UnitFormMdPlayer.h"
#include "UnitFormOctlet.h"
#include "UnitFormPar64.h"
#include "UnitFormRcf322A.h"
#include "UnitFormRcfEvent3000.h"
#include "UnitFormShureSm58.h"
#include "UnitFormSimpleShine1.h"
#include "UnitFormSimpleShine2.h"
#include "UnitFormSimpleSound1.h"
#include "UnitFormSimpleSound2.h"
#include "UnitFormSimpleSound3.h"
#include "UnitFormSimpleSound4.h"
#include "UnitFormTransitionPieceJackMaleTwoCinchFemale.h"
#include "UnitFormTriplet.h"
#include "UnitFormWallSocket220.h"
#include "UnitFormWallSocketPower.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#include "UnitCreateMachines.h"
//---------------------------------------------------------------------------
std::vector<boost::shared_ptr<TFormMachine> > CreateMachines(
  TFormSimStagecraftMain * const formParent,
  const int level)
{
  std::vector<boost::shared_ptr<TFormMachine> > machines;

  switch (level)
  {
    case 1:
    {
      boost::shared_ptr<TFormMachine> m1(
          new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> m2(
          new TFormPar64(0,formParent));
      machines.push_back(m1);
      machines.push_back(m2);
    }
    break;
    case 2:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> mic(new TFormShureSm58(0,formParent));
      machines.push_back(mic);
      machines.push_back(speaker);
      machines.push_back(wallSocket220);
    }
    break;
    case 3:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> speaker2(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> mic(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> triplet(new TFormTriplet(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable(new TFormSimpleSound1(0,formParent));
      machines.push_back(speaker1);
      machines.push_back(mic);
      machines.push_back(speaker2);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable);
      machines.push_back(triplet);
    }
    break;
    case 4:
    {
      boost::shared_ptr<TFormMachine> dimmerpack(new TFormDimblockV3(0,formParent));
      boost::shared_ptr<TFormMachine> lighttable(new TFormSimpleShine1(0,formParent));
      boost::shared_ptr<TFormMachine> wallSocketPower(new TFormWallSocketPower(0,formParent));
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> par64_1(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_2(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_3(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_4(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_5(new TFormPar64(0,formParent));
      machines.push_back(wallSocketPower);
      machines.push_back(dimmerpack);
      machines.push_back(wallSocket220);
      machines.push_back(par64_1);
      machines.push_back(lighttable);
      machines.push_back(par64_2);
      machines.push_back(par64_3);
      machines.push_back(par64_4);
      machines.push_back(par64_5);
    }
    break;
    case 5:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> speaker2(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> mic1(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> mic2(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> triplet(new TFormTriplet(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable(new TFormSimpleSound2(0,formParent));
      machines.push_back(mic1);
      machines.push_back(triplet);
      machines.push_back(mic2);
      machines.push_back(speaker1);
      machines.push_back(soundTable);
      machines.push_back(speaker2);
      machines.push_back(wallSocket220);
    }
    break;
    case 6:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> mic1(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> triplet(new TFormTriplet(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable3(new TFormSimpleSound3(0,formParent));
      machines.push_back(mic1);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      machines.push_back(triplet);
      machines.push_back(soundTable3);
    }
    break;
    case 7:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> mic1(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> mic2(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> mic3(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> speaker2(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> speaker3(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> speaker4(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> octlet(new TFormOctlet(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable3(new TFormSimpleSound3(0,formParent));
      machines.push_back(mic1);
      machines.push_back(mic2);
      machines.push_back(mic3);
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(speaker2);
      machines.push_back(speaker3);
      machines.push_back(speaker4);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable3);
    }
    break;
    case 8:
    {
      //Put a CD on speakers without using a soundtable
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> octlet(new TFormOctlet(0,formParent));
      boost::shared_ptr<TFormCdPlayer> cdPlayer(new TFormCdPlayer(0,formParent));
      boost::shared_ptr<TFormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new TFormTransitionPieceJackMaleTwoCinchFemale(0,formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      machines.push_back(cdPlayer);
      machines.push_back(transitionPiece);
    }
    break;
    case 9:
    {
      //Put a CD on speakers with using a soundtable
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> octlet(new TFormOctlet(0,formParent));
      boost::shared_ptr<TFormCdPlayer> cdPlayer(new TFormCdPlayer(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable4(new TFormSimpleSound4(0,formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(cdPlayer);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable4);
    }
    break;
    case 10:
    {
      //Record a CD on MD play
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> octlet(new TFormOctlet(0,formParent));
      //boost::shared_ptr<TFormMachine> soundTable4(new TFormSimpleSound4(0,formParent));
      boost::shared_ptr<TFormMdPlayer> mdPlayer(new TFormMdPlayer(0,formParent));
      boost::shared_ptr<TFormCdPlayer> cdPlayer(new TFormCdPlayer(0,formParent));
      boost::shared_ptr<TFormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new TFormTransitionPieceJackMaleTwoCinchFemale(0,formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      //machines.push_back(soundTable4);
      machines.push_back(mdPlayer);
      machines.push_back(transitionPiece);
      machines.push_back(cdPlayer);
    }
    break;
    case 11:
    {
      //Record a CD and microphone on MD play
      boost::shared_ptr<TFormMachine> mic1(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> speaker1(new TFormRcf322A(0,formParent));
      boost::shared_ptr<TFormMachine> octlet(new TFormOctlet(0,formParent));
      boost::shared_ptr<TFormMachine> soundTable4(new TFormSimpleSound4(0,formParent));
      boost::shared_ptr<TFormMdPlayer> mdPlayer(new TFormMdPlayer(0,formParent));
      //boost::shared_ptr<TFormCdPlayer> cdPlayer(new TFormCdPlayer(0,formParent));
      boost::shared_ptr<TFormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new TFormTransitionPieceJackMaleTwoCinchFemale(0,formParent));
      machines.push_back(wallSocket220);
      machines.push_back(speaker1);
      machines.push_back(octlet);
      machines.push_back(mic1);
      machines.push_back(soundTable4);
      machines.push_back(transitionPiece);
      //machines.push_back(cdPlayer);
      machines.push_back(mdPlayer);
    }
    break;
    case 12:
    {
      //Level 12: Learn to use the crossfader
      boost::shared_ptr<TFormMachine> dimmerpack(new TFormDimblockV3(0,formParent));
      boost::shared_ptr<TFormMachine> lighttable(new TFormSimpleShine2(0,formParent));
      boost::shared_ptr<TFormMachine> wallSocketPower(new TFormWallSocketPower(0,formParent));
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> par64_1(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_2(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_3(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_4(new TFormPar64(0,formParent));
      boost::shared_ptr<TFormMachine> par64_5(new TFormPar64(0,formParent));
      machines.push_back(wallSocketPower);
      machines.push_back(dimmerpack);
      machines.push_back(wallSocket220);
      machines.push_back(par64_1);
      machines.push_back(lighttable);
      machines.push_back(par64_2);
      machines.push_back(par64_3);
      machines.push_back(par64_4);
      machines.push_back(par64_5);
    }
    break;
    case 13:
    {
      boost::shared_ptr<TFormMachine> wallSocket220(new TFormWallSocket220(0,formParent));
      boost::shared_ptr<TFormMachine> mic(new TFormShureSm58(0,formParent));
      boost::shared_ptr<TFormMachine> speaker(new TFormRcfEvent3000(0,formParent));
      boost::shared_ptr<TFormMachine> amplifier(new TFormEasyAmp(0,formParent));
      machines.push_back(mic);
      machines.push_back(speaker);
      machines.push_back(wallSocket220);
      machines.push_back(amplifier);
    }
    break;
    default: //Do nothing
    break;
  }

  return machines;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
