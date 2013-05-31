#include "mating.h"

//Matingfirst.h
//Works correctly
void Mating ()
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
    FfliesBefore+=NFFlyOnIsland[OurIsland-1];
    MfliesBefore+=NMFlyOnIsland[OurIsland-1];
    FOffFliesBefore+=NFOffFlyOnIsland[OurIsland-1];
    MOffFliesBefore+=NMOffFlyOnIsland[OurIsland-1];
    }
    NFOffFlyOnIsland.push_back(0);
    NMOffFlyOnIsland.push_back(0);

  for(FemaleFly=0;FemaleFly<NFFlyOnIsland[OurIsland];FemaleFly++)     //for every female on island
    {
    //Select a random mate-> mate='male number'
    mate=RandomNumber(NMFlyOnIsland[OurIsland]); //number of male partner

    for(Kid=0;Kid<NKids;Kid++)
      {
      //Putting offspring on right island
      tempFly.Island=OurIsland;

      //Let the kid inherit its parents genes
      int AlleleMother, AlleleFather;
      AlleleMother=RandomNumber(2); // and which allele of parent will be taken
      AlleleFather=RandomNumber(2); // this is done for every "chromosome"
      tempFly.SexChrom[0]=FPop[FfliesBefore+FemaleFly].SexChrom[AlleleMother];
      if(tempFly.SexChrom[0]==X) {Xcounter++;}              //X,Y,Xm counting
      else
        {if(tempFly.SexChrom[0]==Y) {Ycounter++;}
           else {Xmcounter++;}}
      tempFly.SexChrom[1]=MPop[MfliesBefore+mate].SexChrom[AlleleFather];
      if(tempFly.SexChrom[1]==X) {Xcounter++;}              //X,Y,Xm counting
        else {if(tempFly.SexChrom[1]==Y) {Ycounter++;}
          else {Xmcounter++;}}
      //F autosome 1
      AlleleMother=RandomNumber(2);
      AlleleFather=RandomNumber(2);
      tempFly.Fautosome1[0]=FPop[FfliesBefore+FemaleFly].Fautosome1[AlleleMother];
        if(tempFly.Fautosome1[0]==F) {Fcounter1++;}
        else {FDcounter1++;}
      tempFly.Fautosome1[1]=MPop[MfliesBefore+mate].Fautosome1[AlleleFather];
        if(tempFly.Fautosome1[1]==F) {Fcounter1++;}
        else {FDcounter1++;}

      //F autosome 2
      AlleleMother=RandomNumber(2);
      AlleleFather=RandomNumber(2);
      tempFly.Fautosome2[0]=FPop[FfliesBefore+FemaleFly].Fautosome2[AlleleMother];
        if(tempFly.Fautosome2[0]==F) {Fcounter2++;}
        else {FDcounter2++;}
      tempFly.Fautosome2[1]=MPop[MfliesBefore+mate].Fautosome2[AlleleFather];
        if(tempFly.Fautosome2[1]==F) {Fcounter2++;}
        else {FDcounter2++;}

      //F autosome 3
      AlleleMother=RandomNumber(2);
      AlleleFather=RandomNumber(2);
      tempFly.Fautosome3[0]=FPop[FfliesBefore+FemaleFly].Fautosome3[AlleleMother];
        if(tempFly.Fautosome3[0]==F) {Fcounter3++;}
        else {FDcounter3++;}
      tempFly.Fautosome3[1]=MPop[MfliesBefore+mate].Fautosome3[AlleleFather];
        if(tempFly.Fautosome3[1]==F) {Fcounter3++;}
        else {FDcounter3++;}


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
        else {M5counter++;}

      //Putting fly on right island
      tempFly.Island=OurIsland;

      //Mutation in kid...
      /*if(Uniform()<PMut)                    //if the mutation occure
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
      if((tempFly.Mautosome1[0]==O || tempFly.Mautosome1[1]==O) && (tempFly.Mautosome2[0]==O || tempFly.Mautosome2[1]==O))
        { // MM homozygosity on 1st and 2nd autosome is lethal
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
        }

       /*OLD CODE. STILL NEEDED YES/NO?
         if (tempFly.GetSex()==male) //A male is born
         {
         tempFly.sex=male;
         OffMPop.push_back(tempFly);
         NMOffFlyOnIsland[OurIsland]++;
         maleCounter++;
         }
       else
         {
         tempFly.sex=female;
         OffFPop.push_back(tempFly);                    //puts new fly on the end of the female offspring vector
         NFOffFlyOnIsland[OurIsland]++;
         femaleCounter++;
         }*/

      }//next Kid
    } //next FemaleFly
  } //next OurIsland
if (maleCounter==0 && femaleCounter==0) { PopulationDied=true; }
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  NFFlyOnIsland[OurIsland]=0;
  NMFlyOnIsland[OurIsland]=0;
  }
FPop.resize(0);               //paternal populations deleted
MPop.resize(0);               //
}




void NewGeneration (vector <Fly> &dispersingSex, vector <Fly> &nondispersingSex,
                    vector <Fly> &OffdispersingSex, vector <Fly> &OffnondispersingSex,
                    vector <int> &dSexOnIsland, vector <int> &ndSexOnIsland,
                    vector <int> &OffdSexOnIsland, vector <int> &OffNDSexOnIsland,
                    int MaxDsex, int MaxNDsex)
{
int Kid, LuckyFly, OurIsland, fliesBefore=0, OffFliesBefore=0;
vector<Fly>::iterator iBiginning=dispersingSex.begin();

//non-dispersing sex stays on the some island as mothers
for(OurIsland=0;OurIsland<NIslands;OurIsland++)                                   //for every island
  {
  if(OurIsland>0)
    { //check how many offspring flies are on previous islands
    //OffFliesBefore are Non-dispers
    OffFliesBefore+=OffNDSexOnIsland[OurIsland-1];
    }//End of: if(OurIsland>0)

  //Offspring of the non-dispersing sex
  //ShowMessage(OffNDSexOnIsland.
  if(OffNDSexOnIsland[OurIsland]<=MaxNDsex) //Als het eiland nog niet vol is, dan...
    { //if there are less or the same numer of offspring as the carrying capacity of the island
    for(Kid=0;Kid<OffNDSexOnIsland[OurIsland];Kid++)
      { //for every offspring fly moves then to the next generation
      //********************************** Shouldn't the nondispersingSex vector be emptied first"
      nondispersingSex.push_back(OffnondispersingSex[OffFliesBefore+Kid]);
      }
    ndSexOnIsland[OurIsland]=OffNDSexOnIsland[OurIsland]; //number of flies in the new generation equals number of offspring
    }  //End of: if(OffNDSexOnIsland[OurIsland]<=MaxNDsex)
    else
    { //if there are more offspring than carrying capacity of the island
    for(Kid=0;Kid<MaxNDsex;Kid++)
      { //for every place on the island
      //takes random fly from offspring on that island
      LuckyFly=RandomNumber(OffNDSexOnIsland[OurIsland]);
      //and moves it to the next generation
      nondispersingSex.push_back(OffnondispersingSex[OffFliesBefore+LuckyFly]);
      //moves last fly from the island
      OffnondispersingSex[OffFliesBefore+LuckyFly]=OffnondispersingSex[OffFliesBefore+OffNDSexOnIsland[OurIsland]-1];
      OffNDSexOnIsland[OurIsland]--;
      }//Next Kid
    //counts original number of offspring flies on island
    OffNDSexOnIsland[OurIsland]+=MaxNDsex; //?????
    //number of flies in new generatin equals carrying capacity
    ndSexOnIsland[OurIsland]=MaxNDsex;
    }
  }//Next OurIslands

//dispersing sex
int island=0;
OffFliesBefore=0;
int OffdSexCounter=OffdispersingSex.size();
if((int)OffdispersingSex.size()>=MaxDsex*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxDsex;Kid++)
      { //for every place on island
      do
        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(OffdSexCounter);
        }
      while
        (OffdispersingSex[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      OffdispersingSex[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      dispersingSex.push_back(OffdispersingSex[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      OffdispersingSex[LuckyFly]=OffdispersingSex[OffdSexCounter-1];
      //size of offspring population decreases by one
      OffdSexCounter--;
      }//Next Kid
    dSexOnIsland[OurIsland]=MaxDsex;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<OffdSexCounter;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((dSexOnIsland[island]>=MaxDsex || dispersingSex[Kid].Island==island) && n<OffdSexCounter);
    //CAUTION!! An island might get overcrowded!!
    if (dispersingSex[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore+=dSexOnIsland[AlsoAnIsland];
      }//Next AlsoAnIsland
    OffdispersingSex[Kid].Island=island;
    //adds fly to the next generation
    dispersingSex.insert(iBiginning+fliesBefore,OffdispersingSex[Kid]);
    dSexOnIsland[island]++;
    }//Next Kid

  }

//setting sizes of offspring subpopulations to 0
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  OffNDSexOnIsland[OurIsland]=0;
  OffdSexOnIsland[OurIsland]=0;
  }//next OurIsland
//offspring populations resized to zero
OffnondispersingSex.resize(0);
OffdispersingSex.resize(0);
}//End of: NewGeneration


void NewGenerationBoth(vector <Fly> &dispersingSex, vector <Fly> &dispersingSex2,
                       vector <Fly> &OffdispersingSex, vector <Fly> &OffdispersingSex2,
                       vector <int> &dSexOnIsland, vector <int> &dSexOnIsland2,
                       vector <int> &OffdSexOnIsland, vector <int> &OffdSexOnIsland2,
                       int MaxDsex, int MaxDsex2)
{
int Kid, LuckyFly, OurIsland, fliesBefore=0;
int fliesBefore2=0;
vector<Fly>::iterator iBiginning=dispersingSex.begin();
vector<Fly>::iterator iBiginning2=dispersingSex2.begin();

//dispersing sex 1
int island=0;
int OffdSexCounter=OffdispersingSex.size();
if((int)OffdispersingSex.size()>=MaxDsex*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxDsex;Kid++)
      { //for every place on island
//      do
//        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(OffdSexCounter);
//        }
//      while
//        (OffdispersingSex[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      OffdispersingSex[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      dispersingSex.push_back(OffdispersingSex[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      OffdispersingSex[LuckyFly]=OffdispersingSex[OffdSexCounter-1];
      //size of offspring population decreases by one
      OffdSexCounter--;
      }//Next Kid
    dSexOnIsland[OurIsland]=MaxDsex;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<OffdSexCounter;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((dSexOnIsland[island]>=MaxDsex || dispersingSex[Kid].Island==island) && n<OffdSexCounter);
    //CAUTION!! An island might get overcrowded!!
    if (dispersingSex[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore+=dSexOnIsland[AlsoAnIsland];
      }//Next AlsoAnIsland
    OffdispersingSex[Kid].Island=island;
    //adds fly to the next generation
    dispersingSex.insert(iBiginning+fliesBefore,OffdispersingSex[Kid]);
    dSexOnIsland[island]++;
    }//Next Kid
  }

//THE OTHER SEX ALSO DISPERSES HERE
int OffdSexCounter2=OffdispersingSex2.size();
if((int)OffdispersingSex2.size()>=MaxDsex2*NIslands)
  { //if there are in sum more offspring that total carrying capacity of population
  for(OurIsland=0;OurIsland<NIslands;OurIsland++)
    { //for every island
    for(Kid=0;Kid<MaxDsex2;Kid++)
      { //for every place on island
//      do
//        {
        //take by random one dispersing offspring fly
        LuckyFly=RandomNumber(OffdSexCounter2);
//        }
//      while
//        (OffdispersingSex2[LuckyFly].Island==OurIsland && LuckyFly!=0); //but not from the same island
      OffdispersingSex2[LuckyFly].Island=OurIsland;
      //adds that fly to the next generation
      dispersingSex2.push_back(OffdispersingSex2[LuckyFly]);
      //puts last fly from offspring population in place of moved fly
      OffdispersingSex2[LuckyFly]=OffdispersingSex2[OffdSexCounter2-1];
      //size of offspring population decreases by one
      OffdSexCounter2--;
      }//Next Kid
    dSexOnIsland2[OurIsland]=MaxDsex2;
    }//Next OurIsland
  }//End of: if
else //if there are in sum less offspring that total carrying capacity of population -> No flies die
  {
  int n;
  for(Kid=0;Kid<OffdSexCounter2;Kid++)
    { //for every offspring
    n=0;
    do
      { //chose island different thet the one on which the offspring is and not full
      island=RandomNumber(NIslands);
      n++;
      }
    while ((dSexOnIsland2[island]>=MaxDsex2 || dispersingSex2[Kid].Island==island) && n<OffdSexCounter2);
    //CAUTION!! An island might get overcrowded!!
    if (dispersingSex2[Kid].Island==island) ShowMessage("Overcrowding!"); //But it nearly ever happens!
    fliesBefore2=0;
    int AlsoAnIsland; for(AlsoAnIsland=0;AlsoAnIsland<island;AlsoAnIsland++)
      { //checks how many new generation flies are already on all islands with smaller number
      fliesBefore2+=dSexOnIsland2[AlsoAnIsland];
      }//Next AlsoAnIsland
    OffdispersingSex2[Kid].Island=island;
    //adds fly to the next generation
    dispersingSex2.insert(iBiginning2+fliesBefore2,OffdispersingSex2[Kid]);
    dSexOnIsland2[island]++;
    }//Next Kid
  }

//setting sizes of offspring subpopulations to 0
for(OurIsland=0;OurIsland<NIslands;OurIsland++)
  {
  OffdSexOnIsland2[OurIsland]=0;
  OffdSexOnIsland[OurIsland]=0;
  }//next OurIsland
//offspring populations resized to zero
OffdispersingSex.resize(0);
OffdispersingSex2.resize(0);
}//End of: NewGenerationBoth



