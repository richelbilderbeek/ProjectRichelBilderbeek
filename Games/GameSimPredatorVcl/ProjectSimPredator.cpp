//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitHunting.cpp", FormHunting);
USEFORM("UnitMenu.cpp", FormMenu);
USEFORM("UnitChart.cpp", FormChart);
USEFORM("UnitStartHunt.cpp", FormStartHunt);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SimPredator";
                 Application->CreateForm(__classid(TFormMenu), &FormMenu);
                 Application->CreateForm(__classid(TFormStartHunt), &FormStartHunt);
                 Application->CreateForm(__classid(TFormChart), &FormChart);
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
