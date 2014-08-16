object FormMain: TFormMain
  Left = 192
  Top = 107
  Width = 830
  Height = 636
  Caption = 'The Chris Wiley Project (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF004444
    4444444444444444F4F4F444444444444FFF444444444444FFFFF44444444444
    4FFF444444444444F4F4F444444F4444444444444444444444444444444F4444
    4444444444449FF44F9F44FF9444F99FFF9FFF99F4444FF99F9F99FF4444444F
    F999FF4444444FF99F9F99FF4444F99FFF9FFF99F4449FF44F9F44FF94440000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  WindowState = wsMaximized
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBarMain: TStatusBar
    Left = 0
    Top = 583
    Width = 822
    Height = 19
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object PanelLeft: TPanel
    Left = 0
    Top = 0
    Width = 264
    Height = 583
    Align = alLeft
    TabOrder = 1
    object RadioGroupGamy: TRadioGroup
      Left = 1
      Top = 398
      Width = 262
      Height = 43
      Align = alBottom
      Caption = 'Mating system'
      ItemIndex = 0
      Items.Strings = (
        'Monogamy'
        'Polygyny (male can mate multiple times)')
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = RadioGroupGamyClick
    end
    object RadioGroupFemaleSampling: TRadioGroup
      Left = 1
      Top = 441
      Width = 262
      Height = 96
      Align = alBottom
      Caption = 'Female sampling'
      ItemIndex = 0
      Items.Strings = (
        'Best-of-N conspicific'
        'Best-of-N most-extreme trait'
        'Best-of-N closest trait-preference'
        'Fixed threshold conspicific'
        'Fixed threshold trait sign'
        'Fixed threshold probabilistic')
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = RadioGroupFemaleSamplingClick
    end
    object RadioGroupDensityDependentSelection: TRadioGroup
      Left = 1
      Top = 537
      Width = 262
      Height = 45
      Align = alBottom
      Caption = 'Density dependent selection'
      ItemIndex = 1
      Items.Strings = (
        'In reproduction, nOffspring = popSize parents'
        'After selection, nMatureOffspring = popSize parents')
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = RadioGroupDensityDependentSelectionClick
    end
    object PanelLeftTop: TPanel
      Left = 1
      Top = 1
      Width = 262
      Height = 120
      Align = alTop
      TabOrder = 3
      object ButtonRun: TButton
        Left = 8
        Top = 8
        Width = 129
        Height = 57
        Hint = 'Starts the simulation'
        Caption = '---- Run ----'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Impact'
        Font.Style = [fsItalic]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = ButtonRunClick
      end
      object PageControlSim: TPageControl
        Left = 1
        Top = 72
        Width = 260
        Height = 47
        ActivePage = TabSheet14
        Align = alBottom
        TabIndex = 1
        TabOrder = 2
        OnChange = PageControlSimChange
        object TabSheet13: TTabSheet
          Caption = 'Single fraction sim'
          object Label1: TLabel
            Left = 8
            Top = 8
            Width = 48
            Height = 13
            Caption = 'FractionA:'
          end
          object EditFraction: TEdit
            Left = 64
            Top = 0
            Width = 33
            Height = 21
            TabOrder = 0
            Text = '0.5'
          end
        end
        object TabSheet14: TTabSheet
          Caption = 'Range of fractions sim'
          ImageIndex = 1
          object Label3: TLabel
            Left = 128
            Top = 5
            Width = 9
            Height = 13
            Caption = 'to'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label4: TLabel
            Left = 184
            Top = 5
            Width = 20
            Height = 13
            Caption = 'step'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label2: TLabel
            Left = 8
            Top = 8
            Width = 71
            Height = 13
            Caption = 'FractionA: from'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object EditFractionFrom: TEdit
            Left = 88
            Top = 0
            Width = 33
            Height = 21
            TabOrder = 0
            Text = '0.05'
          end
          object EditFractionTo: TEdit
            Left = 144
            Top = 0
            Width = 33
            Height = 21
            TabOrder = 1
            Text = '1.0'
          end
          object EditFractionStep: TEdit
            Left = 208
            Top = 0
            Width = 33
            Height = 21
            TabOrder = 2
            Text = '0.05'
          end
        end
      end
      object BitBtn1: TBitBtn
        Left = 216
        Top = 8
        Width = 41
        Height = 57
        Hint = 'Turn sound on/off'
        Cancel = True
        ModalResult = 2
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        TabStop = False
        OnClick = BitBtn1Click
        OnMouseDown = BitBtn1MouseDown
        Glyph.Data = {
          360C0000424D360C000000000000360000002800000020000000200000000100
          180000000000000C000000000000000000000000000000000000A56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA56E3AA56E3AA5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA56E3AA5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000000000000000A5
          6E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3A00000000
          0000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA56E3A00
          0000000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3A000000000000A56E3AA56E3AA56E3A00
          0000A56E3A000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA56E3A00000000
          0000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3A000000A56E3AA56E3AA56E3A00000000
          0000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A0000000000000000000000
          00A56E3AA56E3AA56E3A00000000000000000000000000000000000000000000
          0000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000000000
          000000000000000000A56E3AA56E3AA56E3AA56E3A0000000000000000000000
          00000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFF000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          00000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          0000000000000000000000000000000000000000000000000000000000000000
          00000000000000000000000000000000000000000000000000FFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3A0000000000000000000000000000
          00000000000000000000000000000000000000000000000000000000FFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3A0000000000000000000000000000
          00000000000000000000000000000000000000000000000000000000FFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A0000
          00000000FFFFFFFFFFFF00000000000000000000000000000000000000000000
          0000FFFFFFFFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3A000000000000FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
          0000000000FFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3A000000000000FFFFFFFFFFFFFFFFFFFFFFFF00000000000000
          0000000000FFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3A00000000000000000000000000000000000000000000
          0000000000000000FFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3A00000000000000000000000000000000000000000000
          0000000000000000FFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3A00000000000000000000000000000000000000000000
          0000000000000000FFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3A00000000000000000000000000000000000000
          0000000000000000000000FFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000000000000000000000
          0000000000000000FFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A000000000000000000FF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000000000000000
          0000000000000000FFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000000000
          0000000000000000000000FFFFFFFFFFFF000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000000000
          0000000000000000000000000000000000000000000000000000A56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000000000
          0000000000000000000000000000000000000000000000000000A56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00000000
          0000000000000000000000000000000000000000A56E3AA56E3AA56E3AA56E3A
          A56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E
          3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3AA56E3A00
          0000000000000000000000000000000000A56E3AA56E3AA56E3A}
        Margin = 0
        Spacing = 0
      end
      object ButtonSave: TButton
        Left = 144
        Top = 8
        Width = 65
        Height = 57
        Hint = 
          'Saves results to tab '#39'Program output'#39' and (if not cancelled) to ' +
          'disk'
        Caption = 'Save'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Impact'
        Font.Style = [fsItalic]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = ButtonSaveClick
      end
    end
    object Panel1: TPanel
      Left = 1
      Top = 121
      Width = 262
      Height = 277
      Align = alClient
      Caption = 'Panel1'
      TabOrder = 4
      object StringGridParameters: TStringGrid
        Left = 33
        Top = 1
        Width = 228
        Height = 275
        Align = alClient
        ColCount = 2
        DefaultColWidth = 128
        DefaultRowHeight = 16
        RowCount = 23
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        ParentFont = False
        ParentShowHint = False
        ScrollBars = ssVertical
        ShowHint = True
        TabOrder = 0
        OnSelectCell = StringGridParametersSelectCell
        RowHeights = (
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16
          16)
      end
      object ProgressBarSim: TProgressBar
        Left = 1
        Top = 1
        Width = 32
        Height = 275
        Align = alLeft
        BorderWidth = 1
        Min = 0
        Max = 20
        Orientation = pbVertical
        Smooth = True
        TabOrder = 1
      end
    end
  end
  object PageControlMain: TPageControl
    Left = 264
    Top = 0
    Width = 558
    Height = 583
    ActivePage = TabSheet6
    Align = alClient
    MultiLine = True
    TabIndex = 1
    TabOrder = 2
    object TabSheet10: TTabSheet
      Caption = 'Bias and fraction mixed pairs in time'
      ImageIndex = 8
      object ChartBiasTime: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 526
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'Unidirectional mating in time')
        BottomAxis.Title.Caption = 'Time (generations)'
        LeftAxis.Title.Caption = 'Value'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series27: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clGreen
          Title = 'Bias A'
          Pointer.InflateMargins = True
          Pointer.Style = psDownTriangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series28: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Bias B'
          Pointer.InflateMargins = True
          Pointer.Style = psTriangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series29: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlack
          Title = 'Fraction mixed pairs'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Number of matings in time'
      ImageIndex = 6
      object ChartMateTime: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'Number of matings in time')
        BottomAxis.Title.Caption = 'Time (generations)'
        LeftAxis.Title.Caption = 'Number of matings'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series20: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'FemaleA - MaleA'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series21: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clYellow
          Title = 'FemaleA - MaleB'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series22: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clLime
          Title = 'Female B - Male A'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series23: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Female B - Male B'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series7: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlack
          Title = 'Total number of matings'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Trait and preference in time'
      ImageIndex = 6
      object ChartTraitPreference: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 526
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'Trait and preference in time of a sample of random individuals')
        BottomAxis.Title.Caption = 'Time (generations)'
        LeftAxis.Title.Caption = 'Value'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series5: TPointSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Trait'
          Pointer.HorizSize = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.VertSize = 2
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series6: TPointSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Preference'
          Pointer.HorizSize = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.VertSize = 2
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series25: TPointSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clWhite
          Title = 'SpeciesValue'
          Pointer.HorizSize = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.VertSize = 2
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Number of individuals in time'
      ImageIndex = 6
      object ChartPopSize: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 526
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'Number of individuals in  timer')
        BottomAxis.Title.Caption = 'Time (generations)'
        LeftAxis.Title.Caption = 'Number of individuals'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series12: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Number of females A'
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series16: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Number of females B'
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series13: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Number of males A'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series19: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Number of males B'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Bias and fraction mixed pairs per fraction'
      object ChartBias: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 526
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          '')
        Title.Visible = False
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Maximum = 1
        BottomAxis.Title.Caption = 'Fraction of MaleA (is also fraction of FemaleA)'
        LeftAxis.AxisValuesFormat = '#,##0.######'
        LeftAxis.ExactDateTime = False
        LeftAxis.StartPosition = 1
        LeftAxis.EndPosition = 99
        LeftAxis.Title.Caption = 'Value'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series1: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clGreen
          Title = 'Bias speciesA'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psDownTriangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series2: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Bias speciesB'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psTriangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series3: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlack
          Title = 'Fraction of mixed pairs'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet12: TTabSheet
      Caption = 'Number of matings per fraction'
      ImageIndex = 8
      object ChartMateFraction: TChart
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          
            'Number of matings for the different fractions maleA (=fraction f' +
            'emaleA)')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 0.1
        BottomAxis.Maximum = 1
        BottomAxis.Title.Caption = 'Fraction maleA (=fraction femaleA)'
        LeftAxis.Title.Caption = 'Number of matings'
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        TabOrder = 0
        object Series9: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'Female A x Male A'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series10: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clYellow
          Title = 'Female A x Male B'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series11: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clLime
          Title = 'Female B x Male A'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
        object Series24: TLineSeries
          Marks.ArrowLength = 0
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Female B x Male B'
          LinePen.Width = 2
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Program output'
      ImageIndex = 2
      object RichEditOutput: TRichEdit
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        Lines.Strings = (
          'RichEditOutput')
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Test'
      ImageIndex = 5
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        ActivePage = TabSheet8
        Align = alClient
        TabIndex = 0
        TabOrder = 0
        object TabSheet8: TTabSheet
          Caption = 'Test female sampling'
          object PanelTest: TPanel
            Left = 0
            Top = 0
            Width = 542
            Height = 113
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
          end
          object ChartTest: TChart
            Left = 0
            Top = 113
            Width = 542
            Height = 385
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clBlack
            Title.Font.Height = -11
            Title.Font.Name = 'Arial'
            Title.Font.Style = [fsBold]
            Title.Text.Strings = (
              'Number of matings')
            BottomAxis.Title.Caption = 'Male index'
            LeftAxis.Title.Caption = 'Number of matings'
            Legend.Visible = False
            View3D = False
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 1
            object Series4: TBarSeries
              ColorEachPoint = True
              Marks.ArrowLength = 20
              Marks.Visible = True
              SeriesColor = clRed
              Title = 'Number of matings'
              BarBrush.Color = clWhite
              BarWidthPercent = 100
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Bar'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
          end
          object StringGridTest: TStringGrid
            Left = 296
            Top = 8
            Width = 441
            Height = 96
            ColCount = 6
            DefaultColWidth = 72
            DefaultRowHeight = 30
            RowCount = 3
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 2
          end
          object ButtonTest: TButton
            Left = 8
            Top = 8
            Width = 281
            Height = 97
            Caption = 'TEST'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -96
            Font.Name = 'Impact'
            Font.Style = [fsItalic]
            ParentFont = False
            TabOrder = 3
            OnClick = ButtonTestClick
          end
        end
        object TabSheet9: TTabSheet
          Caption = 'Test probabilities'
          ImageIndex = 1
          object PanelTestProbTop: TPanel
            Left = 0
            Top = 0
            Width = 542
            Height = 49
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
            object ButtonTestSurvivalSpecies: TButton
              Left = 8
              Top = 16
              Width = 105
              Height = 25
              Caption = 'Survival species'
              TabOrder = 0
              OnClick = ButtonTestSurvivalSpeciesClick
            end
            object ButtonTestTrait: TButton
              Left = 120
              Top = 16
              Width = 89
              Height = 25
              Caption = 'Survival trait'
              TabOrder = 1
              OnClick = ButtonTestTraitClick
            end
            object ButtonTestPreference: TButton
              Left = 216
              Top = 16
              Width = 113
              Height = 25
              Caption = 'Survival preference'
              TabOrder = 2
              OnClick = ButtonTestPreferenceClick
            end
            object ButtonTestProbabilisticMating: TButton
              Left = 336
              Top = 16
              Width = 145
              Height = 25
              Caption = 'Chance to mate probabilistic'
              TabOrder = 3
              OnClick = ButtonTestProbabilisticMatingClick
            end
            object ButtonTestHelp: TButton
              Left = 488
              Top = 16
              Width = 51
              Height = 25
              Caption = 'Help'
              TabOrder = 4
              OnClick = ButtonTestHelpClick
            end
          end
          object ChartTestProbabilities: TChart
            Left = 0
            Top = 49
            Width = 542
            Height = 449
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clBlack
            Title.Font.Height = -11
            Title.Font.Name = 'MS Sans Serif'
            Title.Font.Style = [fsBold]
            Title.Text.Strings = (
              'Name')
            BottomAxis.Automatic = False
            BottomAxis.AutomaticMaximum = False
            BottomAxis.AutomaticMinimum = False
            BottomAxis.Maximum = 1
            BottomAxis.Minimum = -1
            BottomAxis.Title.Caption = 'Value'
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Maximum = 1
            LeftAxis.Title.Caption = 'Value'
            Legend.Visible = False
            View3D = False
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 1
            object Series26: TLineSeries
              Marks.ArrowLength = 8
              Marks.Visible = False
              SeriesColor = clRed
              Title = 'Series'
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              Pointer.Visible = False
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Y'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
          end
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Comments'
      ImageIndex = 3
      object RichEdit2: TRichEdit
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        Cursor = crArrow
        Align = alClient
        Lines.Strings = (
          
            'biasA =  (nMateAB + nMateBA == 0.0 ? 0.0 : nMateAB / (nMateAB + ' +
            'nMateBA));'
          
            'biasB =  (nMateAB + nMateBA == 0.0 ? 0.0 : nMateBA / (nMateAB + ' +
            'nMateBA));'
          ''
          'Mating system:'
          'Monogamy: after a male is selected for mating it is removed'
          'Polygyny: a male can be selected to mate with multiple times'
          ''
          'Female sampling:'
          'Can be tested under tab '#39'Test'#39
          ''
          'Density dependent selection:'
          '1) In reproduction, nOffspring = popSize parents:'
          
            'The offspring keeps getting selected for producing offspring unt' +
            'il there are the right number of males and females in '
          
            'the right proportions. This might slow the program down when it ' +
            'is difficult reaching these numbers.'
          '2) After selection, nMatureOffspring = popSize parents'
          
            'After selection, the remaining individuals are removed until the' +
            're are the right number of males and females in the '
          
            'right proportions. These then produce '#39'nOffspring'#39' per mating. T' +
            'his might end a simulation, when these numbers are '
          'not reached.')
        TabOrder = 0
      end
    end
    object TabSheetAbout: TTabSheet
      Caption = 'About'
      ImageIndex = 9
      object RichEditAbout: TRichEdit
        Left = 0
        Top = 0
        Width = 550
        Height = 519
        Cursor = crArrow
        Align = alClient
        Lines.Strings = (
          '  The Chris Wiley Project, simulation on mixed-pair mating'
          '  Copyright (C) 2009  Rich'#232'l Bilderbeek'
          ''
          
            '  This program is free software: you can redistribute it and/or ' +
            'modify'
          
            '  it under the terms of the GNU General Public License as publis' +
            'hed by'
          
            '  the Free Software Foundation, either version 3 of the License,' +
            ' or'
          '  (at your option) any later version.'
          ''
          
            '  This program is distributed in the hope that it will be useful' +
            ','
          '  but WITHOUT ANY WARRANTY; without even the implied warranty of'
          '  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the'
          '  GNU General Public License for more details.'
          ''
          
            '  You should have received a copy of the GNU General Public Lice' +
            'nse'
          
            '  along with this program.  If not, see <http://www.gnu.org/lice' +
            'nses/>.')
        PlainText = True
        ReadOnly = True
        TabOrder = 0
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'Excel Comma Seperated File|*.csv'
    Title = 'Give filename of data file'
    Left = 152
    Top = 24
  end
end
