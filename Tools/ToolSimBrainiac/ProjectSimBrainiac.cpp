//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSimBrainiacMain.cpp", FormSimBrainiacMain);
USEFORM("UnitFormSimBrainiacMenu.cpp", FormSimBrainiacMenu);
USEFORM("UnitFormSimBrainiacGraph.cpp", FormSimBrainiacGraph);
USEFORM("UnitFormSimBrainiacManual.cpp", FormSimBrainiacManual);
USEFORM("UnitFormSimBrainiacAbout.cpp", FormSimBrainiacAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SimBrainiac";
                 Application->CreateForm(__classid(TFormSimBrainiacMenu), &FormSimBrainiacMenu);
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
