//---------------------------------------------------------------------------
#ifndef UnitSendKeysH
#define UnitSendKeysH
//---------------------------------------------------------------------------
/* Copyright (c) 2004 lallous <lallousx86@yahoo.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
//---------------------------------------------------------------------------
// Modified by Bilderbikkel (RJCB)
// http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>

class CSendKeys
{
private:
  bool m_bWait, m_bUsingParens, m_bShiftDown, m_bAltDown, m_bControlDown, m_bWinDown;
  DWORD  m_nDelayAlways, m_nDelayNow;

  //RJCB: Added static member variable
  static HWND enumwindowsProc_hwnd;
  //RJCB: Added static member variable
  static LPARAM enumwindowsProc_lParam;
  //RJCB: Removed the arguments
  //static BOOL CALLBACK enumwindowsProc(HWND hwnd, LPARAM lParam);
  //RJCB: Use static member variables instead
  static BOOL CALLBACK enumwindowsProc();

  void   CarryDelay();

  typedef BYTE KEYBOARDSTATE_t[256];
  struct enumwindow_t
  {
    LPTSTR str;
    HWND hwnd;
  };

  struct key_desc_t
  {
    LPCTSTR keyName;
    BYTE VKey;
    bool normalkey; // a normal character or a VKEY ?
  };

  enum
  {
    MaxSendKeysRecs  = 71,
    MaxExtendedVKeys = 10
  };

  /*
  Reference: VkKeyScan() / MSDN
  Bit Meaning 
  --- --------
  1   Either SHIFT key is pressed. 
  2   Either CTRL key is pressed. 
  4   Either ALT key is pressed. 
  8   The Hankaku key is pressed 
  16  Reserved (defined by the keyboard layout driver). 
  32  Reserved (defined by the keyboard layout driver). 
  */
  static const WORD VKKEYSCANSHIFTON;
  static const WORD VKKEYSCANCTRLON;
  static const WORD VKKEYSCANALTON;
  static const WORD INVALIDKEY;

  static key_desc_t KeyNames[MaxSendKeysRecs]; 
  static const BYTE ExtendedVKeys[MaxExtendedVKeys];

  static bool BitSet(BYTE BitTable, UINT BitMask);

  void PopUpShiftKeys();

  static bool IsVkExtended(BYTE VKey);
  void SendKeyUp(BYTE VKey);
  void SendKeyDown(BYTE VKey, WORD NumTimes, bool GenUpMsg, bool bDelay = false);
  void SendKey(WORD MKey, WORD NumTimes, bool GenDownMsg);
  static WORD StringToVKey(LPCTSTR KeyString, int &idx);
  void KeyboardEvent(BYTE VKey, BYTE ScanCode, LONG Flags);

public:

  bool SendKeys(LPCTSTR KeysString, bool Wait = false);
  static bool AppActivate(HWND wnd);
  static bool AppActivate(LPCTSTR WindowTitle, LPCTSTR WindowClass = 0);
  void SetDelay(const DWORD delay) { m_nDelayAlways = delay; }
  CSendKeys();
};
//---------------------------------------------------------------------------
#endif
