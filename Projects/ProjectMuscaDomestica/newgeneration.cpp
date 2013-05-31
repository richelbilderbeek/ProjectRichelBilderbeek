#include "newgeneration.h"

//Dispersingfirst.h
void NewGeneration1 (vector <Fly> &OffdispersingSex, vector <Fly> &OffnondispersingSex,
                    vector <Fly> &dispersingSex, vector <Fly> &nondispersingSex,
                    vector <int> &dSexOnIsland, vector <int> &ndSexOnIsland,
                    vector <int> &OffdSexOnIsland, vector <int> &OffndSexOnIsland,
                    int MaxDsex, int MaxNDsex)

{
int Kid, LuckyFly, OurIsland, fliesBefore=0, OffFliesBefore=0;
vector<Fly>::iterator iBiginning=OffdispersingSex.begin();

//non-dispersing sex stays on the some island as mothers
for(OurIsland=0;OurIsland<NIslands;OurIsland++)                                   //for every island
  {
  if(OurIsland>0)
    { //check how many offspring flies are on previous islands
    //OffFliesBefore are Non-dispers
    fliesBefore+=ndSexOnIsland[OurIsland-1];
    }//End of: if(OurIsland>0)

  //Offspring of the non-dispersing sex
  //ShowMessage(ndSexOnIsland.
  if(OffndSexOnIsland[OurIsland]<=MaxNDsex) //Als het eiland nog niet vol is, dan...
    { //if there are less or the same numer of offspring as the carrying capacity of the island
    for(Kid=0;Kid<ndSexOnIsland[OurIsland];Kid++)
      { //for every offspring fly moves then to the next generation
      //********************************** Shouldn't the OffnondispersingSex vector be emptied first"
      OffnondispersingSex.push_back(nondispersingSex[fliesBefore+Kid]);
      }
    //ShowMessage(OffndSexOnIsland.size());
    OffndSexOnIsland[OurIsland]=ndSexOnIsland[OurIsland]; //number of flies in the new generation equals number of offspring
    }  //End of: if(ndSexOnIsland[OurIsland]<=MaxNDsex)
    else
    { //if there are more offspring than carrying capacity of the island
    for(Kid=0;Kid<MaxNDsex;Kid++)
      { //for every place on the island
      //takes random fly from offspring on that island
      LuckyFly=RandomNumber(ndSexOnIsland[OurIsland]);
      //and moves it to the next generation
      OffnondispersingSex.push_back(nondispersingSex[fliesBefore+LuckyFly]);
      //moves last fly from the island
      nondispersingSex[fliesBefore+LuckyFly]=nondispersingSex[fliesBefore+ndSexOnIsland[OurIsland]-1];
      ndSexOnIsland[OurIsland]--;
      }//Next Kid
    //counts original number of offspring flies on island
    ndSexOnIsland[OurIsland]+=MaxNDsex; //?????
    //number of flies in new generatin equals carrying capacity
    OffndSexOnIsland[OurIsland]=MaxNDsex;
    }
  }//Next OurIslands

//dispersing sex
int island=0;
fliesBefore=0;
int dSexCounter=dispersingSex.size();
if((int)dispersingSex.size()>=MaxDsex*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxDsex;Kid++)
      { //for every place on island
      do
        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(dSexCounter);
        }
      while
        (dispersingSex[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      dispersingSex[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      OffdispersingSex.push_back(dispersingSex[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      dispersingSex[LuckyFly]=dispersingSex[dSexCounter-1];
      //size of offspring population decreases by one
      dSexCounter--;
      }//Next Kid
    OffdSexOnIsland[OurIsland]=MaxDsex;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<dSexCounter;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((OffdSexOnIsland[island]>=MaxDsex || OffdispersingSex[Kid].Island==island) && n<dSexCounter);
    //CAUTION!! An island might get overcrowded!!
    if (OffdispersingSex[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore+=OffdSexOnIsland[AlsoAnIsland];
      }//Next AlsoAnIsland
    dispersingSex[Kid].Island=island;
    //adds fly to the next generation
    OffdispersingSex.insert(iBiginning+fliesBefore,dispersingSex[Kid]);
    OffdSexOnIsland[island]++;
    }//Next Kid

  }

//setting sizes of offspring subpopulations to 0
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  ndSexOnIsland[OurIsland]=0;
  dSexOnIsland[OurIsland]=0;
  }//next OurIsland
//offspring populations resized to zero
nondispersingSex.resize(0);
dispersingSex.resize(0);
}//End of: NewGeneration

//Every female mates with one randomly chosen male from her island and gives offspring
//males can be chosen several times



//Every female mates with one randomly chosen male from her island and gives offspring
//males can be chosen several times






void Mating2 (TRadioGroup * RadioGroup1)
{
int FemaleFly,Kid,OurIsland, mate, offNum;
Fly tempFly;
int FfliesBefore=0;
int MfliesBefore=0;
int FOffFliesBefore=0;
int MOffFliesBefore=0;
for(OurIsland=0;OurIsland<NIslands;OurIsland++)         //for evey island
  {
  if (OurIsland>0) //Is it NOT the first island, then...
    {
    //counts how many flies and offspring in sum are on island with lower numbers
    FfliesBefore+=NFOffFlyOnIsland[OurIsland-1];
    MfliesBefore+=NMOffFlyOnIsland[OurIsland-1];
    FOffFliesBefore+=NFFlyOnIsland[OurIsland-1];
    MOffFliesBefore+=NMFlyOnIsland[OurIsland-1];
    }

    NFFlyOnIsland.push_back(0);
    NMFlyOnIsland.push_back(0);

  for(FemaleFly=0;FemaleFly<NFOffFlyOnIsland[OurIsland];FemaleFly++)     //for every female on island
    {
    //Select a random mate-> mate='male number'
    mate=RandomNumber(NMFlyOnIsland[OurIsland]); //number of male partner

    for(Kid=0;Kid<10*(MaxFPopSize+MaxMPopSize)/NFFlyOnIsland[OurIsland];Kid++)                                              //creation of 10 offspring
      {
        //Inheriting SLocus of parents
        int AlleleMother, AlleleFather;
        AlleleMother=RandomNumber(2); // and which allele of parent will be taken
        AlleleFather=RandomNumber(2); // this is done for every "chromosome"
        tempFly.SLocus[0] = FPop[FfliesBefore+FemaleFly].SLocus[AlleleMother];
        tempFly.SLocus[1] = MPop[MfliesBefore+mate].SLocus[AlleleFather];
        //if(Uniform()<PMut) //if the mutation occure
        //if (1)
        //  {
          int OneSLocus=RandomNumber(2);  //for which locus it will occure
          tempFly.SLocus[OneSLocus] += ((Uniform()*PMut)-(0.5*PMut));
        //  }

        //Keep track of S in the population
        SumS+= ((tempFly.SLocus[0]+tempFly.SLocus[1])/2.0);
        FliesCheckedForS++;

        //Putting offspring on right island
        tempFly.Island=OurIsland;

        //Determining offspring's sex
        double ChanceOffspringIsMale=-1.0;
        switch(RadioGroup1->ItemIndex)
          {
          case 0: //If mother is in control....
                  ChanceOffspringIsMale = (FPop[FfliesBefore+FemaleFly].SLocus[0]
                                         +FPop[FfliesBefore+FemaleFly].SLocus[1])/2.0;
                  break;
          case 1: //If father is in control...
                  ChanceOffspringIsMale = (MPop[MfliesBefore+mate].SLocus[0]
                                         +MPop[MfliesBefore+mate].SLocus[1])/2.0;
                  break;
          case 2: //If both are in control...
                  ChanceOffspringIsMale = (FPop[FfliesBefore+FemaleFly].SLocus[0]
                                         +FPop[FfliesBefore+FemaleFly].SLocus[1]
                                         +MPop[MfliesBefore+mate].SLocus[0]
                                         +MPop[MfliesBefore+mate].SLocus[1])/4.0;
                  break;
          case 3: //If genotype offspring is in control...
                  ChanceOffspringIsMale = (tempFly.SLocus[0]+tempFly.SLocus[1])/2.0;
                  break;
          }//End of: switch (RadioGroup1->Index)
       if (Uniform() < ChanceOffspringIsMale) //A male is born
         {
         tempFly.sex=male;
         MPop.push_back(tempFly);
         NMFlyOnIsland[OurIsland]++;
         maleCounter++;
         }
       else
         {
         tempFly.sex=female;
         FPop.push_back(tempFly);                    //puts new fly on the end of the female offspring vector
         NFFlyOnIsland[OurIsland]++;
         femaleCounter++;
         }
        /*
        tempFly.SexChrom[0]=FPop[FfliesBefore+FemaleFly].SexChrom[AlleleMother];
          if(tempFly.SexChrom[0]==X) {Xcounter++;}              //X,Y,Xm counting
            else {if(tempFly.SexChrom[0]==Y) {Ycounter++;}
                    else {Xmcounter++;}}
        tempFly.SexChrom[1]=MPop[MfliesBefore+mate].SexChrom[AlleleFather];
          if(tempFly.SexChrom[1]==X) {Xcounter++;}              //X,Y,Xm counting
            else {if(tempFly.SexChrom[1]==Y) {Ycounter++;}
                    else {Xmcounter++;}}

        AlleleMother=RandomNumber(2);
        AlleleFather=RandomNumber(2);
        tempFly.Fautosome[0]=FPop[FfliesBefore+FemaleFly].Fautosome[AlleleMother];
          if(tempFly.Fautosome[0]==F) {Fcounter++;}
          else {FDcounter++;}
        tempFly.Fautosome[1]=MPop[MfliesBefore+mate].Fautosome[AlleleFather];
          if(tempFly.Fautosome[1]==F) {Fcounter++;}
          else {FDcounter++;}

        AlleleMother=RandomNumber(2);
        AlleleFather=RandomNumber(2);
        tempFly.Mautosome1[0]=FPop[FfliesBefore+FemaleFly].Mautosome1[AlleleMother];
          if(tempFly.Mautosome1[0]==O) {mO1counter++;}
          else {M1counter++;}
        tempFly.Mautosome1[1]=MPop[MfliesBefore+mate].Mautosome1[AlleleFather];
          if(tempFly.Mautosome1[1]==O) {mO1counter++;}
          else {M1counter++;}

          AlleleMother=RandomNumber(2);
        AlleleFather=RandomNumber(2);
        tempFly.Mautosome2[0]=FPop[FfliesBefore+FemaleFly].Mautosome2[AlleleMother];
          if(tempFly.Mautosome2[0]==O) {mO2counter++;}
          else {M2counter++;}
        tempFly.Mautosome2[1]=MPop[MfliesBefore+mate].Mautosome2[AlleleFather];
          if(tempFly.Mautosome2[1]==O) {mO2counter++;}
          else {M2counter++;}

          AlleleMother=RandomNumber(2);
        AlleleFather=RandomNumber(2);
        tempFly.Mautosome3[0]=FPop[FfliesBefore+FemaleFly].Mautosome3[AlleleMother];
          if(tempFly.Mautosome3[0]==O) {mO3counter++;}
          else {M3counter++;}
        tempFly.Mautosome3[1]=MPop[MfliesBefore+mate].Mautosome3[AlleleFather];
          if(tempFly.Mautosome3[1]==O) {mO3counter++;}
          else {M3counter++;}

          AlleleMother=RandomNumber(2);
        AlleleFather=RandomNumber(2);
        tempFly.Mautosome5[0]=FPop[FfliesBefore+FemaleFly].Mautosome5[AlleleMother];
          if(tempFly.Mautosome5[0]==O) {mO5counter++;}
          else {M5counter++;}
        tempFly.Mautosome5[1]=MPop[MfliesBefore+mate].Mautosome5[AlleleFather];
          if(tempFly.Mautosome5[1]==O) {mO5counter++;}
          else {M5counter++;} */
            //tempFly.Island=OurIsland;

            /*
            if(Uniform()<PMut)                    //if the mutation occure
            {
                int locus=RandomNumber(12);          //for which locus it will occure
                int all=0;

                switch(locus)
                {
                    case 0: do {all=RandomNumber(3);}
                            while((SEXCHROM) all==tempFly.SexChrom[0]);
                            if(tempFly.SexChrom[0]==X) Xcounter--;
                            else
                            {if(tempFly.SexChrom[0]==Y) Ycounter--;
                                else Xmcounter--;}
                            tempFly.SexChrom[0]=SEXCHROM(all);
                            if(tempFly.SexChrom[0]==X) Xcounter++;
                            else
                            {if(tempFly.SexChrom[0]==Y) Ycounter++;
                                else Xmcounter++;}
                            break;
                    case 1: do {all=RandomNumber(3);}
                            while((SEXCHROM) all==tempFly.SexChrom[1]);
                            if(tempFly.SexChrom[1]==X) Xcounter--;
                            else
                            {if(tempFly.SexChrom[1]==Y) Ycounter--;
                                else Xmcounter--;}
                            tempFly.SexChrom[1]=SEXCHROM(all);
                            if(tempFly.SexChrom[1]==X) Xcounter++;
                            else
                            {if(tempFly.SexChrom[1]==Y) Ycounter++;
                                else Xmcounter++;}
                            break;
                    case 2: do {all=RandomNumber(2);}
                            while((FAUTOSOME) all==tempFly.Fautosome[0]);
                            if(tempFly.Fautosome[0]==F) Fcounter--;
                            else FDcounter--;
                            tempFly.Fautosome[0]=FAUTOSOME(all);
                            if(tempFly.Fautosome[0]==F) Fcounter++;
                            else FDcounter++;
                            break;
                    case 3: do {all=RandomNumber(2);}
                            while((FAUTOSOME) all==tempFly.Fautosome[1]);
                            if(tempFly.Fautosome[1]==F) Fcounter--;
                            else FDcounter--;
                            tempFly.Fautosome[1]=FAUTOSOME(all);
                            if(tempFly.Fautosome[1]==F) Fcounter++;
                            else FDcounter++;
                            break;
                    case 4: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome1[0]);
                            if(tempFly.Mautosome1[0]==O) mO1counter--;
                            else M1counter--;
                            tempFly.Mautosome1[0]=MAUTOSOME(all);
                            if(tempFly.Mautosome1[0]==O) mO1counter++;
                            else M1counter++;
                            break;
                    case 5: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome1[1]);
                            if(tempFly.Mautosome1[1]==O) mO1counter--;
                            else M1counter--;
                            tempFly.Mautosome1[1]=MAUTOSOME(all);
                            if(tempFly.Mautosome1[1]==O) mO1counter++;
                            else M1counter++;
                            break;
                    case 6: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome2[0]);
                            if(tempFly.Mautosome2[0]==O) mO2counter--;
                            else M2counter--;
                            tempFly.Mautosome2[0]=MAUTOSOME(all);
                            if(tempFly.Mautosome2[0]==O) mO2counter++;
                            else M2counter++;
                            break;
                    case 7: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome2[1]);
                            if(tempFly.Mautosome2[1]==O) mO2counter--;
                            else M2counter--;
                            tempFly.Mautosome2[1]=MAUTOSOME(all);
                            if(tempFly.Mautosome2[1]==O) mO2counter++;
                            else M2counter++;
                            break;
                    case 8: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome3[0]);
                            if(tempFly.Mautosome3[0]==O) mO3counter--;
                            else M3counter--;
                            tempFly.Mautosome3[0]=MAUTOSOME(all);
                            if(tempFly.Mautosome3[0]==O) mO3counter++;
                            else M3counter++;
                            break;
                    case 9: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome3[1]);
                            if(tempFly.Mautosome3[1]==O) mO3counter--;
                            else M3counter--;
                            tempFly.Mautosome3[1]=MAUTOSOME(all);
                            if(tempFly.Mautosome3[1]==O) mO3counter++;
                            else M3counter++;
                            break;
                    case 10: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome5[0]);
                            if(tempFly.Mautosome5[0]==O) mO5counter--;
                            else M5counter--;
                            tempFly.Mautosome5[0]=MAUTOSOME(all);
                            if(tempFly.Mautosome5[0]==O) mO5counter++;
                            else M5counter++;
                            break;
                    case 11: do {all=RandomNumber(2);}
                            while((MAUTOSOME) all==tempFly.Mautosome5[1]);
                            if(tempFly.Mautosome5[1]==O) mO5counter--;
                            else M5counter--;
                            tempFly.Mautosome5[1]=MAUTOSOME(all);
                            if(tempFly.Mautosome5[1]==O) mO5counter++;
                            else M5counter++;
                            break;
                }//End of: switch(locus)
            }*/

            /*if((tempFly.Mautosome1[0]==O || tempFly.Mautosome1[1]==O) && (tempFly.Mautosome2[0]==O || tempFly.Mautosome2[1]==O))
              {                                                              // MM homozygosity on 1st and 2nd autosome is lethal
                if(tempFly.CheckSex()==female)
                {
                    OffFPop.push_back(tempFly);                    //puts new fly on the end of the female offspring vector
                    NFOffFlyOnIsland[OurIsland]++;
                    femaleCounter++;
                }
                else
                {
                    OffMPop.push_back(tempFly);
                    NMOffFlyOnIsland[OurIsland]++;
                    maleCounter++;
                }
            }*/

      }//next Kid
    } //next FemaleFly
  } //next OurIsland
//setting sizes of subpopulations to 0
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  NFOffFlyOnIsland[OurIsland]=0;
  NMOffFlyOnIsland[OurIsland]=0;
  }
OffFPop.resize(0);               //paternal populations deleted
OffMPop.resize(0);               //
}






void NewGeneration3 (vector <Fly> &MPop, vector <Fly> &FPop,
                    vector <Fly> &OffMPop, vector <Fly> &OffFPop,
                    vector <int> &NMPop, vector <int> &NFPop,
                    vector <int> &NOffMPop, vector <int> &NOffFPop,
                    int MaxMFlies, int MaxFFlies)
{
int Kid, LuckyFly, OurIsland, fliesBefore=0, OffFliesBefore=0;
vector<Fly>::iterator iMaleBeginning=MPop.begin();
vector<Fly>::iterator iFemaleBeginning=FPop.begin();

//males
int island=0;
OffFliesBefore=0;
int OffMaleCounter=OffMPop.size();
if((int)OffMPop.size()>=MaxMFlies*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxMFlies;Kid++)
      { //for every place on island
      do
        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(OffMaleCounter);
        }
      while
        (OffMPop[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      OffMPop[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      MPop.push_back(OffMPop[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      OffMPop[LuckyFly]=OffMPop[OffMaleCounter-1];
      //size of offspring population decreases by one
      OffMaleCounter--;
      }//Next Kid
    NMPop[OurIsland]=MaxMFlies;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<OffMaleCounter;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((NMPop[island]>=MaxMFlies || MPop[Kid].Island==island) && n<OffMaleCounter);
    //CAUTION!! An island might get overcrowded!!
    if (MPop[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore+=NMPop[AlsoAnIsland];
      }//Next AlsoAnIsland
    OffMPop[Kid].Island=island;
    //adds fly to the next generation
    MPop.insert(iMaleBeginning+fliesBefore,OffMPop[Kid]);
    NMPop[island]++;
    }//Next Kid
  }


//females
fliesBefore=0, OffFliesBefore=0;
island=0;
OffFliesBefore=0;
int OffFemaleCounter=OffMPop.size();
if((int)OffFPop.size()>=MaxFFlies*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxFFlies;Kid++)
      { //for every place on island
      do
        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(OffFemaleCounter);
        }
      while
        (OffFPop[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      OffFPop[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      FPop.push_back(OffFPop[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      OffFPop[LuckyFly]=OffFPop[OffFemaleCounter-1];
      //size of offspring population decreases by one
      OffFemaleCounter--;
      }//Next Kid
    NFPop[OurIsland]=MaxFFlies;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<OffFemaleCounter;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((NFPop[island]>=MaxFFlies || FPop[Kid].Island==island) && n<OffFemaleCounter);
    //CAUTION!! An island might get overcrowded!!
    if (FPop[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore+=NFPop[AlsoAnIsland];
      }//Next AlsoAnIsland
    OffFPop[Kid].Island=island;
    //adds fly to the next generation
    FPop.insert(iFemaleBeginning+fliesBefore,OffFPop[Kid]);
    NFPop[island]++;
    }//Next Kid
  }



//setting sizes of offspring subpopulations to 0
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  NOffFPop[OurIsland]=0;
  NOffMPop[OurIsland]=0;
  }//next OurIsland
//offspring populations resized to zero
OffFPop.resize(0);
OffMPop.resize(0);
}//End of: NewGeneration

//Every female mates with one randomly chosen male from her island and gives offspring
//males can be chosen several times







