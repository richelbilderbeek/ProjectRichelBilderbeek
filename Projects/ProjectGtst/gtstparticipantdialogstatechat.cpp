//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/shared_ptr.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WRadioButton>
#include <Wt/WTable>
#include <Wt/WTableRow>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstchatmessage.h"
#include "gtstgroupfinished.h"
#include "gtstgrouploggedin.h"
#include "gtstgroupnotloggedin.h"
#include "gtstgroup.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstserverstate.h"
#include "gtstserverstatechat.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstate.h"
#include "gtstparticipantdialogstatechat.h"
#include "shape.h"
#include "shapewidget.h"
//#include "trace.h"
#include "wtserverpusher.h"
#include "wtshapewidget.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateChat::ParticipantDialogStateChat(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

///Do something random with the UI, used by DebugDialog
void ribi::gtst::ParticipantDialogStateChat::DoSomethingRandom()
{
  switch (std::rand() % 10)
  {
    case 0: ui.m_edit_chat->setText(GetRandomDebugString()); break;
    case 1: SubmitChatText(); break;
    default: break; //No problem
  }
}

std::string ribi::gtst::ParticipantDialogStateChat::GetRandomDebugString() const
{
  static std::vector<std::string> v;
  if (v.empty())
  {
    v =
    {
      "Success should not go to head and failure should not go to heart. (Tamil proverb)",
      "Light travels faster then sound... which is why most people appear brilliant until you hear them.",
      "Happiness is like a butterfly, which when pursued is just beyond your grasp, but which if you will sit down quietly may alight upon you. (Hawthorne)",
      "The larger the lake of knowledge the longer the shore of wonder.",
      "When the power of love overcomes the love of power, then the world will know peace. (Jimi Hendrix)",
      "There is a light at the end of every tunnel, just pray it's not a train.",
      "You were born as an original. Don't die as a copy.",
      "He who feels that he is too small to make a difference has never been bitten by a mosquito.",
      "If I knew grandchildren were going to be this much fun, I would have had them first!",
      "If you let go of the past, it no longer has a hold on you.",
      "There is a certain freedom in having nothing left to lose.",
      "Rules + Regulations - Relationships = Resentment + Rebellion.",
      "When I stand before the Lord, I'd rather explain why I went, rather than why I didn't go.",
      "We do what we believe, the rest is just a bunch of religious talk.",
      "Of course men can multitask, they read on the toilet.",
      "Friendship should not be sought, but is usually found both by chance and good luck.",
      "Enthusiasm can be like a fire that needs an occasional poke with a stick.",
      "The envious praise me unknowingly. (Kahlil Gibran)",
      "If you can laugh with a person, you can work with a person.",
      "Strive for perfection in everything you do. ",
      "Take the best that exists and make it better. ",
      "When it does not exist, design it. (Sir Frederick Henry Royce - of Rolls-Royce)",
      "Smile is contagious; just smile at someone and see their reaction.",
      "It takes a day to find a friend, a moment to lose them but a lifetime to forget them.",
      "He, who doesn't hope to win has already lost. (Simon Bolivar)",
      "Don't follow the crowd, let the crowd follow you.",
      "Making your good times count and not forgeting your bad times makes a man sucessful.",
      "Though we travel the world over to find the beautiful, we must carry it with us or we find it not. (Ralph Waldo Emerson)",
      "Fate decides who walks into your life, you decide who you let stay, who you let walk away, and who you refuse to let walk out.",
      "It's true that we don't know what we've got until we lose it, but it's also true that we don't know what we've been missing until it arrives.",
      "Don't make someone a priority, who only makes you an option.",
      "If a man is not there for you at your worst, he does not deserve to see you at your best.",
      "It is the pain of sacrifice or the pain of regret.",
      "He who wrestles with us, strengthens our nerves and sharpens our skills. Our antagonist is our helper. (Edmund Burke)",
      "Friendship is not about who came first or who cares the most. It is all about who came in your life and never left.",
      "Contingencies have tendencies to become dependencies. (W. Thomas McQueeney)",
      "When you take things for granted, the things you are granted, get taken. (Phil Hennessy)",
      "The older I get, the smarter my Dad gets. (Mark Twain)",
      "The search for wisdom is a great challenge; to act on wisdom is an even greater challenge. (Jagad Guru)",
      "Charity may begin at home, but if it goes no further, it's no longer charity. It's clan loyalty.",
      "A computer once beat me at chess, but it was no match for me at kick boxing.",
      "Advice for the day: If you have a headache, do what it says on the aspirin bottle: Take two, and keep away from children.",
      "Expecting the world to treat you fairly because you are good is like expecting the bull not to charge because you are a vegetarian.",
      "When the well's dry, we know the worth of water. (Ben Franklin)",
      "A succesful man makes more money than his woman can spend. ",
      "A succesful woman is one who can find such a man.",
      "If you can't dance, don't blame the dance floor.",
      "The road to a friends house is never long. (Swedish proverb)",
      "The time to ensure that the toilet works is before you really need it.",
      "Making enemies out of friends is easy. ",
      "Making friends out of enemies is difficult, but it is actually worthwhile.",
      "Fools learn from experience. Wise men learn from the experience of others (Otto von Bismark)",
      "When the congregation falls asleep it is time for the minister to wake up.",
      "The measure of greatness is not found in your accomplishments. Its in how much discouragement it takes to stop you.",
      "Laziness is the mother of all vice... but, it's a mother and you should respect her! (Spanish popular wisdom)",
      "Talent hits the target which no one else can hit; genius hits the target which no one else can see.",
      "A beautiful relationship does not depend upon how good we understand someone but on how well we avoid misunderstandings.",
      "Wisdom will keep you from getting into situations where you need it. (Bruce M. Sandbrook)",
      "Opportunity is a bald man with a beard: You can catch him coming, but you can' t catch him going.",
      "What is worth having is worth waiting for.",
      "Love is an irresistible desire to be irresistibly desired. (Robert Frost)",
      "An eye for an eye leaves the whole world blind. (Mohandas Gandhi)",
      "As long as people keep killing people, to stop the killing of people, the killing will go on.",
      "If love was a raindrop I would send you a shower ",
      "If hope was a minute I would send you an hour",
      "If happiness was a leaf I would send you a tree",
      "If you need a friend you will always have me!",
      "Surely it's no coincidence that the word 'listen' is an anagram of the word 'silent'.",
      "May every day of your life together be worse than the next. (Old Irish wedding blessing)",
      "If this is coffee, please bring me some tea; but if this is tea, please bring me some coffee. (Abraham Lincoln)",
      "A good match blows fire...",
      "You may have grown old, but you may not have grown up.",
      "It is not what you gather but what you scatter that tells what kind of life you have lived.",
      "If you need time alone, try cleaning the house.",
      "If I never had a bad day, how would I know whether I was having a good day? (Lee)",
      "When you give and don't expect anything back that's love. But if you give and expect a return it's an investment.",
      "Laughter is a smile with the volume turned up.",
      "Sometimes we all have days where we are 386's in a P4 world.",
      "Have you ever noticed how the contents of a box are much more interesting before the box is opened?",
      "It is okay to visit your past just don't bring any luggage with you.",
      "There's a book that tells you where you should go on your vacation. It's called your checkbook.",
      "Knowledge is proud she knows so much; wisdom is humble that she knows no more. (Cowper)",
      "Twenty years from now you will be more disappointed by the things you did not do than by the ones you did. (Mark Twain)",
      "You can't expect people to look eye to eye with you if you are looking down on them.",
      "We can't always build the future for our youth, but we can build our youth for the future. (Franklin D. Roosevelt)",
      "Be not simply good; be good for something. (Henry David Thoreau)",
      "Success is the ability to go from one failure to another with no loss of enthusiasm. (Winston Churchill)",
      "Be careful about reading health books. You may die of a misprint. (Mark Twain)",
      "Better a diamond with a flaw than a pebble without.",
      "A children's catechism class was learning the Apostles Creed. Each child had been assigned a sentence to repeat. ",
      "People laugh because I'm different, I laugh because they're all the same.",
      "Hope is the ability to hear the music of the future. ",
      "Faith is having the courage to dance to it today.",
      "You can't make someone else's choices. You shouldn't let someone else make yours. (Colin Powell)",
      "Impossibility simply means I'm possibility. (Monsieur Nana Adom)",
      "Faith is personal, but never private.",
      "Tears are the baptism of the soul.",
      "Utility is when you have one telephone, luxury is when you have two, and paradise is when you have none.",
      "A politician is the one who shakes your hand before elections and your confidence after.",
      "Quality rather than quantity determines your success.",
      "Don't protect yourself by a fence, but rather by your friends.        ",
      "A baby seal walks into a club. (Anonymous)",
      "Here was the sort of man you only dared to cross if you had a team of Sherpas with you. (Douglas Adams)",
      "I don't smoke, I don't drink, I don't snort and I don't gamble. I do lie a little bit though. (Tim Maia)",
      "I'm not an actor, but I play one on TV. (David Recksiek)",
      "Did you know that dolphins are just gay sharks? (Heather Morris)",
      "Black Beauty, He was a dark horse. (Tim Vine)",
      "Bigfoot is blurry, it's not the photographer's fault. (Mitch Hedberg)",
      "I have nothing to declare except my genius. (Oscar Wilde, upon arriving at US customs 1882[2])",
      "Race is just a pigment of the imagination (Glen Highland)",
      "If all those sweet young things were laid end to end - I wouldn't be a bit surprised. (Dorothy Parker, on girls attending a Yale prom[3])",
      "So, have you noticed there aren't a lot of Chinese guys named Rusty? (George Carlin)",
      "I never forget a face, but in your case I'll be glad to make an exception. (Groucho Marx)",
      "Take my wife - please! (Henny Youngman)",
      "The worst time to have a heart attack is during a game of charades (Demetri Martin)",
      "My friend has difficulty sleeping, but I can do it with my eyes closed. (Shmuel Breban)",
      "If it wasn't for pickpockets, I'd have no sex life at all. (Rodney Dangerfield)",
      "Overall, I'd say my career as a photographer has been a bit of a blur. (Milton Jones)",
      "My mom bought me a memory pillow a couple of years ago... I don't tell secrets in my bedroom anymore. (Bink)",
      "Ah, nostalgia ain't what it used to be... (English Proverb)",
      "I have a map of the world... it's actual size. (Steven Wright)",
      "I live in a two-income household, but who knows how long my mom can keep that up. (Shmuel Breban)",
      "I quit my job at the helium factory, I refuse to be spoken to in that tone. (Stewart Francis)",
      "I have come here to chew bubblegum and kick ass, and I'm all out of bubblegum. (Nada in They Live[4])",
      "People laughed when I said I'd become a comedian. Well, they're not laughing now. (Bob Monkhouse)",
      "A single spark can set a prairie on fire",
      "Water can both sustain and sink a ship",
      "Count not what is lost, but what is left",
      "If there is a strong general there will be no weak soldiers",
      "To extend your life by a year take one less bite each meal",
      "Peace only comes when reason rules",
      "Even the tallest tower started from the ground",
      "Eloquence provides only persuasion, but truth buys loyalty",
      "Wisdom is attained by learning when to hold one's tongue",
      "A single tree cannot make a forest",
      "If one eats less one will taste more",
      "One hand alone cannot clap, it takes two to quarrel",
      "It does not matter if the cat is black or white, so long as it catches mice",
      "Cowards have dreams, brave men have visions",
      "Learning is like the horizon; there is no limit",
      "The old horse will know the way",
      "A good friend shields you from the storm",
      "Change the skin, wash the heart",
      "Sow melon, reap melon; sow beans, reap beans",
      "One sings, all follow",
      "Fortune has a fickle heart and a short memory",
      "Harsh words and poor reasoning never settle anything",
      "Dangerous enemies will meet again in narrow streets",
      "Better to bend in the wind than to break",
      "Do not kill the hen for her eggs",
      "First attain skill; creativity comes later",
      "Make the cap fit the head",
      "A single beam cannot support a great house",
      "Do not be concerned with things outside your door",
      "Wise men may not be learned; learned men may not be wise",
      "Crows are black the world over",
      "Do not lift a rock only to drop it on your own foot",
      "Kill the chicken to frighten the monkey",
      "Wait long, strike fast",
      "Do not wait until you're thirsty to dig a well",
      "One who would pick the roses must bear with thorns",
      "Failure is the mother of success",
      "Do not climb a tree to look for a fish",
      "Only time and effort brings proficiency",
      "Distance tests the endurance of a horse; time reveals a man's character",
      //Programming
      "Programs must be written for people to read, and only incidentally for machines to execute. Harold Abelson and Gerald Jay Sussman",
      "Fools ignore complexity. Pragmatists suffer it. Some can avoid it. Geniuses remove it. Alan Perlis",
      "If you lie to the compiler, it will get its revenge. Henry Spencer"
    };
  }
  assert(!v.empty());
  std::string s = v[ std::rand() % v.size() ];
  return s;
}

void ribi::gtst::ParticipantDialogStateChat::RespondToServerPush()
{
  ServerStateChat * const server_state
    = dynamic_cast<ServerStateChat*>(m_server->GetStates()->GetCurrentState());
  if (!server_state)
  {
    std::clog << __func__ << ": warning: no ServerStateChat\n";
    return;
  }

  assert(GetDialog()->CanGetParticipant());
  assert(GetDialog()->GetParticipant()->GetId() >= 0);

  //Get chat messages for this participant
  if (server_state->CanGetChatMessages(GetDialog()->GetParticipant()))
  {
    const std::vector<boost::shared_ptr<ChatMessage> > chat_messages
      = server_state->GetChatMessages(
          GetDialog()->GetParticipant());

    std::for_each(chat_messages.begin(),chat_messages.end(),
      [this](const boost::shared_ptr<ChatMessage> chat_message)
      {
        assert(this->ui.m_table);
        this->ui.m_table->insertRow(0);
        WtShapeWidget * chat_tag = chat_message->GetSender()->GetChatShape()->Clone();
        ui.m_table->elementAt(0,0)->addWidget(chat_tag);
        ui.m_table->elementAt(0,1)->addWidget(new Wt::WText(chat_message->GetText()));
      } );

  }

  //Display the Participant
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateChat::RespondToTimedServerPush()
{
  const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();

  //Update label_time_left
  {
    const std::string text
    =  std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds ");
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
  }
}

void ribi::gtst::ParticipantDialogStateChat::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  ui.m_edit_chat = new Wt::WLineEdit(
    std::string("Hello from ")
    + std::to_string(GetDialog()->GetParticipant()->GetId()));
  ui.m_label_status = new Wt::WLabel("Welcome participant");

  assert(GetDialog()->GetParticipant()->CanGetId()
    && "Assume a logged in participant with an ID");

  ui.m_label_chat_tag = new Wt::WLabel("Your chat tag is");

  ui.m_label_group = new Wt::WLabel(
    std::string("You are in group number ")
    + std::to_string(
      m_server->GetGroups()->FindMyGroup(GetDialog()->GetParticipant())->GetId()));
  ui.m_label_time_left = new Wt::WLabel(
    (std::string("Time left: ")
    + std::to_string(m_server->GetStates()->GetCurrentState()->GetTimeLeft())
    + std::string(" seconds ")).c_str());
  ui.m_table = new Wt::WTable;

  assert(ui.m_edit_chat);
  assert(ui.m_label_group);
  assert(ui.m_label_chat_tag);
  assert(ui.m_label_status);
  assert(ui.m_label_time_left);
  assert(ui.m_table);

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_status);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_group);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_chat_tag);
  dialog->addWidget(GetDialog()->GetParticipant()->GetChatShape()->Clone());
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_time_left);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_edit_chat);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_table);

  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Possible voting options",dialog);

    const std::vector<std::string> descriptions
      = m_server->GetParameters()->GetVoting()->GetVoteDescriptions();
    const int n_descriptions
      = boost::numeric_cast<int>(descriptions.size());
    //Add the RadioButtons
    for (int i=0; i!=n_descriptions; ++i)
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton(descriptions[i].c_str(), container);
      button->setEnabled(false);
      new Wt::WBreak(container);
    }
  }


  ui.m_edit_chat->setMinimumSize(600,Wt::WLength::Auto);
  ui.m_table->setMinimumSize(600,600);
  ui.m_edit_chat->enterPressed().connect(
    this,&ribi::gtst::ParticipantDialogStateChat::SubmitChatText);
}

void ribi::gtst::ParticipantDialogStateChat::SubmitChatText()
{
  assert(ui.m_edit_chat);
  assert(GetDialog()->CanGetParticipant()
    && "When the dialog in in the chatting state, there should be a participant");

  if (ui.m_edit_chat->text().empty()) return;

  const std::string s = ui.m_edit_chat->text().toUTF8();
  ui.m_edit_chat->setText(GetRandomDebugString().c_str());

   

  ServerStateChat * const server_state
    = dynamic_cast<ServerStateChat*>(m_server->GetStates()->GetCurrentState());
  if (!server_state)
  {
    std::clog << __func__ << ": warning: no ServerStateChat\n";
    return;
  }


  server_state->NotifyChatMessage(
    GetDialog()->GetParticipant(),
      boost::shared_ptr<ChatMessage>(
        new ChatMessage(
          GetDialog()->GetParticipant(),s)));
}

