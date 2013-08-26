//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitTransitionPiece.h"
//---------------------------------------------------------------------------
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
TransitionPieceJackMaleTwoCinchFemale::TransitionPieceJackMaleTwoCinchFemale()
  : mJack(boost::shared_ptr<JackMale>(new JackMale(this))),
    mCinchL(boost::shared_ptr<CinchWhiteFemale>(new CinchWhiteFemale(this))),
    mCinchR(boost::shared_ptr<CinchRedFemale>(new CinchRedFemale(this)))
{

}
//---------------------------------------------------------------------------
const double TransitionPieceJackMaleTwoCinchFemale::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  if (connector == mJack.get() )
  {
    const Connector * const inputL = this->mCinchL->GetConnectedTo();

    double audioInputL = 0.0;
    if (inputL != 0
      && std::find(prevConnectors.begin(),prevConnectors.end(),inputL)
        == prevConnectors.end())
    {
      //Correct connection
      const Machine * const inputMachine = inputL->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      audioInputL = inputMachine->AudioSignalStrength(inputL,prevConnectors);
    }

    const Connector * const inputR = this->mCinchR->GetConnectedTo();

    double audioInputR = 0.0;
    if (inputR != 0
      && std::find(prevConnectors.begin(),prevConnectors.end(),inputR)
        == prevConnectors.end())
    {
      //Correct connection
      const Machine * const inputMachine = inputR->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      audioInputL = inputMachine->AudioSignalStrength(inputR,prevConnectors);
    }
    return std::max(audioInputL,audioInputR);
  }
  else
  {
    assert(connector == mCinchL.get() || connector == mCinchR.get());

    const Connector * const input = this->mJack->GetConnectedTo();
    if (input != 0
      && std::find(prevConnectors.begin(),prevConnectors.end(),input)
        == prevConnectors.end())
    {
      //Correct connection
      const Machine * const inputMachine = input->mBelongsTo;
      assert(inputMachine != 0);
      prevConnectors.push_back(connector); //We just checked connector...
      const double audioInput
        = inputMachine->AudioSignalStrength(input,prevConnectors);
      return audioInput;
    }
    else
    {
      return 0.0;
    }
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
