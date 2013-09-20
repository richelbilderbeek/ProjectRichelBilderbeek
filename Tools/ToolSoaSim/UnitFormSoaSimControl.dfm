object FormSoaSimControl: TFormSoaSimControl
  Left = 212
  Top = 194
  Width = 434
  Height = 402
  Caption = 'SoaSim (C) 2007 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsMDIForm
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 426
    Height = 41
    Align = alTop
    TabOrder = 0
    object ButtonClearAll: TButton
      Left = 8
      Top = 8
      Width = 89
      Height = 25
      Caption = 'Clear all'
      TabOrder = 0
      OnClick = ButtonClearAllClick
    end
    object CheckBoxAddPerson: TCheckBox
      Left = 112
      Top = 13
      Width = 105
      Height = 17
      Caption = 'Add person'
      TabOrder = 1
      OnClick = CheckBoxAddPersonClick
    end
    object CheckBoxShowChart: TCheckBox
      Left = 216
      Top = 13
      Width = 97
      Height = 17
      Caption = 'Show chart'
      TabOrder = 2
      OnClick = CheckBoxShowChartClick
    end
    object ButtonAbout: TButton
      Left = 326
      Top = 8
      Width = 89
      Height = 25
      Caption = 'About'
      TabOrder = 3
      OnClick = ButtonAboutClick
    end
  end
  object TimerMeasure: TTimer
    Interval = 10000
    OnTimer = TimerMeasureTimer
    Left = 24
    Top = 112
  end
end
