//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormAboutTheAuthor.cpp", FormAboutTheAuthor);
USEFORM("UnitFormParameters.cpp", FormParameters);
USEFORM("UnitFormResults.cpp", FormResults);
USEFORM("UnitFormTest.cpp", FormTest);
USEFORM("UnitMain.cpp", FormThorVeenProject);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "The Thor Veen Project";
                 Application->HelpFile = "C:\\Program Files\\Borland\\CBuilder6\\Projects\\Simulations\\ThorVeen\\7\\PROJECTHELP.HLP";
     Application->CreateForm(__classid(TFormThorVeenProject), &FormThorVeenProject);
                 Application->CreateForm(__classid(TFormResults), &FormResults);
                 Application->CreateForm(__classid(TFormParameters), &FormParameters);
                 Application->CreateForm(__classid(TFormTest), &FormTest);
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
