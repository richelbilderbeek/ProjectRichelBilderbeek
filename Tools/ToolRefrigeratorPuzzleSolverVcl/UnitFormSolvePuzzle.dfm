object FormSolvePuzzle: TFormSolvePuzzle
  Left = 192
  Top = 114
  BorderStyle = bsDialog
  Caption = 'The Refrigerator Puzzle Solver (C) 2008 Rich'#232'l Bilderbeek'
  ClientHeight = 304
  ClientWidth = 456
  Color = clWhite
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  ShowHint = True
  PixelsPerInch = 96
  TextHeight = 14
  object ProgressBar: TProgressBar
    Left = 7
    Top = 8
    Width = 442
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 0
  end
  object ButtonQuit: TButton
    Left = 368
    Top = 40
    Width = 81
    Height = 25
    Caption = 'Quit'
    TabOrder = 1
    OnClick = ButtonQuitClick
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 72
    Width = 445
    Height = 229
    ColCount = 9
    DefaultColWidth = 48
    FixedCols = 0
    RowCount = 9
    FixedRows = 0
    TabOrder = 2
  end
  object CheckBoxDisplay: TCheckBox
    Left = 8
    Top = 40
    Width = 161
    Height = 17
    Caption = 'Display current'
    TabOrder = 3
  end
  object ButtonSolve: TButton
    Left = 184
    Top = 40
    Width = 89
    Height = 25
    Caption = 'Solve'
    TabOrder = 4
    OnClick = ButtonSolveClick
  end
  object ButtonAbout: TButton
    Left = 280
    Top = 40
    Width = 81
    Height = 25
    Caption = 'About'
    TabOrder = 5
    OnClick = ButtonAboutClick
  end
end
