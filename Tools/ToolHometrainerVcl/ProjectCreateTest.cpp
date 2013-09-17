//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormCreateTest.cpp", FormCreateTest);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
USEFORM("UnitFormExample.cpp", FormExample);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Hometrainer 2 Test Creater";
                 Application->CreateForm(__classid(TFormCreateTest), &FormCreateTest);
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
