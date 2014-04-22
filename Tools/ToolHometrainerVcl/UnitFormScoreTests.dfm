object FormScoreTests: TFormScoreTests
  Left = 207
  Top = 134
  Width = 766
  Height = 480
  Caption = 'Hometrainer 2 Test Scorer (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 14
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 758
    Height = 41
    Align = alTop
    TabOrder = 0
    object LabelKey: TLabel
      Left = 92
      Top = 12
      Width = 21
      Height = 14
      Caption = 'Key'
    end
    object LabelPenalty: TLabel
      Left = 345
      Top = 12
      Width = 49
      Height = 14
      Caption = 'Penalty'
    end
    object LabelNquestions: TLabel
      Left = 201
      Top = 12
      Width = 91
      Height = 14
      Caption = '#questions: ?'
      Visible = False
    end
    object ButtonLoad: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Load'
      TabOrder = 0
      OnClick = ButtonLoadClick
    end
    object EditKey: TEdit
      Left = 120
      Top = 8
      Width = 73
      Height = 22
      TabOrder = 1
      Text = '0'
    end
    object ButtonSave: TButton
      Left = 672
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      Enabled = False
      TabOrder = 5
      OnClick = ButtonSaveClick
    end
    object ButtonAbout: TButton
      Left = 592
      Top = 8
      Width = 75
      Height = 25
      Caption = 'About'
      TabOrder = 4
      OnClick = ButtonAboutClick
    end
    object EditPenalty: TEdit
      Left = 400
      Top = 8
      Width = 57
      Height = 22
      TabOrder = 2
      Text = '0'
    end
    object ButtonScore: TButton
      Left = 464
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Score'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = ButtonScoreClick
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 41
    Width = 758
    Height = 405
    ActivePage = TabSheetStudents
    Align = alClient
    TabIndex = 0
    TabOrder = 1
    object TabSheetStudents: TTabSheet
      Caption = 'Student scores'
      object StringGridStudents: TStringGrid
        Left = 0
        Top = 0
        Width = 750
        Height = 376
        Align = alClient
        ColCount = 4
        DefaultColWidth = 128
        RowCount = 2
        TabOrder = 0
      end
    end
    object TabSheetQuestions: TTabSheet
      Caption = 'Question scores'
      ImageIndex = 1
      object StringGridQuestions: TStringGrid
        Left = 0
        Top = 0
        Width = 750
        Height = 376
        Align = alClient
        ColCount = 3
        DefaultColWidth = 128
        FixedCols = 0
        RowCount = 2
        TabOrder = 0
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text file|*.txt'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Title = 'Please select the results to score'
    Left = 8
    Top = 72
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'Comma seperated file|*.csv'
    Title = 'Please select a file to save the results to'
    Left = 40
    Top = 72
  end
end
