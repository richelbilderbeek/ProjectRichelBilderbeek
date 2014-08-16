object FormReversi: TFormReversi
  Left = 202
  Top = 153
  Width = 457
  Height = 363
  Caption = 'Reversi (C) 2007 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Constraints.MinHeight = 363
  Constraints.MinWidth = 457
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier'
  Font.Style = []
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF007777
    8888777788887777888877778888777788887777888877778888777788888888
    CCCC999977778888CCCC999977778888CCCC999977778888CCCC999977777777
    9999CCCC888877779999CCCC888877779999CCCC888877779999CCCC88888888
    7777888877778888777788887777888877778888777788887777888877770000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poScreenCenter
  ShowHint = True
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object ImageBoard: TImage
    Left = 0
    Top = 82
    Width = 449
    Height = 247
    Align = alClient
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    Stretch = True
    OnMouseDown = ImageBoardMouseDown
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 0
    Width = 449
    Height = 41
    Align = alTop
    BorderWidth = 4
    Caption = 'Reversi'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 0
    object ImageRedActive: TImage
      Left = 5
      Top = 5
      Width = 30
      Height = 31
      Align = alLeft
      Picture.Data = {
        07544269746D61703A000000424D3A0000000000000036000000280000000100
        0000010000000100180000000000040000000000000000000000000000000000
        0000FFFFFF00}
      Stretch = True
      OnClick = ImageActiveClick
    end
    object ImageBlueActive: TImage
      Left = 414
      Top = 5
      Width = 30
      Height = 31
      Align = alRight
      Picture.Data = {
        07544269746D61703A000000424D3A0000000000000036000000280000000100
        0000010000000100180000000000040000000000000000000000000000000000
        0000FFFFFF00}
      Stretch = True
      Visible = False
      OnClick = ImageActiveClick
    end
  end
  object PanelMenu: TPanel
    Left = 0
    Top = 41
    Width = 449
    Height = 41
    Align = alTop
    BorderWidth = 4
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 1
    object LabelRed: TLabel
      Left = 35
      Top = 5
      Width = 64
      Height = 31
      Align = alLeft
      Alignment = taCenter
      AutoSize = False
      Caption = ' 2 '
    end
    object ImageRed: TImage
      Left = 5
      Top = 5
      Width = 30
      Height = 31
      Align = alLeft
      Picture.Data = {
        07544269746D61703A000000424D3A0000000000000036000000280000000100
        0000010000000100180000000000040000000000000000000000000000000000
        0000FFFFFF00}
      Stretch = True
    end
    object ImageBlue: TImage
      Left = 414
      Top = 5
      Width = 30
      Height = 31
      Align = alRight
      Picture.Data = {
        07544269746D61703A000000424D3A0000000000000036000000280000000100
        0000010000000100180000000000040000000000000000000000000000000000
        0000FFFFFF00}
      Stretch = True
    end
    object LabelBlue: TLabel
      Left = 350
      Top = 5
      Width = 64
      Height = 31
      Align = alRight
      Alignment = taCenter
      AutoSize = False
      Caption = ' 2 '
    end
    object LabelRestart: TLabel
      Left = 99
      Top = 5
      Width = 144
      Height = 31
      Align = alLeft
      Alignment = taCenter
      Caption = ' Restart '
      OnClick = LabelRestartClick
    end
    object LabelAbout: TLabel
      Left = 238
      Top = 5
      Width = 112
      Height = 31
      Align = alRight
      Alignment = taCenter
      Caption = ' About '
      OnClick = LabelAboutClick
    end
  end
end
