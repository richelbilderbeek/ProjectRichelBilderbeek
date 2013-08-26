//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop
USEFORM("UnitFormImageRotaterClx.cpp", FormImageRotaterClx);
USEFORM("UnitFormAboutClx.cpp", FormAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "The Image Rotater";
                 Application->CreateForm(__classid(TFormImageRotaterClx), &FormImageRotaterClx);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch(...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch(Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
