object FormMain: TFormMain
  Left = 192
  Top = 114
  AutoSize = True
  BorderStyle = bsDialog
  Caption = 'GrayCoder (C) 2009 Richel Bilderbeek'
  ClientHeight = 164
  ClientWidth = 597
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
  object PanelInt: TPanel
    Left = 0
    Top = 41
    Width = 597
    Height = 41
    Align = alTop
    TabOrder = 2
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 140
      Height = 14
      Caption = 'Integer binary value'
    end
    object EditIntBinary: TEdit
      Left = 216
      Top = 8
      Width = 281
      Height = 22
      TabStop = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object PanelGray: TPanel
    Left = 0
    Top = 82
    Width = 597
    Height = 41
    Align = alTop
    TabOrder = 3
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 154
      Height = 14
      Caption = 'Gray code binary value'
    end
    object EditGrayBinary: TEdit
      Left = 216
      Top = 8
      Width = 281
      Height = 22
      TabStop = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 597
    Height = 41
    Align = alTop
    Caption = 'PanelTop'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 147
      Height = 14
      Caption = 'Integer decimal value'
    end
    object EditInt: TEdit
      Left = 256
      Top = 11
      Width = 201
      Height = 22
      TabOrder = 1
      Text = '0'
      OnChange = EditIntChange
    end
    object ButtonIntPlus: TButton
      Left = 456
      Top = 10
      Width = 24
      Height = 23
      Caption = '+'
      TabOrder = 2
      OnClick = ButtonIntPlusClick
    end
    object ButtonIntMinus: TButton
      Left = 232
      Top = 10
      Width = 24
      Height = 23
      Caption = '-'
      TabOrder = 0
      OnClick = ButtonIntMinusClick
    end
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 123
    Width = 597
    Height = 41
    Align = alTop
    Caption = 'PanelBottom'
    TabOrder = 1
    object Label4: TLabel
      Left = 8
      Top = 16
      Width = 161
      Height = 14
      Caption = 'Gray code decimal value'
    end
    object EditGray: TEdit
      Left = 256
      Top = 11
      Width = 201
      Height = 22
      TabOrder = 1
      Text = '0'
      OnChange = EditGrayChange
    end
    object ButtonGrayMinus: TButton
      Left = 232
      Top = 10
      Width = 24
      Height = 23
      Caption = '-'
      TabOrder = 0
      OnClick = ButtonGrayMinusClick
    end
    object ButtonGrayPlus: TButton
      Left = 456
      Top = 10
      Width = 24
      Height = 23
      Caption = '+'
      TabOrder = 2
      OnClick = ButtonGrayPlusClick
    end
    object ButtonAbout: TButton
      Left = 512
      Top = 8
      Width = 75
      Height = 25
      Caption = 'About'
      TabOrder = 3
      OnClick = ButtonAboutClick
    end
  end
end
