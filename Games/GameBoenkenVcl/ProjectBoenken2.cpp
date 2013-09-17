//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormBoenken2Game.cpp", FormBoenken2Game);
USEFORM("UnitFormBoenken2Menu.cpp", FormBoenken2Menu);
USEFORM("UnitFormBoenken2PressKey.cpp", FormBoenken2PressKey);
USEFORM("UnitFormBoenken2About.cpp", FormBoenken2About);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Boenken 2";
                 Application->CreateForm(__classid(TFormBoenken2Menu), &FormBoenken2Menu);
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
