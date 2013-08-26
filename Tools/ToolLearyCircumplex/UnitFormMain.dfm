object FormMain: TFormMain
  Left = 293
  Top = 171
  BorderStyle = bsDialog
  Caption = 'LearyCircumplex (C) 2009 Rich'#232'l Bilderbeek'
  ClientHeight = 192
  ClientWidth = 304
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object Editor1: TValueListEditor
    Left = 8
    Top = 8
    Width = 209
    Height = 175
    Strings.Strings = (
      'BS=5.3'
      'SB=6.2'
      'SO=6.6'
      'OS=5.8'
      'OT=2.9'
      'TO=2.8'
      'TB=2.6'
      'BT=3.7')
    TabOrder = 0
    TitleCaptions.Strings = (
      'Legend'
      'Score')
    ColWidths = (
      102
      101)
  end
  object ButtonDraw: TButton
    Left = 224
    Top = 8
    Width = 73
    Height = 25
    Caption = 'Draw'
    TabOrder = 1
    OnClick = ButtonDrawClick
  end
  object ButtonSave: TButton
    Left = 224
    Top = 40
    Width = 73
    Height = 25
    Caption = 'Save'
    TabOrder = 2
    OnClick = ButtonSaveClick
  end
  object ButtonAbout: TButton
    Left = 224
    Top = 160
    Width = 73
    Height = 25
    Caption = 'About'
    TabOrder = 3
    OnClick = ButtonAboutClick
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Please select a filename to save your Leary Circumplex'
    Left = 224
    Top = 72
  end
end
