//---------------------------------------------------------------------------
///\mainpage GTST
///
///Welcome to the GTST documentation
///
///\author
///Richel Bilderbeek
///
///\remark
///In collaboration with Lucas Molleman, Piet van den Berg and
///Franjo Weissing
///
///\todo
///- let an Administrator also remain logged in by his/her IP
///- let a Partipant that has a browser refresh automatically go to the
///  Participant screens instead of to the Welcome screen
///- when a Participant participates, remove the menu items that are not
///  to be used anymore: Administrator, About, Experiment flow
///- Add quiz at beginning
///- Add questionnaire at end

///\remark
///Most classes have the following:
///  private:
///  ~ParticipantDialog();
///  friend void boost::checked_delete<>(Administrator*);
///
///This idiom the following trouble,
///cited from http://www.boost.org/libs/utility/checked_delete.html:
///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
///class types to be deleted with a delete-expression.
///When the class has a non-trivial destructor, or a class-specific operator
///delete, the behavior is undefined. Some compilers issue a warning when an
///incomplete type is deleted, but unfortunately, not all do, and programmers
///sometimes ignore or disable warnings.
///
///The template syntax of the befriending with boost::checked_delete is from
///* Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8.
///  Item 8: 'Befriending templates'.

///\remark
///Hall Of Fame, that is people that broke the server:
/// - 82.136.255.242
/// - 84.85.246.65
/// - 85.151.237.75
/// - 127.0.0.1
/// - 129.125.142.212
/// - 129.125.142.230
/// - 129.125.177.214
/// - 145.94.229.7
///(yes, the joke is intentional)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "gtstall_groups.h"
#include "gtstall_serverstates.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstmenudialog.h"
#include "gtstserver.h"
#include "ipaddress.h"
#include "stopwatch.h"
#include "trace.h"
#include "wtautoconfig.h"
#include "wtselectfiledialog.h"
#pragma GCC diagnostic pop

///\brief
///The Wt application of this program.
struct WtGtstApplication : public Wt::WApplication
{
  ///Create a WtGtstApplication
  WtGtstApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("GTST");
    this->useStyleSheet("wt.css");
    const boost::scoped_ptr<ribi::SafeIpAddress> ip_address(
      new ribi::SafeIpAddress(env.clientAddress()));
    root()->addWidget(new ribi::gtst::MenuDialog(ip_address.get()));
  }
};

///Create a Wt::WApplication
Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  return new WtGtstApplication(env);
}

///\brief
///The program's entry point
int main(int argc, char *argv[])
{
  { START_TRACE(); }
  ribi::WtSelectFileDialog::SetPath(boost::filesystem::path(argv[0]).parent_path().string());
  ribi::WtAutoConfig a(argc,argv,createApplication);

  return a.Run();
}

