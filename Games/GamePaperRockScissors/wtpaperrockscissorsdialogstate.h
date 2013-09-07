#ifndef WTPAPERROCKSCISSORSDIALOGSTATE_H
#define WTPAPERROCKSCISSORSDIALOGSTATE_H

#include <boost/checked_delete.hpp>

#include <Wt/WObject>


namespace ribi {

struct WtPaperRockScissorsDialog;
struct WtPaperRockScissorsServer;
struct WtPaperRockScissorsEvent;

struct WtPaperRockScissorsDialogState : public Wt::WObject
{
  WtPaperRockScissorsDialogState(
    WtPaperRockScissorsDialog * const dialog,
    WtPaperRockScissorsServer * const server);

  void Connect();
  void Disconnect();
  ///ProcessEvent processes an event given by the server, when
  ///another user does something we need to be noted of
  virtual void ProcessEvent(const WtPaperRockScissorsEvent& event) = 0;

  void SetStateAbout(WtPaperRockScissorsDialogState * const prev_state);

  virtual void Show() = 0;

  protected:
  virtual ~WtPaperRockScissorsDialogState();
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(WtPaperRockScissorsDialogState* x);

  protected:
  WtPaperRockScissorsDialog * const m_dialog;
  WtPaperRockScissorsServer * const m_server;
};

struct WtPaperRockScissorsDialogStateAbout
  : public WtPaperRockScissorsDialogState
{
  WtPaperRockScissorsDialogStateAbout(
    WtPaperRockScissorsDialog * const dialog,
    WtPaperRockScissorsServer * const server,
    WtPaperRockScissorsDialogState * const prev_state);
  void ProcessEvent(const WtPaperRockScissorsEvent& event);

  void SetOnCloseState(WtPaperRockScissorsDialogState * const prev_state);
  void Show();

  private:
  virtual ~WtPaperRockScissorsDialogStateAbout() {}
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(WtPaperRockScissorsDialogStateAbout* x);

  WtPaperRockScissorsDialogState * m_prev_state;

  void OnClose();
};

struct WtPaperRockScissorsDialogStateConnect
  : public WtPaperRockScissorsDialogState
{
  WtPaperRockScissorsDialogStateConnect(
    WtPaperRockScissorsDialog * const dialog,
    WtPaperRockScissorsServer * const server);

  void ProcessEvent(const WtPaperRockScissorsEvent& event);
  void Show();

  private:
  virtual ~WtPaperRockScissorsDialogStateConnect() {}
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(WtPaperRockScissorsDialogStateConnect* x);
};

struct WtPaperRockScissorsDialogStateGame
  : public WtPaperRockScissorsDialogState
{
  WtPaperRockScissorsDialogStateGame(
    WtPaperRockScissorsDialog * const dialog,
    WtPaperRockScissorsServer * const server);

  void ProcessEvent(const WtPaperRockScissorsEvent& event);
  void Send();
  void Show();

  private:
  virtual ~WtPaperRockScissorsDialogStateGame() {}
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(WtPaperRockScissorsDialogStateGame* x);

  Wt::WButtonGroup * m_group;
};

struct WtPaperRockScissorsDialogStateLogin
  : public WtPaperRockScissorsDialogState
{
  WtPaperRockScissorsDialogStateLogin(
    WtPaperRockScissorsDialog * const dialog,
    WtPaperRockScissorsServer * const server);

  void ProcessEvent(const WtPaperRockScissorsEvent& event);
  void Show();

  private:
  virtual ~WtPaperRockScissorsDialogStateLogin() {}
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(WtPaperRockScissorsDialogStateLogin* x);

  Wt::WLineEdit * m_edit_username;
  void OnEditChanged();
};

} //~namespace ribi

#endif // WTPAPERROCKSCISSORSDIALOGSTATE_H
