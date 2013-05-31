#ifndef WTWEBSITEMENUDIALOG_H
#define WTWEBSITEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
namespace Wt
{
  enum Orientation;
  struct WMenu;
  struct WStackedWidget;
  struct WWidget;
}
//---------------------------------------------------------------------------
///WtWebsiteMenuDialog is the visual menu.
///All it does is emit signals when a button is clicked.
struct WtWebsiteMenuDialog : public Wt::WContainerWidget
{
  WtWebsiteMenuDialog();

  private:
  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewConnectThreeMenuDialog() const;
  Wt::WWidget * CreateNewRandomCodeDialog() const;
  Wt::WWidget * CreateNewTestAsciiArterDialog() const;
  Wt::WWidget * CreateNewTestEncrangerDialog() const;
  Wt::WWidget * CreateNewTestNewickVectorDialog() const;
  Wt::WWidget * CreateNewTicTacToeDialog() const;
  Wt::WWidget * CreateNewTimePollDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;

  Wt::WMenu * CreateNewMenu(
    Wt::WStackedWidget * const contents,
    const Wt::Orientation& orientation) const;

  void CheckResources();
  void ShowMenuBorder();
  void ShowMenuHorizontal();
  void ShowMenuVertical();

  public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

};
//---------------------------------------------------------------------------


#endif // WTWEBSITEMENUDIALOG_H
