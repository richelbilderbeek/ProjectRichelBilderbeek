object FormRestart: TFormRestart
  Left = 352
  Top = 258
  BorderStyle = bsNone
  Caption = 'FormRestart'
  ClientHeight = 149
  ClientWidth = 266
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
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 266
    Height = 41
    Align = alTop
    Caption = 'Do you really want to restart?'
    TabOrder = 0
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 41
    Width = 266
    Height = 108
    Align = alClient
    TabOrder = 1
    object PanelYes: TPanel
      Left = 8
      Top = 8
      Width = 121
      Height = 41
      Caption = 'Yes'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = PanelYesClick
    end
    object PanelNo: TPanel
      Left = 136
      Top = 8
      Width = 121
      Height = 41
      Caption = 'No'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = PanelNoClick
    end
    object EditSize: TLabeledEdit
      Left = 8
      Top = 72
      Width = 121
      Height = 22
      EditLabel.Width = 70
      EditLabel.Height = 14
      EditLabel.Caption = 'Board size'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      Text = '8'
    end
  end
end
