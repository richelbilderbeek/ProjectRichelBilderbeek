//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/test/included/prg_exec_monitor.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WLabel>
//---------------------------------------------------------------------------
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groups.h"
#include "ipaddress.h"
#include "logfile.h"
#include "maintimer.h"
#include "stopwatch.h"
#include "wtautoconfig.h"
#include "parameters.h"
#include "projectgtstmenudialog.h"
#include "server.h"
#include "serverstate.h"
#include "serverstateassignpayoff.h"
#include "serverstatechat.h"
#include "serverstatechooseaction.h"
#include "serverstatefinished.h"
#include "serverstategroupassign.h"
#include "serverstategroupreassign.h"
#include "serverstatequiz.h"
#include "serverstateviewresultsall.h"
#include "serverstateviewresultsgroup.h"
#include "serverstateviewresultsvoting.h"
#include "serverstatevoting.h"
#include "serverstatewaiting.h"
#include "trace.h"
#include "wtbroadcastserver.h"
#include "wtselectfiledialog.h"
//---------------------------------------------------------------------------
struct WtGtstTestConcurrencyDialog : public Wt::WContainerWidget, WtBroadcastServerClient
{
  ///Create a MenuDialog using one IP address per Participant
  WtGtstTestConcurrencyDialog()
  {
    MainTimer::Get();
    {
       
      server->TestMe();
      WtBroadcastServer::GetInstance()->Post();
    }
    ui.m_label = new Wt::WLabel;
    this->addWidget(ui.m_label);
  }
  void UpdatePage()
  {
    ///Let this thread sleep, to give the other thread a chance
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    const int x = std::rand() % 100;
    switch (x)
    {
      case 0:
      {
        const  
        const std::set<boost::shared_ptr<Administrator> >& admins
          = server->GetAdministrators();
        ui.m_label->setText(
          (std::to_string(x) + std::string(": ")
          + std::to_string(admins.size())).c_str()
          );
      }
      break;
      case 1:
      {
        const  
        const ServerState * const state = server->GetCurrentState();
        ui.m_label->setText(
          (std::to_string(x) + std::string(": ")
          + std::to_string(state->ToStr())).c_str()
          );
      }
      break;
      case 2:
      {
        const  
        const Groups * const groups = server->GetGroups();
        ui.m_label->setText(
          (std::to_string(x) + std::string(": ")
          + std::to_string(groups->CollectParticipants().size())).c_str()
          );
      }
      break;
      case 3:
      {
         
        boost::shared_ptr<Parameters> p(new Parameters);
        p->ReadFromFile("parameters7.txt");
        server->SetParameters(p);
        WtBroadcastServer::GetInstance()->Post();
      }
      break;
      case 4:
      {
        const  
        const LogFile * const log = server->GetLog();
        ui.m_label->setText(
          (std::to_string(x) + std::string(": ")
          + std::to_string(log->m_log_filename)).c_str()
          );
      }
      break;
      case 5:
      {
        const  
        const Parameters * const parameters = server->GetParameters();
        ui.m_label->setText(
          (std::to_string(x) + std::string(": ")
          + std::to_string(parameters->CreateDefaultParticipant()->ToAdminStr())).c_str()
          );
      }
      break;
      default:
        //No problem
      break;
    }
    this->refresh();
  }
  private:
  struct Ui
  {
    Ui() : m_label(0) {}
    Wt::WLabel * m_label;
  } ui;
};
//---------------------------------------------------------------------------
///\brief
///The Wt application to test the concurrency of this program.
struct WtGtstTestConcurrencyApplication : public Wt::WApplication
{
  ///Create a WtGameTheoryApplication
  WtGtstTestConcurrencyApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("GTST");
    this->useStyleSheet("wt.css");
    root()->addWidget(new WtGtstTestConcurrencyDialog);
  }
};
//---------------------------------------------------------------------------
///Create a Wt::WApplication
Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new WtGtstTestConcurrencyApplication(env);
}
//---------------------------------------------------------------------------
///\brief
///The program's entry point
///
///Normally, this function its name would be 'main', but because
///of using the Boost.Test library, the main entry point function must
///be called 'cpp_main'
int cpp_main(int argc, char **argv)
{
  boost::debug::detect_memory_leaks(true);
  {
    START_TRACE();
  }
  WtSelectFileDialog::SetPath(boost::filesystem::path(argv[0]).parent_path().string());
  WtAutoConfig a(argc,argv,createApplication);

  return a.Run();
}
//---------------------------------------------------------------------------
