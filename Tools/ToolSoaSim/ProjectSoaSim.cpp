//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSoaSimMain.cpp", FormSoaSimMain);
USEFORM("UnitFormSoaSimControl.cpp", FormSoaSimControl);
USEFORM("UnitFormSoaSimChart.cpp", FormSoaSimChart);
USEFORM("UnitFormSoaSimAdd.cpp", FormSoaSimAddPerson);
USEFORM("UnitFormSoaSimAbout.cpp", FormSoaSimAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SoaSim";
                 Application->CreateForm(__classid(TFormSoaSimControl), &FormSoaSimControl);
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
