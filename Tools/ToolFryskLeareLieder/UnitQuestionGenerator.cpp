//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitQuestionGenerator.h"
//---------------------------------------------------------------------------
#include <ctime>
#include <cassert>
#include <algorithm>
//---------------------------------------------------------------------------
QuestionGenerator::QuestionGenerator(const std::set<QuestionType>& types)
: mNcorrect(0),
  mNincorrect(0),
  mQuestionTypes(types),
  mEasyVerbs(GetEasyVerbs()),
  mMediumVerbs(GetMediumVerbs()),
  mHardVerbs(GetHardVerbs()),
  mEasyNouns(GetEasyNouns()),
  mMediumNouns(GetMediumNouns()),
  mHardNouns(GetHardNouns()),
  mEasySentences(GetEasySentences()),
  mMediumSentences(GetMediumSentences()),
  mHardSentences(GetHardSentences())
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------

std::string QuestionGenerator::GetQuestion() const
{
  //Set the iterator to a random questiontype
  const int type = std::rand() % mQuestionTypes.size();
  std::set<QuestionType>::const_iterator iter = mQuestionTypes.begin();
  for (int i=0; i<type; ++i) { ++iter; }

  switch ( *iter )
  {
    case easyVerb       : return GetQuestion(mEasyVerbs);
    case mediumVerb     : return GetQuestion(mMediumVerbs);
    case hardVerb       : return GetQuestion(mHardVerbs);
    case easyNoun       : return GetQuestion(mEasyNouns);
    case mediumNoun     : return GetQuestion(mMediumNouns);
    case hardNoun       : return GetQuestion(mHardNouns);
    case easySentence   : return GetQuestion(mEasySentences);
    case mediumSentence : return GetQuestion(mMediumSentences);
    case hardSentence   : return GetQuestion(mHardSentences);
  }
  assert(!"Should not get here");
  return "";
}
//---------------------------------------------------------------------------
std::string QuestionGenerator::GetQuestion(const QuestionMap& verbs) const
{
  const int size = verbs.size();

  //Draw a random index
  const int index = std::rand() % size;

  //Set the iterator to the correct answer
  Iterator iterator = verbs.begin();
  for (int i=0; i<index; ++i) { ++iterator; }

  //Get the question
  mLastQuestion = (*iterator).first;

  //Get the answer
  mAnswers = verbs.equal_range(mLastQuestion);

  //Return the question the iterator points to
  return mLastQuestion;
}
//---------------------------------------------------------------------------
bool QuestionGenerator::GiveAnswer(const std::string& answer)
{
  for (Iterator i = mAnswers.first; i!= mAnswers.second; ++i)
  {
    if ( ToUpperCase(i->second) == ToUpperCase(answer) )
    {
      ++mNcorrect;
      return true;
    }
  }
  ++mNincorrect;
  return false;
}
//---------------------------------------------------------------------------
std::vector<std::string> QuestionGenerator::GetAnswers() const
{
  std::vector<std::string> v;

  for (Iterator i = mAnswers.first; i!= mAnswers.second; ++i)
  {
    v.push_back(i->second);
  }
  return v;

}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetEasyVerbs() const
{
  QuestionMap verbs;
  //29. Dwaan
  verbs.insert(std::make_pair("Tiidwurd: dwaan,ik,notiid", "doch"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,do,notiid", "dochst"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,hy,notiid", "docht"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,wy,notiid", "dogge"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,ik,doetiid", "die"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,do,doetiid", "diest"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,hy,doetiid", "die"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,wy,doetiid", "diene"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,wy,doetiid", "dienen"));
  verbs.insert(std::make_pair("Tiidwurd: dwaan,mulwurd", "haw dien"));
  //46. Gean
  verbs.insert(std::make_pair("Tiidwurd: gean,ik,notiid", "gean"));
  verbs.insert(std::make_pair("Tiidwurd: gean,do,notiid", "giest"));
  verbs.insert(std::make_pair("Tiidwurd: gean,hy,notiid", "giet"));
  verbs.insert(std::make_pair("Tiidwurd: gean,wy,notiid", "geane"));
  verbs.insert(std::make_pair("Tiidwurd: gean,ik,doetiid", "gong"));
  verbs.insert(std::make_pair("Tiidwurd: gean,do,doetiid", "gongst"));
  verbs.insert(std::make_pair("Tiidwurd: gean,hy,doetiid", "gong"));
  verbs.insert(std::make_pair("Tiidwurd: gean,wy,doetiid", "gongen"));
  verbs.insert(std::make_pair("Tiidwurd: gean,mulwurd", "bin gongen"));
  //55. Hawwe
  verbs.insert(std::make_pair("Tiidwurd: hawwe,ik,notiid", "haw"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,do,notiid", "hast"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,hy,notiid", "hat"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,wy,notiid", "hawwe"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,ik,doetiid", "hie"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,do,doetiid", "hiest"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,hy,doetiid", "hie"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,wy,doetiid", "hiene"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,wy,doetiid", "hienen"));
  verbs.insert(std::make_pair("Tiidwurd: hawwe,mulwurd", "haw hân"));
  //120. Sykje
  verbs.insert(std::make_pair("Tiidwurd: sykje,ik,notiid", "sykje"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,do,notiid", "sikest"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,hy,notiid", "siket"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,wy,notiid", "sykje"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,ik,doetiid", "socht"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,do,doetiid", "sochtest"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,hy,doetiid", "socht"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,wy,doetiid", "sochten"));
  verbs.insert(std::make_pair("Tiidwurd: sykje,mulwurd", "haw socht"));
  //121. Sille
  verbs.insert(std::make_pair("Tiidwurd: sille,ik,notiid", "sil"));
  verbs.insert(std::make_pair("Tiidwurd: sille,do,notiid", "silst"));
  verbs.insert(std::make_pair("Tiidwurd: sille,hy,notiid", "sil"));
  verbs.insert(std::make_pair("Tiidwurd: sille,wy,notiid", "sille"));
  verbs.insert(std::make_pair("Tiidwurd: sille,ik,doetiid", "soe"));
  verbs.insert(std::make_pair("Tiidwurd: sille,do,doetiid", "soest"));
  verbs.insert(std::make_pair("Tiidwurd: sille,hy,doetiid", "soe"));
  verbs.insert(std::make_pair("Tiidwurd: sille,wy,doetiid", "soene"));
  verbs.insert(std::make_pair("Tiidwurd: sille,mulwurd", "haw sillen"));
  //124. Sizze
  verbs.insert(std::make_pair("Tiidwurd: sizze,ik,notiid", "sjis"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,do,notiid", "seist"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,hy,notiid", "seit"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,wy,notiid", "sizze"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,ik,doetiid", "sei"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,do,doetiid", "seist"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,hy,doetiid", "sei"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,wy,doetiid", "seine"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,wy,doetiid", "seinen"));
  verbs.insert(std::make_pair("Tiidwurd: sizze,mulwurd", "haw sein"));
  //125. Sjen
  verbs.insert(std::make_pair("Tiidwurd: sjen,ik,notiid", "sjoch"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,do,notiid", "sjochst"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,hy,notiid", "sjocht"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,wy,notiid", "sjogge"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,ik,doetiid", "seach"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,do,doetiid", "seachst"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,hy,doetiid", "seach"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,wy,doetiid", "seagen"));
  verbs.insert(std::make_pair("Tiidwurd: sjen,mulwurd", "haw sjoen"));
  //187. Wêze
  verbs.insert(std::make_pair("Tiidwurd: wêze,ik,notiid", "bin"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,do,notiid", "bist"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,hy,notiid", "is"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,wy,notiid", "binne"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,jo,notiid", "binne"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,ik,doetiid","wie"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,do,doetiid","wiest"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,hy,doetiid","wie"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,wy,doetiid","wiene"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,wy,doetiid","wienen"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,jo,doetiid","wiene"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,jo,doetiid","wienen"));
  verbs.insert(std::make_pair("Tiidwurd: wêze,mulwurd",   "haw west"));
  return verbs;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetMediumVerbs() const
{
  QuestionMap verbs;
  verbs.insert(std::make_pair("Medium verb", "anything"));
  return verbs;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetHardVerbs() const
{
  QuestionMap verbs;
  verbs.insert(std::make_pair("Hard verb", "anything"));
  return verbs;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetEasyNouns() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Niemand", "Net ien"));
  nouns.insert(std::make_pair("Niets", "Neat"));
  nouns.insert(std::make_pair("Akkoord", "Akkoart"));
  nouns.insert(std::make_pair("Misschien", "Mooglik"));
  nouns.insert(std::make_pair("Hier", "Hjir"));
  nouns.insert(std::make_pair("Daar", "Dêr"));
  nouns.insert(std::make_pair("Ergens", "Earne"));
  nouns.insert(std::make_pair("Nergens", "Nearne"));
  nouns.insert(std::make_pair("Overal", "Oeral"));
  nouns.insert(std::make_pair("Overal", "Rûnom"));
  nouns.insert(std::make_pair("Dichtbij", "Tichteby"));
  nouns.insert(std::make_pair("Rechtdoor", "Rjochttroch"));
  nouns.insert(std::make_pair("Via", "Fia"));
  nouns.insert(std::make_pair("In", "Yn"));
  nouns.insert(std::make_pair("Op", "Op"));
  nouns.insert(std::make_pair("Onder", "ûnder"));
  nouns.insert(std::make_pair("Tegen", "Tsjin"));
  nouns.insert(std::make_pair("Tegenover", "Foar oer"));
  nouns.insert(std::make_pair("Naast", "Neist"));
  nouns.insert(std::make_pair("Bij", "By"));
  nouns.insert(std::make_pair("Voor", "Foar"));
  nouns.insert(std::make_pair("Beneden", "ûnder"));
  nouns.insert(std::make_pair("Boven", "boppe"));
  nouns.insert(std::make_pair("Binnen", "binnen"));
  nouns.insert(std::make_pair("Buiten", "bûten"));
  nouns.insert(std::make_pair("Achter", "Efter"));
  nouns.insert(std::make_pair("Vooraan", "Foaroan"));
  nouns.insert(std::make_pair("Achteraan", "Efteroan"));
  //Translation verbs
  nouns.insert(std::make_pair("Blijken", "Blike"));
  nouns.insert(std::make_pair("Blijven", "Bliuwe"));
  nouns.insert(std::make_pair("Durven", "Doare"));
  nouns.insert(std::make_pair("Doen", "Dwaan"));
  nouns.insert(std::make_pair("Vinden", "Fine"));
  nouns.insert(std::make_pair("Gaan", "Gean"));
  nouns.insert(std::make_pair("Hebben", "Hawwe"));
  nouns.insert(std::make_pair("Geven", "Jaan"));
  nouns.insert(std::make_pair("Kunnen", "Kinne"));
  nouns.insert(std::make_pair("Klinken", "Klinke"));
  nouns.insert(std::make_pair("Komen", "Komme"));
  nouns.insert(std::make_pair("Krijgen","Krije"));
  nouns.insert(std::make_pair("Lijken","Lykje"));
  nouns.insert(std::make_pair("Laten","Litte"));
  nouns.insert(std::make_pair("Kijken","Loaitsje"));
  nouns.insert(std::make_pair("Kijken","Sjen"));
  nouns.insert(std::make_pair("Mogen","Meie"));
  nouns.insert(std::make_pair("Maken","Meitsje"));
  nouns.insert(std::make_pair("Moeten","Moatte"));
  nouns.insert(std::make_pair("Lopen","Rinne"));
  nouns.insert(std::make_pair("Zoeken","Sykje"));
  nouns.insert(std::make_pair("Zullen","Sille"));
  nouns.insert(std::make_pair("Zeggen","Sizze"));
  nouns.insert(std::make_pair("Zien","Loaitsje"));
  nouns.insert(std::make_pair("Zien","Sjen"));
  nouns.insert(std::make_pair("Staan","Stean"));
  nouns.insert(std::make_pair("Denken","Tinke"));
  nouns.insert(std::make_pair("Zijn", "Wêze"));
  nouns.insert(std::make_pair("Willen", "Wolle"));
  nouns.insert(std::make_pair("Worden", "Wurde"));
  return nouns;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetMediumNouns() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Medium noun", "anything"));
  return nouns;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetHardNouns() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Hard noun", "anything"));
  return nouns;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetEasySentences() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Wie?", "Wa?"));
  nouns.insert(std::make_pair("Wie is dat?", "Wa is dat?"));
  nouns.insert(std::make_pair("Wat?", "Wat?"));
  nouns.insert(std::make_pair("Wat is hier te zien?", "Wat is hjir te sjen?"));
  nouns.insert(std::make_pair("Waar?", "Wêr?"));
  nouns.insert(std::make_pair("Hoe?", "Hoe?"));
  nouns.insert(std::make_pair("Hoe ver is dat?", "Hoe fier is dat?"));
  nouns.insert(std::make_pair("Hoelang duurt dat?", "Hoe lang duorret dat?"));
  nouns.insert(std::make_pair("Hoeveel?", "Hoefolle?"));
  nouns.insert(std::make_pair("Hoeveel kost dat?", "Hoefolle kostet dat?"));
  nouns.insert(std::make_pair("Hoe laat is het?", "Hoe let is it?"));
  nouns.insert(std::make_pair("Welk(e)?", "Hokker?"));
  nouns.insert(std::make_pair("Welk glas is voor mij?", "Hokker glês is foar my?"));
  nouns.insert(std::make_pair("Hoeveel?", "Hoefolle?"));
  nouns.insert(std::make_pair("Wanneer?", "Wannear?"));
  nouns.insert(std::make_pair("Waarom?", "Wêrom?"));
  nouns.insert(std::make_pair("Het spijt me", "It spyt my"));
  nouns.insert(std::make_pair("Een ogenblikje a.u.b.", "Momint graach"));
  nouns.insert(std::make_pair("Ik heb nu geen tijd", "Ik ha it no net oan tiid"));
  nouns.insert(std::make_pair("Dat is onmogelijk", "Dat kin net"));
  nouns.insert(std::make_pair("Ik geloof het wel", "Ik leau fan wol"));
  nouns.insert(std::make_pair("Ik denk het ook", "Ik tink it ek"));
  nouns.insert(std::make_pair("Ik hoop het ook", "Ik hoopje it ek"));
  nouns.insert(std::make_pair("Helemaal niet", "Hielendal net"));
  nouns.insert(std::make_pair("Dat klopt", "Dat kloppet"));
  nouns.insert(std::make_pair("Ik weet het niet", "Ik wit it net"));
  nouns.insert(std::make_pair("Ver weg", "Fier fuort"));
  nouns.insert(std::make_pair("Naar recht", "Nei rjochts"));
  nouns.insert(std::make_pair("Naar links", "Nei links"));
  nouns.insert(std::make_pair("In het midden", "Yn 'e midden"));
  nouns.insert(std::make_pair("Naar voren", "Nei foarren"));
  nouns.insert(std::make_pair("Naar beneden", "Nei ûnderen"));
  nouns.insert(std::make_pair("Naar boven", "Nei boppen"));
  nouns.insert(std::make_pair("In het noorden", "Yn it noarden"));
  nouns.insert(std::make_pair("Naar het zuiden", "Nei it noarden"));
  nouns.insert(std::make_pair("Uit het westen", "ût it westen"));
  nouns.insert(std::make_pair("Van het oosten", "Fan it easten"));
  nouns.insert(std::make_pair("Welke dag is het vandaag?", "Watfoar dei is it hjoed?"));
  nouns.insert(std::make_pair("De hoeveelste is het vandaag?", "De hoefolste is it hjoed?"));
  nouns.insert(std::make_pair("Deze week", "Fan 'e wike"));
  nouns.insert(std::make_pair("Volgende week", "Nije wike"));
  nouns.insert(std::make_pair("Volgende maand", "Oare moanne"));
  nouns.insert(std::make_pair("De volgende dag", "De oare deis"));
  nouns.insert(std::make_pair("De vorige dag", "De foarige deis"));
  nouns.insert(std::make_pair("Dit jaar", "Fan 't jier"));
  nouns.insert(std::make_pair("Vorig jaar", "Ferline jier"));
  nouns.insert(std::make_pair("Volgend jaar", "Takom jier"));
  nouns.insert(std::make_pair("Volgend jaar", "Takomme jier"));
  nouns.insert(std::make_pair("Vrije dag", "Frije dei"));
  nouns.insert(std::make_pair("Een half uur", "In healoere"));
  nouns.insert(std::make_pair("Om hoe laat?", "Om hoe let?"));
  nouns.insert(std::make_pair("Hoe laat kan ik langskomen?", "Hoe let kin ik delkomme?"));
  nouns.insert(std::make_pair("Te vroeg", "Te betiid"));
  nouns.insert(std::make_pair("Te laat", "Te let"));
  nouns.insert(std::make_pair("Op tijd", "Op 'e tiid"));
  //Chapter 2
  nouns.insert(std::make_pair("Goedemorgen", "Goeie moarn"));
  nouns.insert(std::make_pair("Goedemiddag", "Goeie middei"));
  nouns.insert(std::make_pair("Goedenavond", "Goejûn"));
  nouns.insert(std::make_pair("Hoe gaat het ermee?", "Hoe is't dermei?"));
  nouns.insert(std::make_pair("Niet zo goed", "Net sa goed"));
  nouns.insert(std::make_pair("Gaat wel", "Giet wol"));
  nouns.insert(std::make_pair("Ik ga maar eens", "Ik stap mar wer ris op"));
  nouns.insert(std::make_pair("Ik moet er vandoor", "Ik moat fuort"));
  nouns.insert(std::make_pair("Tot ziens", "Oant sjen"));
  nouns.insert(std::make_pair("Tot straks", "Oant aanst"));
  nouns.insert(std::make_pair("Tot zo", "Oant daliks"));
  nouns.insert(std::make_pair("Dank u wel", "Tankjewol"));
  nouns.insert(std::make_pair("Geen dank", "Neat te tankjen"));
  nouns.insert(std::make_pair("Graag gedaan", "Graach dien"));
  nouns.insert(std::make_pair("Laat maar zitten", "Lit mar sitte"));
  nouns.insert(std::make_pair("Dat kan iedereen overkomen", "Dat kin elk oerkomme"));
  return nouns;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetMediumSentences() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Medium noun", "anything"));
  return nouns;
}
//---------------------------------------------------------------------------
QuestionGenerator::QuestionMap QuestionGenerator::GetHardSentences() const
{
  QuestionMap nouns;
  nouns.insert(std::make_pair("Hard noun", "anything"));
  return nouns;
}
//---------------------------------------------------------------------------
std::string ToUpperCase(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
   (int(*)(int)) std::toupper);
  return s;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



#pragma package(smart_init)
