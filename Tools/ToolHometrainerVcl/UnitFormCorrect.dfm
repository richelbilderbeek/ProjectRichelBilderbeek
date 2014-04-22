object FormCorrect: TFormCorrect
  Left = 329
  Top = 210
  BorderStyle = bsNone
  Caption = 'FormCorrect'
  ClientHeight = 164
  ClientWidth = 388
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWhite
  Font.Height = -64
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 69
  object PanelCorrect: TPanel
    Left = 0
    Top = 0
    Width = 388
    Height = 164
    Align = alClient
    Caption = 'Correct!'
    Color = clBlack
    TabOrder = 0
  end
  object TimerAutoClose: TTimer
    OnTimer = TimerAutoCloseTimer
    Left = 8
    Top = 8
  end
end
