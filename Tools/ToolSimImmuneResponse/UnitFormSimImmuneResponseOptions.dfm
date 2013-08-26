object FormSimImmuneResponseOptions: TFormSimImmuneResponseOptions
  Left = 481
  Top = 313
  BorderStyle = bsNone
  Caption = 'FormSimImmuneResponseOptions'
  ClientHeight = 200
  ClientWidth = 259
  Color = clBlack
  Font.Charset = ANSI_CHARSET
  Font.Color = clBlack
  Font.Height = -13
  Font.Name = 'Courier New'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 16
  object ButtonProduceBcell: TButton
    Left = 8
    Top = 8
    Width = 241
    Height = 25
    Caption = 'Produce B cell'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = ButtonProduceBcellClick
  end
  object ButtonQuit: TButton
    Left = 8
    Top = 168
    Width = 241
    Height = 25
    Caption = 'Quit'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = ButtonQuitClick
  end
  object ButtonProduceCtl: TButton
    Left = 8
    Top = 40
    Width = 241
    Height = 25
    Caption = 'Produce cytotoxic T lymphocyte'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = ButtonProduceCtlClick
  end
  object ButtonProduceThelperCell: TButton
    Left = 8
    Top = 104
    Width = 241
    Height = 25
    Caption = 'Produce T helper cell'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = ButtonProduceThelperCellClick
  end
  object ButtonProduceMacrophage: TButton
    Left = 8
    Top = 72
    Width = 241
    Height = 25
    Caption = 'Produce macrophage'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = ButtonProduceMacrophageClick
  end
  object ButtonAbout: TButton
    Left = 144
    Top = 136
    Width = 105
    Height = 25
    Caption = 'About'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = ButtonAboutClick
  end
  object ButtonRestart: TButton
    Left = 8
    Top = 136
    Width = 129
    Height = 25
    Caption = 'Restart'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = ButtonRestartClick
  end
end
