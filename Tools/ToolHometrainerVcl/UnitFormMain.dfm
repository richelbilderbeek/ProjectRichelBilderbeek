object FormMain: TFormMain
  Left = 182
  Top = 128
  Width = 704
  Height = 527
  BorderIcons = [biMinimize, biMaximize]
  Caption = 'Hometrainer 2 (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWhite
  Font.Height = -16
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  WindowState = wsMaximized
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 18
  object Panel: TPanel
    Left = 0
    Top = 452
    Width = 696
    Height = 41
    Align = alBottom
    Caption = 'Correct: 0, incorrect: 0'
    Color = clBlack
    TabOrder = 0
    object PanelQuit: TPanel
      Left = 600
      Top = 1
      Width = 95
      Height = 39
      Align = alRight
      BevelOuter = bvNone
      Color = clBlack
      TabOrder = 0
      DesignSize = (
        95
        39)
      object Quit: TButton
        Left = 12
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'Quit'
        TabOrder = 0
        OnClick = QuitClick
      end
    end
  end
  object PanelQuestion: TPanel
    Left = 0
    Top = 0
    Width = 696
    Height = 452
    Align = alClient
    Color = clBlack
    TabOrder = 1
  end
  object TimerMain: TTimer
    Interval = 10
    OnTimer = TimerMainTimer
    Left = 8
    Top = 8
  end
end
