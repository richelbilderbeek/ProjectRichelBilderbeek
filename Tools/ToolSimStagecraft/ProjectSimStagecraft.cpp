//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormCdPlayer.cpp", FormCdPlayer);
USEFORM("UnitFormDimblockV3.cpp", FormDimblockV3);
USEFORM("UnitFormEasyAmp.cpp", FormEasyAmp);
USEFORM("UnitFormMachine.cpp", FormMachine);
USEFORM("UnitFormMdPlayer.cpp", FormMdPlayer);
USEFORM("UnitFormOctlet.cpp", FormOctlet);
USEFORM("UnitFormPar64.cpp", FormPar64);
USEFORM("UnitFormRcf322A.cpp", FormRcf322A);
USEFORM("UnitFormRcfEvent3000.cpp", FormRcfEvent3000);
USEFORM("UnitFormShureSm58.cpp", FormShureSm58);
USEFORM("UnitFormSimpleShine1.cpp", FormSimpleShine1);
USEFORM("UnitFormSimpleShine2.cpp", FormSimpleShine2);
USEFORM("UnitFormSimpleSound1.cpp", FormSimpleSound1);
USEFORM("UnitFormSimpleSound2.cpp", FormSimpleSound2);
USEFORM("UnitFormSimpleSound3.cpp", FormSimpleSound3);
USEFORM("UnitFormSimpleSound4.cpp", FormSimpleSound4);
USEFORM("UnitFormSimStagecraftAbout.cpp", FormSimStagecraftAbout);
USEFORM("UnitFormSimStagecraftMain.cpp", FormSimStagecraftMain);
USEFORM("UnitFormSimStagecraftMenu.cpp", FormSimStagecraftMenu);
USEFORM("UnitFormSimStagecraftOtherLicences.cpp", FormSimStagecraftOtherLicences);
USEFORM("UnitFormSimStagecraftSelect.cpp", FormSimStagecraftSelect);
USEFORM("UnitFormSimStagecraftWhatsNew.cpp", FormSimStagecraftWhatsNew);
USEFORM("UnitFormSprites.cpp", FormSprites);
USEFORM("UnitFormTransitionPieceJackMaleTwoCinchFemale.cpp", FormTransitionPieceJackMaleTwoCinchFemale);
USEFORM("UnitFormTriplet.cpp", FormTriplet);
USEFORM("UnitFormWallSocket220.cpp", FormWallSocket220);
USEFORM("UnitFormWallSocketPower.cpp", FormWallSocketPower);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SimStagecraft";
                 Application->CreateForm(__classid(TFormSimStagecraftMenu), &FormSimStagecraftMenu);
                 Application->CreateForm(__classid(TFormSprites), &FormSprites);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
