object FormResults: TFormResults
  Left = 191
  Top = 107
  Width = 696
  Height = 480
  Caption = 'Results'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 14
  object PageControlMain: TPageControl
    Left = 0
    Top = 0
    Width = 688
    Height = 446
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 3
    TabOrder = 0
    object TabSheet3: TTabSheet
      Caption = 'Results'
      ImageIndex = 1
      object RichEditResults: TRichEdit
        Left = 0
        Top = 0
        Width = 680
        Height = 417
        Align = alClient
        Lines.Strings = (
          'RichEditResults')
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Population size in time'
      ImageIndex = 2
      object ChartNumbers: TChart
        Left = 0
        Top = 0
        Width = 680
        Height = 417
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -13
        Title.Font.Name = 'Courier New'
        Title.Font.Style = []
        Title.Text.Strings = (
          'Number of birds in pools initially'
          'in every generation')
        BottomAxis.Title.Caption = 'Time'
        LeftAxis.Title.Caption = 'Number of individuals'
        Legend.Alignment = laBottom
        Legend.Font.Charset = ANSI_CHARSET
        Legend.Font.Color = clBlack
        Legend.Font.Height = -11
        Legend.Font.Name = 'Courier New'
        Legend.Font.Style = []
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series2: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'Single males'
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
          SeriesColor = 8388863
          Title = 'Single females'
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
        object Series4: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clGreen
          Title = 'Couples'
          Pointer.InflateMargins = True
          Pointer.Style = psDiamond
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
        object Series5: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clYellow
          Title = 'Migrants'
          Pointer.HorizSize = 3
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.VertSize = 3
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
        object Series6: TLineSeries
          Active = False
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clBlack
          Title = 'Death'
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
    object TabSheet8: TTabSheet
      Caption = 'Pedigree'
      ImageIndex = 4
      object RichEditPedigree: TRichEdit
        Left = 0
        Top = 41
        Width = 680
        Height = 376
        Align = alClient
        Lines.Strings = (
          'RichEdit2')
        PlainText = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 680
        Height = 41
        Align = alTop
        TabOrder = 1
        object ButtonSavePedigree: TButton
          Left = 8
          Top = 8
          Width = 153
          Height = 25
          Caption = 'Save pedigree'
          TabOrder = 0
          OnClick = ButtonSavePedigreeClick
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'General parameters in time'
      ImageIndex = 4
      object Chart1: TChart
        Left = 0
        Top = 0
        Width = 680
        Height = 417
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Text.Strings = (
          'TChart')
        View3D = False
        Align = alClient
        TabOrder = 0
        object Series1: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
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
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
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
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
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
    object TabSheet9: TTabSheet
      Caption = 'Specific parameters in time'
      ImageIndex = 5
      object ChartTraits: TChart
        Left = 0
        Top = 0
        Width = 680
        Height = 417
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -13
        Title.Font.Name = 'Courier New'
        Title.Font.Style = []
        Title.Text.Strings = (
          'Evolvable traits in time')
        BottomAxis.Title.Caption = 'Time'
        BottomAxis.Title.Font.Charset = ANSI_CHARSET
        BottomAxis.Title.Font.Color = clBlack
        BottomAxis.Title.Font.Height = -11
        BottomAxis.Title.Font.Name = 'Courier New'
        BottomAxis.Title.Font.Style = []
        LeftAxis.Title.Caption = 'Evolvable trait'
        LeftAxis.Title.Font.Charset = ANSI_CHARSET
        LeftAxis.Title.Font.Color = clBlack
        LeftAxis.Title.Font.Height = -11
        LeftAxis.Title.Font.Name = 'Courier New'
        LeftAxis.Title.Font.Style = []
        Legend.Alignment = laBottom
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series7: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'playHawk alpha'
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
        object Series8: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clGreen
          Title = 'playHawk beta'
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
        object Series9: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clYellow
          Title = 'pPlayHawk (combination)'
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
  end
  object SaveDialogPedigree: TSaveDialog
    DefaultExt = 'ped'
    Filter = 'Pedigree files|*.ped'
    Left = 176
    Top = 32
  end
end
