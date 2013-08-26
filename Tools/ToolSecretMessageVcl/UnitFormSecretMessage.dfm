object FormSecretMessage: TFormSecretMessage
  Left = 211
  Top = 139
  Width = 625
  Height = 484
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'SecretMessage (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 14
  object PanelCreate: TPanel
    Left = 0
    Top = 0
    Width = 617
    Height = 150
    Align = alTop
    BevelOuter = bvNone
    Caption = '(X) Create '
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSilver
    Font.Height = -85
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnMouseDown = PanelCreateMouseDown
  end
  object PanelExtract: TPanel
    Left = 0
    Top = 150
    Width = 617
    Height = 150
    Align = alTop
    BevelOuter = bvNone
    Caption = '(X) Extract'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSilver
    Font.Height = -85
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnMouseDown = PanelExtractMouseDown
  end
  object PanelAbout: TPanel
    Left = 0
    Top = 300
    Width = 617
    Height = 150
    Align = alTop
    BevelOuter = bvNone
    Caption = '(X) About  '
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSilver
    Font.Height = -85
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnMouseDown = PanelAboutMouseDown
  end
end
