object FormIncorrect: TFormIncorrect
  Left = 329
  Top = 210
  BorderStyle = bsNone
  Caption = 'FormIncorrect'
  ClientHeight = 291
  ClientWidth = 399
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWhite
  Font.Height = -16
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 18
  object PanelIncorrect: TPanel
    Left = 0
    Top = 0
    Width = 399
    Height = 97
    Align = alTop
    Caption = 'Incorrect!'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clWhite
    Font.Height = -64
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 97
    Width = 399
    Height = 32
    Align = alTop
    Caption = 'The correct answer was: '
    Color = clBlack
    TabOrder = 1
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 129
    Width = 399
    Height = 162
    Align = alClient
    Color = clBlack
    PlainText = True
    ReadOnly = True
    TabOrder = 2
  end
  object TimerAutoClose: TTimer
    Interval = 2500
    OnTimer = TimerAutoCloseTimer
    Left = 8
    Top = 8
  end
end
