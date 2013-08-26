object FormMain: TFormMain
  Left = 536
  Top = 184
  Width = 278
  Height = 240
  Caption = 'Logistic Growth Equation Simulator (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object TrackBar1: TTrackBar
    Left = 0
    Top = 0
    Width = 270
    Height = 33
    Align = alTop
    Max = 4000
    Orientation = trHorizontal
    Frequency = 1000
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object Editor1: TValueListEditor
    Left = 0
    Top = 33
    Width = 270
    Height = 120
    Align = alTop
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goAlwaysShowEditor, goThumbTracking]
    Strings.Strings = (
      'r='
      'Nequil=')
    TabOrder = 1
    ColWidths = (
      47
      217)
  end
  object ButtonCreateFeigen: TButton
    Left = 8
    Top = 168
    Width = 153
    Height = 25
    Caption = 'Create Feigenbaum'
    TabOrder = 2
    OnClick = ButtonCreateFeigenClick
  end
  object ButtonAbout: TButton
    Left = 168
    Top = 168
    Width = 91
    Height = 25
    Caption = 'About'
    TabOrder = 3
    OnClick = ButtonAboutClick
  end
end
