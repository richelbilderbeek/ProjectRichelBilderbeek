//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormPrimeExpert.cpp", FormPrimeExpert);
USEFORM("UnitFormPrimeExpertAbout.cpp", FormPrimeExpertAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "PrimeExpert";
                 Application->CreateForm(__classid(TFormPrimeExpert), &FormPrimeExpert);
                 Application->CreateForm(__classid(TFormPrimeExpertAbout), &FormPrimeExpertAbout);
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
