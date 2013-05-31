#ifndef NSANABROSKEYS_H
#define NSANABROSKEYS_H
//---------------------------------------------------------------------------
#include <set>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
struct NsanaBrosKeys : public boost::noncopyable
{
  NsanaBrosKeys();

  int GetHorizontal() const;
  int GetVertical() const;

  //double StealDx();
  //double StealDy();

  void KeyPress(const int key);
  void KeyRelease(const int key);

  static int GetKeyLeft() { return m_key_left; }
  static int GetKeyRight(){ return m_key_right; }
  static int GetKeyUp()   { return m_key_up; }
  static int GetKeyDown() { return m_key_down; }
  static void SetKeyLeft(const int key);
  static void SetKeyRight(const int key);
  static void SetKeyUp(const int key);
  static void SetKeyDown(const int key);

  ///m_signal_keyschanged is emitted when a key is changed.
  ///m_signal_keyschanged is declared mutable, because emitting a signal
  ///IMHO does not change the state of NsanaBrosKeys.
  mutable boost::signals2::signal<void ()> m_signal_keyschanged;

  private:
  ~NsanaBrosKeys() {}
  friend void boost::checked_delete<>(NsanaBrosKeys *);

  std::set<int> m_keys;
  int m_dx;
  int m_dy;

  static int m_key_left;
  static int m_key_right;
  static int m_key_up;
  static int m_key_down;

  void Update();
};
//---------------------------------------------------------------------------
#endif // NSANABROSKEYS_H
