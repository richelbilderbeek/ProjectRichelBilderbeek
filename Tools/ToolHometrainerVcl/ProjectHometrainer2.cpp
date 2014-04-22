//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormCorrect.cpp", FormCorrect);
USEFORM("UnitFormImage.cpp", FormImage);
USEFORM("UnitFormIncorrect.cpp", FormIncorrect);
USEFORM("UnitFormExample.cpp", FormExample);
USEFORM("UnitFormMain.cpp", FormMain);
USEFORM("UnitFormMenu.cpp", FormMenu);
USEFORM("UnitFormMultipleChoiceQuestion.cpp", FormMultipleChoiceQuestion);
USEFORM("UnitFormOpenQuestion.cpp", FormOpenQuestion);
USEFORM("UnitFormQuestion.cpp", FormQuestion);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Hometrainer 2";
                 Application->CreateForm(__classid(TFormMenu), &FormMenu);
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
