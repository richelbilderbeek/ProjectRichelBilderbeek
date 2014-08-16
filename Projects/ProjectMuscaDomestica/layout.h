//Layout.h

//function showing proportions in every generation on RichEdit
void ShowOnRichEdit(TRichEdit *output, int i, int r, TChart * Chart1)     //i-generation, r-run
{
//NIKS
}


//InitializeParameters(ValueListEditor1,
//                     RadioGroupDispersingSex->ItemIndex,
//                     RadioGroupWhoIsInControl->ItemIndex
//                     RichEditOutput, Chart1);

void InitializeParameters(TValueListEditor * ValueListEditor1,
                          int WhoDisperses,
                          int WhoIsInControl,
                          TRichEdit * RichEditOutput,
                          TChart * Chart1)
  {
  NIslands=ValueListEditor1->Cells[1][1].ToIntDef(0);
  MaxFPopSize=ValueListEditor1->Cells[1][2].ToIntDef(0);
  MaxMPopSize=ValueListEditor1->Cells[1][3].ToIntDef(0);
  NGenerations=ValueListEditor1->Cells[1][4].ToIntDef(0);
  NRuns=ValueListEditor1->Cells[1][5].ToIntDef(0);
  PMut=ValueListEditor1->Cells[1][6].ToDouble();
  CalculateStdDevTime=ValueListEditor1->Cells[1][7].ToIntDef(0);
  if (CalculateStdDevTime<NGenerations) CalculateStdDevTime=NGenerations/10;
  ValueListEditor1->Cells[1][7]=CalculateStdDevTime;
  String info="Number of islands: ";
  info+=IntToStr(NIslands);
  info+="\nNumber of females on island: ";
  info+=IntToStr(MaxFPopSize);
  info+="\nNumber of males on island: ";
  info+=IntToStr(MaxMPopSize);
  info+="\nNumber of generations: ";
  info+=IntToStr(NGenerations);
  info+="\nPMut: ";
  info+=(String)PMut;
  switch (WhoDisperses)
    {
    case 0 : //Males disperse
             NextGeneration=NextGenerationMales;
             info+="\nDispersing sex: males";
             break;
    case 1 : //Females disperse
             NextGeneration=NextGenerationFemales;
             info+="\nDispersing sex: females";
             break;
    case 2 : //Both disperse
             NextGeneration=NextGenerationBoth;
             info+="\nDispersing sex: both";
             break;
    default : ShowMessage("Option not possible!"); exit(1);
    }
  switch (WhoIsInControl)
    {
    case 0 : //Father
             CreateOffspring=CreateOffspringFather;
             info+="\nfather is in control";
             break;
    case 1 : //Mother
             CreateOffspring=CreateOffspringMother;
             info+="\nmother is in control";
             break;
    case 2 : //Both
             CreateOffspring=CreateOffspringBoth;
             info+="\nboth are in control";
             break;
    case 3 : //Zygote
             CreateOffspring=CreateOffspringBoth;
             info+="\nzygote is in control";
             break;
    default : ShowMessage("Option not possible!"); exit(1);
    }

  #ifdef FIRSTDISPERSE
    info+="\nDispersing first";
  #endif
  #ifdef FIRSTMATE
    info+="\nMating first";
  #endif
  info+="\nCalculateStdDevTime: ";
  info+=IntToStr(CalculateStdDevTime);
  RichEditOutput->Lines->Clear();
  RichEditOutput->Lines->Add(info);
    //RichEditOutput->Lines->Add("Run \t Generation \t Male % \t X % \t Y % \t Xm % \t FD % \t M1 % \t M2 % \t M3 % \t M5 % \n");
    //RichEditOutput->Lines->Add("Run \t Generation \t Male % \t X % \t Y % \t Xm % \t FD % \t M1 % \t M2 % \t M3 % \t M5 % \n");
  }


void ShowOnChart (TChart * Chart1,int Generation, TImage * ImageMale, TImage * ImageFemale, TImage * ImageResult)
{
assert(FPop.size()+MPop.size()==(NIslands*(MaxMPopSize+MaxFPopSize)));
double ResultValue=0.5*SLocusCounter/ (double)(NIslands*(MaxMPopSize+MaxFPopSize));
Morpher(ImageMale,ImageFemale,ImageResult,ResultValue);
Chart1->BackImage->Graphic=ImageResult->Picture->Graphic;
Chart1->Series[0]->AddY(ResultValue,
                        "",Chart1->Series[0]->SeriesColor);
OurDataSet[Generation]=ResultValue;
}

void EmptyTotalChart(TChart * Chart1)
  {
  int counter; for (counter=0; counter < Chart1->SeriesCount(); counter++)
    {
    Chart1->Series[counter]->Clear();
    }//Next counter
  }//End of: EmptyTotalChart

//saves results from chosen RichEdit
void SeveResults (TRichEdit *Edit, TRadioGroup * RadioGroupDispersingSex)
{
    String name="results_";

    #ifdef MALESDISPERSE
      name+="m_";
    #endif

    #ifdef FEMALESDISPERSE
      name+="f_";
    #endif
    name+=IntToStr(NIslands);
    name+="i_";
    name+=IntToStr(MaxMPopSize);
    name+="m_";
    name+=IntToStr(MaxFPopSize);
    name+="f_";
    name+=IntToStr(NGenerations);
    name+="g.doc";
    Form1->Save1->FileName=name;
    Form1->Save1->Execute();
    if(Form1->Save1->FileName!="")
    {
        Edit->Lines->SaveToFile(Form1->Save1->FileName);
    }
}

/*void UpStartScreenLayout(TRichEdit * output,TRichEdit * runsOutput,TRadioGroup * DispersingSex, TChart * Chart1)
  {
  //Put info about simulation into RichEdit objects
  String info;
  info ="Number of islands: "+IntToStr(NIslands);
  info+="\nNumber of females on island: "+IntToStr(MaxFPopSize);
  info+="\nNumber of males on island: "+IntToStr(MaxMPopSize);
  info+="\nNumber of generations: "+IntToStr(NGenerations);
  if(DispersingSex->ItemIndex==0) { info+="\nDispersing sex: males"; }
    else { info+="\nDispersing sex: females"; }
  info+="\n";
  output->Lines->Clear();
  output->Lines->Add(info);
  output->Lines->Add("Run \t Generation \t Male % \t X % \t Y % \t Xm % \t FD % \t M1 % \t M2 % \t M3 % \t M5 % \n");
  runsOutput->Lines->Clear();
  runsOutput->Lines->Add(info);
  runsOutput->Lines->Add("Run \t Generation \t Male % \t X % \t Y % \t Xm % \t FD % \t M1 % \t M2 % \t M3 % \t M5 % \n");
  Chart1->BottomAxis->Maximum=NGenerations;
  }*/

