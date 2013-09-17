//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormCreateDoc.cpp", FormCreateDoc);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
USEFORM("UnitFormExample.cpp", FormExample);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Hometrainer 2 CreateDoc";
                 Application->CreateForm(__classid(TFormCreateDoc), &FormCreateDoc);
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
