object FormRandomCode: TFormRandomCode
  Left = 209
  Top = 137
  Width = 519
  Height = 368
  Caption = 'Random C++ Code Generator (C) 2007 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Constraints.MinHeight = 142
  Constraints.MinWidth = 452
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  Icon.Data = {
    0000010001001010020000000000B00000001600000028000000100000002000
    0000010001000000000080000000000000000000000000000000000000000000
    0000FFFFFF00FFFF00008E310000F5ED0000F5ED0000CDED0000BC310000BDFD
    0000CDFD0000FFFF0000CCDB0000BB5B0000BB5B0000BB530000BB4B0000CCDB
    0000FFFF00000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000}
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object RichEdit1: TRichEdit
    Left = 0
    Top = 41
    Width = 511
    Height = 293
    Align = alClient
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 511
    Height = 41
    Align = alTop
    TabOrder = 1
    DesignSize = (
      511
      41)
    object ButtonGenerate: TButton
      Left = 8
      Top = 8
      Width = 177
      Height = 25
      Caption = 'Generate random code'
      TabOrder = 0
      OnClick = ButtonGenerateClick
    end
    object ButtonAbout: TButton
      Left = 431
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'About'
      TabOrder = 1
      OnClick = ButtonAboutClick
    end
  end
end
